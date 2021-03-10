#pragma GCC optimize("Ofast")
#pragma GCC optimization("unroll-loops")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

#include <bits/stdc++.h>
#include "classes.h"
using namespace std;

// ------------------------------------------------- DISTANCE FUNCTION -------------------------------------------------------------------

double distance(int u, int v)
{
	double ans = 0;
	vector<double> coordinates_u = node_index_to_coordinates[u];
	vector<double> coordinates_v = node_index_to_coordinates[v];
	for(int j = 0; j < dimensions; j++){
		ans += (coordinates_u[j] - coordinates_v[j]) * (coordinates_u[j] - coordinates_v[j]);
	}
	return sqrt(ans);
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ----------------------------------------- FINDING POINTS TO ADD AND DELETE ------------------------------------------------------------

void reading_queries(Graph& G, vector<int>& to_add, vector<int>& to_remove)
{
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

// ---------------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------- RANDOM NEIGHBOUR SEARCH -------------------------------------------------------------------

void Reverse_Map(int v, Graph& G){
	for(int u : G.neighbours(v)){
		G.add_edge(u, v);
	}
}

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

void Check_Neighborhood(int u, Graph& NG, Graph& EG, set<int>* temp, Parameters parameter)
{	
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

void random_neighbour_search(Graph& G, vector<int>& S, vector<int>& A, int type_A, Parameters& parameter)
{
	map<int, set<int>> v;

	// A is old clustered data (it contains indices of the points)
	if(type_A == 0)
	{ 
		for(int u : S)
		{
			for(int v : clusters)
			{
				for(int i = 0; i < parameter.k; i++)
				{
					int idx = rand() % clusters[v].size();
					v[u].insert(clusters[v][idx]);
				}
			}
		}
	}
	// A is new added points (it contains indices of the points)
	else if(type_A == 1)
	{
		for(int u : s)
		{
			for(int i = 0; i < parameter.k; i++){
				int idx = rand() % A.size();
				v[u].insert(A[idx]);
			}
		}
	}

	for(int u : S){
		int i = 0;
		while(i < parameter.iter){
			for(int v : )
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ---------------------------------------- NODE IDENTIFICATION PART ---------------------------------------------------------------------

void node_identification_addition(Graph& G, vector<int>& A, Parameter& parameter, vector<int>& upd_ins)
{	
	// find epsilon neighbourhood of newly added points
	vector<int> dataset;
	for(auto u: G.core) dataset.push_back(u);
	for(auto u: G.noncore) dataset.push_back(u); 
	random_neighbour_search(G, A, dataset, 1, parameter, upd_ins);

	if(A.size() * G.noncore.size() <= parameter.threshold)
	{
		for(auto u : G.noncore){
			for(auto v : A){
				if(G.edges[u].size() > parameter.epsilon){
					break;
				}
				if(distance(u,v) <= parameter.epsilon){
					G.add_edge(u,v);
				}
			}
		}
	}
	else {
		vector<int> S;
		for(auto v : G.noncore) S.push_back(v);
		random_neighbour_search(G, S, A, 0, parameter, upd_ins);
	}
}

void node_identification_deletion(Graph& G, vector<int>& D, Parameter& parameter, vector<int>& upd_del)
{
	vector<int> dataset;
	for(auto u: G.core) dataset.push_back(u);
	for(auto u: G.noncore) dataset.push_back(u); 

	set<int>& R = G.core;
	vector<int> I;

	set<int> d;
	for(auto u : D){
		d.insert(u);
	}
	for(auto u : R){
		vector<int> to_remove;
		for(auto v : G.edges[u]){
			if(d.find(v) != d.end()){
				to_remove.push_back(v);
			}
		}
		for(auto v : to_remove){
			G.edges[u].erase(v);
		}
		if(G.edges[u].size() < parameter.Minpts && G.edges[u].size() + to_remove.size() >= parameter.Minpts){
			I.push_back(u);
		}
	}
	random_neighbour_search(G, I, dataset, 1, parameter, upd_del);
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// -------------------------------------------- CLUSTER MEMBERSHIP PART ------------------------------------------------------------------

void dfs(int u, Graph& G, int cluster_no, vector<int>& visited)
{
	visited[u] = 1;
	int prev_cluster = G.cluster_identification[u];
	G.cluster[prev_cluster].erase(u);

	G.cluster_identification[u] = cluster_no;
	G.cluster[cluster_no].insert(u);

	for(auto v : G.edges[u]){
		if(!visited[v]){
			dfs(v, G, cluster_no, visited);
		}
	}
}

void cluster_membership(Graph& G, vector<int>& upd){
	vector<int> visited(G.N + 1, 0);
	
	for(auto u : upd){
		if(!visited[u]){
			dfs(u, G, u, visited);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ----------------------------------------- BUILDING THE GRAPH --------------------------------------------------------------------------

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

void build_graph(Graph& G){
	build_epsilon_graph(G);
	points_info(G);
	clusters_info(G);
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// -------------------------------------------- SAVE INFO REGARDING CLUSTERS AND POINTS IN FILES -----------------------------------------

void save_epsilon_graph(Graph& G){
	fstream f;
	f.open("epsilon_graph.txt",ios::out);
	for(auto u : G.active){
		f << u << "  ";
		for(auto v : G.edges[u]){
			f << v << " ";
		}
		f << "\n";
	}
}

void save_points_info(Graph& G){
	fstream f;
	f.open("points_info.txt",ios::out);
	f << G.dimension << "\n";
	for(auto u : G.active){
		Node* curr = G.id_to_node[u];
		f << u << " " << curr->type << " ";
		for(double c : curr->coordinate){
			f << c << " ";
		}
		f << "\n";
	}
}

void save_clusters_info(Graph& G){
	fstream f;
	f.open("clusters_info.txt",ios::out);
	f << clusters.size() << "\n";
	for(vector<int> u : clusters){
		f << u.size() << "\n";
		for(int v : u){
			f << v << " ";
		}
		f << "\n";
	}
}

void save(Graph& G){
	save_epsilon_graph(G);
	save_points_info(G);
	save_clusters_info(G);
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ---------------------------------- MAIN FUNCTION CALLING ALL OTHER FUNCTIONS ----------------------------------------------------------

int main()
{
	Graph G;
	vector<int> to_remove, to_add;
	vector<int> upd_ins, upd_del;
	
	// building the graph from static version
	build_graph();

	// reading the points to add or remove
	reading_queries(G, to_add, to_remove);
	
	// identifying added nodes
	node_identification_addition(G, to_add, parameter, upd_ins);
	cluster_membership(upd_ins);

	// identifying deleted nodes
	node_identification_deletion(G, to_delete, parameter, upd_del);
	cluster_membership(upd_del);

	// saving in the files
	save(G);

	return 0;
}

// ---------------------------------------------------------------------------------------------------------------------------------------