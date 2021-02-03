#include <bits/stdc++.h>
using namespace std;

#include "phase1.cpp"

// return maximum core node from the list
int Max_Core_Node(vector<int> list, Graph& G)
{
	// returns node from list having maximum coreness value
	vector<pair<int,int>> v;
	for(auto it:list){
		v.push_back({-G.edges[it].size(), it});
	}
	sort(v.begin(), v.end());
	return v[0].second;
}

// convert graph to identify all nodes and return it
Graph Coreness_Dissemination(Graph EG, int total_nodes)
{
	// Here we identify the core, boundary and noise points of the input ε-graph.
	for(auto v : EG.active){
		if(EG.edges[v].size() >= para.Minpts - 1){
			node_from_id[v]->type = "core"; 							// Make it a core node
		}
	}
	for(auto v : EG.active){
		if(node_from_id[v]->type != "core"){
			for(auto u : EG.neighbours(v)){
				if(node_from_id[u]->type == "core"){
					node_from_id[v]->type = "border"; 					// Make it a border node
				}
			}	
		}
	}
	set<int> s;
	for(auto it: EG.active){
		s.insert(it);
	}
	for(auto v : s){
		if(node_from_id[v]->type != "core" && node_from_id[v]->type != "border"){
			node_from_id[v]->type = "noise";							// Mark them as noise points
			EG.remove_node(v);											// We need to remove all the noise points from G
		}
	}
	return EG;
}

void Max_Selection_Step(int u, Graph& G, Graph& H){
	vector<int> NNg = G.neighbours(u);
	NNg.push_back(u);
	
	int umax = Max_Core_Node(NNg,G);
	// cout << u << " " << node_from_id[u]->type << " " << umax << '\n';

	if(node_from_id[u]->type != "core"){
		H.active.insert(u);
		H.add_edge(u, umax);
	}
	else {
		for(auto v : NNg){
			H.active.insert(v);
			H.add_edge(v, umax);
		}
	}
	H.active.insert(umax);
	H.add_edge(umax, umax);
}

// in pruning, nodes not proposed as seeds(those with no incoming edges) are deactivated
void Pruning_Step(int u, Graph& T, Graph& H, Graph& G)
{
	vector<int> NNh = H.neighbours(u);
	int umax = Max_Core_Node(NNh, H);
	
	if(node_from_id[u]->type != "core"){
		G.remove_node(u);
		T.add_edge(umax, u);
	}
	else {
		bool f = 0;
		for(auto v : NNh){
			if(v != umax){
				G.add_edge(v, umax);
				G.add_edge(umax, v);	
			}
			if(v == u){
				f = 1;
			}
		}
		// if u not present in NNh
		if(f == 0){
			G.remove_node(u);
			T.add_edge(umax, u);
		}
	}
}

void dfs(int curr, Graph& T, vector<bool>& visited, vector<int>& v){
	if(visited[curr]){
		return;
	}
	v.push_back(curr);
	visited[curr] = 1;
	for(auto it:T.edges[curr]){
		dfs(it,T,visited,v);
	}
}

Graph Seed_Propagation(set<int> seeds, Graph T)
{
	vector<bool> visited(T.N,0);
	vector<vector<int>> list;
	for(auto it:seeds){
		vector<int> v;
		dfs(it,T,visited,v);
		list.push_back(v);
	}
	for(int i = 0; i < list.size(); i++){
		for(auto it:list[i]){
			cout<<it<<" ";
		}
		cout<<'\n';
	}
	// The final output will be a list of lists where each list corresponds to a separate cluster
	return T;
}

void initialize_nodes(int total_nodes){
	for(int i = 0; i < total_nodes; i++){
		node_from_id[i] = new Node(i);
	}
}

void print_node_type(int total_nodes){
	for(int i = 0; i < total_nodes; i++){
		cout<<node_from_id[i]->type<<" ";
	}
	cout<<'\n';
}

// finding all the clusters
Graph Discovering_Dense_Regions(Graph EG, int total_nodes)
{
	initialize_nodes(total_nodes);

	Graph T(total_nodes);
	Graph G = Coreness_Dissemination(EG, total_nodes);
	print_graph(G, total_nodes);

	int i = 0;
	while(i < para.iter && G.active.size() > 0)
	{
		Graph H(total_nodes);
		H.active.clear();

		// Seed identification process
		for(auto n : G.active){
			Max_Selection_Step(n, G, H);	
		}
		
		G.clean_graph();

		// do in parallel
		set<int> s;
		for(auto n : H.active){
			s.insert(n);
		}
		for(auto n : s){
			Pruning_Step(n, T, H, G);	
		}
		i++;
	}
	print_graph(T, total_nodes);
	return Seed_Propagation(G.active, T);
}

int main()
{
	int n;
	cin>>n;
	coordinates.resize(n);
	for(int i = 0; i < n; i++){
		cin >> coordinates[i].first >> coordinates[i].second;
	}
	cout << '\n';
	Graph EG = epsilon_graph_construction(n);
	Graph T = Discovering_Dense_Regions(EG,n);
	return 0;
}