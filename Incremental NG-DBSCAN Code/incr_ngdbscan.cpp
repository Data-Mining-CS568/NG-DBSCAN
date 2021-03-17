// rename active to dataset_pts in incr_classes.h

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
			id = *G.unused_indices.begin();
			G.unused_indices.erase(G.unused_indices.begin());
			G.active.insert(id);
			G.noncore.insert(id);	// making initially noncore
			to_add.push_back(id);

			Node* curr = new Node(id,"noncore",v);
			G.id_to_node[id] = curr;
			
			G.node_index_to_coordinates[id] = v;
			G.coordinates_to_node_index[v] = id;
		}
		else {
			if(G.coordinates_to_node_index.count(v)){
				int id = G.coordinates_to_node_index[v];
				to_remove.push_back(id);
				G.active.erase(id);
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------- RANDOM NEIGHBOUR SEARCH -------------------------------------------------------------------

void check_for_completion(int u, Graph& G, Parameters& parameter, set<int>& found_completed){
	if(G.edges[u].size() == parameter.Minpts){
		found_completed.insert(u);
	}
}

void random_neighbour_search(Graph& G, vector<int>& S, vector<int>& A, int type_A, Parameters& parameter, vector<int>& upd, char type)
{
	map<int, set<int>> mp;

	// A is old clustered data (it contains indices of the points)
	if(type_A == 1)
	{ 
		// for each point in S, we find some neighbours of it
		for(int u : S)
		{
			// assign k points from each cluster
			for(auto it : G.clusters)
			{
				int v = it.first;
				for(int i = 0; i < parameter.k; i++)
				{
					int idx = rand() % G.clusters[v].size();
					mp[u].insert(G.clusters[v][idx]);
				}
			}

			// assign some points from newly added
			for(int i = 0; i < parameter.k; i++){
				int z = rand() % A.size();
				if(u != z){
					mp[u].insert(z);
				}
			}
		}
	}
	// A is new added points (it contains indices of the points)
	else if(type_A == 0)
	{
		// for each point in S, we find some neighbours of it
		for(int u : S)
		{
			// find k random neighbours of each point
			for(int i = 0; i < parameter.k; i++){
				int idx = rand() % A.size();
				mp[u].insert(A[idx]);
			}
		}
	}

	// nodes which got their type changed
	set<int> found_completed;

	// going through list of each node for which we want to find some neighbours
	for(int u : S)
	{
		int i = 0;
		set<int> temp;
		map<int, int> visited;

		// run for constant number of iterations
		while(i < parameter.iter)
		{
			// going through list of u
			for(int v : mp[u])
			{
				if(distance(u, v, G) <= parameter.epsilon){
					G.add_edge(u, v);
					G.add_edge(v, u);
					check_for_completion(v, G, parameter, found_completed);
					check_for_completion(u, G, parameter, found_completed);
				}
				// inserting non-visited neighbours of present node v in list of u
				for(int w : G.neighbours(v)){
					if(!visited.count(w)){
						visited[w] = 1;
						temp.insert(w);
					}
				}
				i++;
			}
			// changing to new list of u
			mp[u] = temp;
		}
	}
	// inserting those into upd who got their type changed from noncore to core or vice versa
	if(type == 'A'){
		for(auto v : found_completed){
			upd.push_back(v);
			G.core.insert(v);
			if(G.noncore.find(v) != G.noncore.end()){
				G.noncore.erase(v);
			}
		}	
	}
	else {
		for(auto v : S){
			if(found_completed.find(v) == found_completed.end()){
				upd.push_back(v);
				G.core.erase(v);
				G.noncore.insert(v);
			}
		}
		for(auto v : found_completed){
			if(G.noncore.find(v) != G.noncore.end()){
				G.noncore.erase(v);
			}
			G.core.insert(v);
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
				if(distance(u, v, G) <= parameter.epsilon){
					G.add_edge(u, v);
					G.add_edge(v, u);
				}
			}
		}
	}
	else {
		vector<int> S;
		for(auto v : G.noncore) S.push_back(v);
		random_neighbour_search(G, S, A, 0, parameter, upd_ins, 'A');
	}
	
	cout << A.size() << " " << G.noncore.size() << " " << upd_ins.size() << endl;
}

void node_identification_deletion(Graph& G, vector<int>& D, Parameters& parameter, vector<int>& upd_del)
{
	vector<int> dataset;
	for(auto u: G.core) dataset.push_back(u);
	for(auto u: G.noncore) dataset.push_back(u); 

	set<int>& R = G.core;
	vector<int> I;

	set<int> deleted;
	for(auto u : D){
		deleted.insert(u);
		G.delete_entries(u);
	}
	// checking which core nodes can change to non-core
	for(auto u : R){
		vector<int> affected;
		for(auto v : G.edges[u]){
			if(deleted.find(v) != deleted.end()){
				affected.push_back(u);
				break;
			}
		}
		for(auto v : affected){
			G.edges[u].erase(v);
		}
		if(G.edges[u].size() < parameter.Minpts && G.edges[u].size() + affected.size() >= parameter.Minpts){
			I.push_back(u);
		}
	}
	random_neighbour_search(G, I, dataset, 1, parameter, upd_del, 'D');
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// -------------------------------------------- CLUSTER MEMBERSHIP PART ------------------------------------------------------------------

void dfs(int u, Graph& G, int cluster_no, map<int,int>& visited)
{
	visited[u] = 1;
	int prev_cluster = G.cluster_identification[u];
	vector<int>& v = G.clusters[prev_cluster];

	auto it = find(v.begin(),v.end(),u);
	if(it != v.end()){
		v.erase(it);
	}

	G.cluster_identification[u] = cluster_no;
	G.clusters[cluster_no].push_back(u);

	for(auto v : G.edges[u]){
		if(!visited.count(v)){
			dfs(v, G, cluster_no, visited);
		}
	}
}

void cluster_membership(Graph& G, vector<int>& upd){
	map<int, int> visited;
	
	for(auto u : upd){
		if(!visited.count(u)){
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
		G.unused_indices.erase(id);
		G.active.insert(id);

		if(type == "core"){
			G.core.insert(id);
		}
		else {
			G.noncore.insert(id);
		}
		G.node_index_to_coordinates[id] = v;
		G.coordinates_to_node_index[v] = id;
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
	f.open("epsilon_graph_save1.txt",ios::out);
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
	f.open("points_save1.txt",ios::out);
	f << G.active.size() << " " << G.dimension << "\n";
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
	f.open("clusters_save1.txt",ios::out);
	f << G.clusters.size() << "\n";
	for(auto it : G.clusters){
		vector<int>& u = it.second;
		f << it.first << " " << u.size() << "\n";
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
	
	cout << "\nAddition: \n";
	for(auto u : to_add) cout << u << " ";
	cout << endl;

	cout << "\nDeletion: \n";
	for(auto u : to_delete) cout << u << " ";
	cout << endl;

	// identifying added nodes
	node_identification_addition(G, to_add, parameter, upd_ins);

	cout << "\nPresent in upd_ins: \n";
	for(auto u : upd_ins) cout << u << " ";
	cout << endl;

	cluster_membership(G, upd_ins);

	// identifying deleted nodes
	node_identification_deletion(G, to_delete, parameter, upd_del);

	// cout << "\nPresent in upd_del: \n";
	// for(auto u : upd_del) cout << u << " ";
	// cout << endl;

	cluster_membership(G, upd_del);

	// saving in the files
	save(G);
	return 0;
}

// ---------------------------------------------------------------------------------------------------------------------------------------