#pragma GCC optimize("Ofast")
#pragma GCC optimization("unroll-loops")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

#include <bits/stdc++.h>
#include "classes.h"
using namespace std;

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
			int id = *G.unused.begin();
			to_add.push_back(id);
			G.unused.erase(G.unused.begin());
			G.node_index_to_coordinates[id] = v;
			G.coordinates_to_node_index[v] = id;
		}
		else {
			int id = G.coordinates_to_node_index[v];
			to_remove.push_back(id);
		}
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
		else if(type == "border"){
			G.border.insert(id);
		}
		else {
			G.noise.insert(id);
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

int main()
{
	vector<int> to_remove;
	vector<int> to_add;
	reading_queries(G,to_add,to_remove);
	build_epsilon_graph(G);
	return 0;
}