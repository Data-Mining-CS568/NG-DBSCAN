#include <bits/stdc++.h>
using namespace std;

#include "incr_classes.h"

// ------------------------------------------------- DISTANCE FUNCTION -------------------------------------------------------------------

double distance(int u, int v, Graph& G)
{
	double ans = 0;
	vector<double>& coordinates_u = G.node_index_to_coordinates[u];
	vector<double>& coordinates_v = G.node_index_to_coordinates[v];
	for(int j = 0; j < G.dimension; j++){
		ans += (coordinates_u[j] - coordinates_v[j]) * (coordinates_u[j] - coordinates_v[j]);
	}
	return sqrt(ans);
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ----------------------------------------- FINDING POINTS TO ADD AND DELETE ------------------------------------------------------------

void reading_queries(Graph& G, vector<int>& to_add, vector<int>& to_remove)
{
	int total_queries;
	char type;
	fstream f;
	f.open("queries.txt",ios::in);
	f >> total_queries;

	for(int i = 0; i < total_queries; i++)
	{
		f >> type;
		vector<double> v(G.dimension);
		for(int i = 0; i < G.dimension; i++){
			f >> v[i];
		}
		if(type == 'A'){
			int id;
			if(G.unused_indices.size() == 0){
				id = G.last_unused_index;
				G.last_unused_index++;
			}
			else {
				id = *G.unused_indices.begin();
				G.unused_indices.erase(G.unused_indices.begin());
			}
			to_add.push_back(id);
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

void random_neighbour_search(Graph& G, vector<int>& S, vector<int>& A, int type_A, Parameters& parameter, vector<int> upd, char type)
{
	map<int, set<int>> mp;

	// A is old clustered data (it contains indices of the points)
	if(type_A == 0)
	{ 
		for(int u : S)
		{
			for(auto it : G.clusters)
			{
				int v = it.first;
				for(int i = 0; i < parameter.k; i++)
				{
					int idx = rand() % G.clusters[v].size();
					mp[u].insert(G.clusters[v][idx]);
				}
			}
		}
	}
	// A is new added points (it contains indices of the points)
	else if(type_A == 1)
	{
		for(int u : S)
		{
			for(int i = 0; i < parameter.k; i++){
				int idx = rand() % A.size();
				mp[u].insert(A[idx]);
			}
		}
	}

	for(int u : S)
	{
		int i = 0;
		set<int> temp;
		map<int, int> visited;
		bool complete = 0;
		while(i < parameter.iter)
		{
			for(int v : mp[u])
			{
				if(G.edges[u].size() >= parameter.Minpts){
					complete = 1;
					break;
				}
				if(distance(u, v, G) <= parameter.epsilon){
					G.add_edge(u, v);
				}
				for(int w : G.neighbours(v)){
					if(!visited[w]){
						visited[w] = 1;
						temp.insert(w);
					}
				}
				i++;
			}
			if(complete){
				break;
			}
			mp[u] = temp;
		}

		// inserting those into upd who got their type changed from core to noncore or vice versa
		if(complete && type == 'A'){ //change4 
			upd.push_back(u);
			if(type_A == 1){ //new data
				G.core.insert(u);
			}
			else{
				G.core.insert(u);
				G.noncore.erase(u);
			}
		}

		else if(!complete && type == 'A' && type_A ==1) //new data to be added in noncore set
		{	
			G.noncore.insert(u);
		}
		else if(!complete && type == 'D'){
			upd.push_back(u);
			G.core.erase(u);
			G.noncore.erase(u);
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ---------------------------------------- NODE IDENTIFICATION PART ---------------------------------------------------------------------

void node_identification_addition(Graph& G, vector<int>& A, Parameters& parameter, vector<int>& upd_ins)
{	
	// find epsilon neighbourhood of newly added points
	vector<int> dataset;
	for(auto u: G.core) dataset.push_back(u);
	for(auto u: G.noncore) dataset.push_back(u); 
	random_neighbour_search(G, A, dataset, 1, parameter, upd_ins, 'A');

	if(A.size() * G.noncore.size() <= parameter.threshold)
	{
		for(auto u : G.noncore){
			for(auto v : A){
				if(G.edges[u].size() > parameter.Minpts){
					break;
				}
				if(distance(u,v,G) <= parameter.epsilon){
					G.add_edge(u,v);
				}
			}
		}
	}
	else {
		vector<int> S;
		for(auto v : G.noncore) S.push_back(v);
		random_neighbour_search(G, S, A, 0, parameter, upd_ins, 'A');
	}
}

void node_identification_deletion(Graph& G, vector<int>& D, Parameters& parameter, vector<int>& upd_del)
{
	vector<int> dataset;
	for(auto u: G.core) dataset.push_back(u);
	for(auto u: G.noncore) dataset.push_back(u); 

	set<int>& R = G.core;
	vector<int> I;

	set<int> d;
	for(auto u : D){
		d.insert(u);
		G.delete_entries(u);
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
	random_neighbour_search(G, I, dataset, 1, parameter, upd_del, 'D');
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// -------------------------------------------- CLUSTER MEMBERSHIP PART ------------------------------------------------------------------

void dfs(int u, Graph& G, int cluster_no, vector<int>& visited)
{
	visited[u] = 1;
	int prev_cluster = G.cluster_identification[u];
	vector<int>& v = G.clusters[prev_cluster];
	auto it = find(v.begin(),v.end(),u);
	v.erase(it);

	G.cluster_identification[u] = cluster_no;
	G.clusters[cluster_no].push_back(u);

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
	f.open("epsilon_graph_save.txt",ios::in);
	string s;
	G.edges.clear();

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
	f.open("points_save.txt",ios::in);
	int n, dimension, id;
	string type;
	f >> n >> dimension;
	G.dimension = dimension;

	while(!f.eof())
	{
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
	f.open("clusters_save.txt",ios::in);

	// Reading Clusters file
	int no_of_clusters, pts_each_cluster, cluster_id = 0;
	f >> no_of_clusters;

	for(int j = 0; j < no_of_clusters; j++)
	{
		f >> cluster_id >> pts_each_cluster;
		vector<int> v(pts_each_cluster);
		for(int i = 0; i < pts_each_cluster; i++){
			f >> v[i];
			G.cluster_identification[v[i]] = cluster_id;
		}
		G.clusters[cluster_id] = v;
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
	f << G.clusters.size() << "\n";
	for(auto it : G.clusters){
		vector<int>& u = it.second;
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
	Graph G(0);
	Parameters parameter;
	vector<int> to_delete, to_add;
	vector<int> upd_ins, upd_del;
	
	// building the graph from static version
	build_graph(G);

	// reading the points to add or remove
	reading_queries(G, to_add, to_delete);
	
	// identifying added nodes
	// node_identification_addition(G, to_add, parameter, upd_ins);
	// cluster_membership(G, upd_ins);

	// identifying deleted nodes
	// node_identification_deletion(G, to_delete, parameter, upd_del);
	// cluster_membership(G, upd_del);

	// saving in the files
	// save(G);

	return 0;
}

// ---------------------------------------------------------------------------------------------------------------------------------------