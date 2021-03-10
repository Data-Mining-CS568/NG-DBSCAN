#pragma GCC optimize("Ofast")
#pragma GCC optimization("unroll-loops")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

#include <bits/stdc++.h>
#include "classes.h"
using namespace std;

// calculating distance between 2 points
double distance(int u, int v)
{
	if(dataset_type == "text"){
		double ans = jaro_winkler(sentences[u], sentences[v]);
		return ans;
	}
	else if(dataset_type == "non_text"){
		double ans = 0;
		vector<double> coordinates_u = node_index_to_coordinates[u];
		vector<double> coordinates_v = node_index_to_coordinates[v];
		for(int j = 0; j < dimensions; j++){
			ans += (coordinates_u[j] - coordinates_v[j]) * (coordinates_u[j] - coordinates_v[j]);
		}
		return sqrtf(ans);
	}
	return 0.0;
}

void reading_queries(Graph& G,vector<int>& to_add,vector<int>& to_remove){
	int dimension;
	char type;
	fstream f;
	f.open("queries.txt",ios::in);
	f >> dimension;

	while(!f.eof())
	{
		f >> type;
		vector<double> v(dimension);
		for(int i = 0; i < dimension; i++){
			f >> v[i];
		}
		if(type == 'A'){
			int id = *G.unused_indices.begin();
			to_add.push_back(id);
			G.unused.erase(G.unused_indices.begin());
			G.node_index_to_coordinates[id] = v;
			G.coordinates_to_node_index[v] = id;
		}
		else {
			int id = G.coordinates_to_node_index[v];
			to_remove.push_back(id);
		}
	}
}
// Making the graph undirected
void Reverse_Map(int v, Graph& G){
	for(int u : G.neighbours(v)){
		G.add_edge(u, v);
	}
}

// reducing neighbour graph
void Reduce_NG(int u, Graph& NG, Graph& EG, int& delta, Parameters parameter){
	if(EG.edges[u].size() >= parameter.Mmax){
		NG.remove_node(u);
		delta++;
	}
	vector<int> l = NG.neighbours(u);
	
	priority_queue<pair<double,int>> pq;
	for(auto v:l){
		pq.push({distance(u,v),v});
	}
	while(pq.size() > parameter.k){
		pair<double,int> curr = pq.top();
		pq.pop();
		NG.remove_edge(u, curr.second);
	}
}


// checking neighbour graph and updating ε graph
void Check_Neighborhood(int u, Graph& NG, Graph& EG, set<int>* temp, Parameters parameter){
	
vector<int> neighbours = NG.neighbours(u);
for(auto v : neighbours){
		double dis = distance(u,v);
		if(dis<=parameter.epsilon){
			EG.add_edge(u,v);
			//Add neighbours of v in NG
			vector<int> temp1 = EG.neighbours(v);
			for(auto v1 : temp1){
				temp1[v].insert(v1);
			}

		}
	}
}


void random_neighbour_search(Graph & EG, vector<int> &S, vector<int> &A, int typeA, Parameters parameter)
{
	
	int total_nodes = EG.vertices_count();
	Graph NG(total_nodes);
	//Random Initialisation
	if(typeA == 0){ //A is old clustered data (it contains indices of the points)
		for(auto u : s){
			for(int it=0; it<list.size();++it)
			{
				for(int i=0;i<parameter.k;++i){
					int ind = rand()%(list[it].size());
					NG.add_edge(u, list[it][ind]);
				}
			}
		}
	}
	else if(typeA == 1){ //A is new added points (it contains indices of the points)
		for(auto u : s){
			for(int i=0;i<parameter.k;++i){
				int ind = rand()%(A.size());
				NG.add_edge(u, A[ind]);
			}
		}
	}


	int i=0;
	while(i<parameter.iter){
		for(int u : NG.active){
				Reverse_Map(u, NG);
		}

		set<int> temp[total_nodes];
		for(int u : NG.active){
			Check_Neighborhood(u, NG, EG, temp, parameter);	
		}
		for(int i = 0; i < total_nodes; i++){
			for(int u : temp[i]){
				NG.add_edge(i, u);
			}
		}

		set<int> c;
		for(auto it:NG.active){
			c.insert(it);
		}
		
		for(int u : c){
			Reduce_NG(u, NG, EG, delta, parameter);
		}
		
		// remove the unnecessary edges
		for(int u : NG.active){
			vector<int> temp = NG.neighbours(u);
			for(int v : temp){
				if(NG.active.find(v) == NG.active.end()){
					NG.edges[u].erase(v);
				}
			}
		}
		i++;

	}

}

void build_epsilon_graph(Graph& G)
{
	fstream f;
	f.open("epsilon_graph.txt",ios::in);
	string s;

	while(!f.eof()){
		getline(f,s);
		vector<int> v;
		stringstream str(s);
		string id;
		while(str >> id){
			v.push_back(stoi(id));
		}
		for(int i = 1; i < v.size(); i++){
			G.edges[v[0]].insert(v[i]);
		}
	}
}



void points_info(Graph& G)
{
	fstream f;
	f.open("points_info.txt",ios::in);
	int dimension, id;
	string type;
	f >> dimension;

	while(!f.eof()){
		vector<double> v(dimension);
		f >> id >> type;
		for(int i = 0; i < dimension; i++){
			f >> v[i];
		}
		if(type == "core"){
			G.core.insert(id);
		}
		else {
			G.noncore.insert(id);
		}
		Node* n = new Node(id, type, v);
		G.id_to_node[id] = n;
	}
}

void clusters_info(Graph& G)
{
	fstream f;
	f.open("clusters.txt",ios::in);
	int no_of_clusters, each_cluster;
	f >> no_of_clusters;

	while(!f.eof()){
		f >> each_cluster;
		vector<int> v(each_cluster);
		for(int i = 0; i < each_cluster; i++){
			cin >> v[i];
		}
	}
}

void node_identification_addition(Graph& G, vector<int>& A, Parameter& p){
	
	Graph EG(G.vertices_count()+A.size());
	build_epsilon_graph(EG);

	//find epsilon neighbourhood of newly added points
	vector<int> dataset(A);
	for(auto u: G.core) dataset.push_back(u);
	for(auto u: G.noncore) dataset.push_back(u); 
	random_neighbour_search(EG, A, dataset, 1, p)

	if(A.size() * G.noncore.size() <= p.threshold){
		for(auto u : G.noncore){
			for(auto v : A){
				if(G.edges[u].size() > p.epsilon){
					break;
				}
				if(distance(u,v) <= p.epsilon){
					G.add_edge(u,v);
				}
			}
		}
	}
	else{
		vector<int> S;
		for(auto v : G.noncore) S.push_back(v);
		random_neighbour_search(EG,S,A,0, p);
	}
}

int main()
{
	vector<int> to_remove;
	vector<int> to_add;
	reading_queries(G,to_add,to_remove);
	build_epsilon_graph(G);
	return 0;
}