#include <bits/stdc++.h>
using namespace std;

#include "classes.h"

Parameters para;

double distance(int u,int v){
	return sqrtf((double)pow(coordinates[u].first - coordinates[v].first,2) + pow(coordinates[u].second - coordinates[v].second,2));
}

// Random selection of at most ρk nodes from NG.neighbours(n)
vector<int> random_selecting_nodes(Graph& NG, int n){
	vector<int> v = NG.neighbours(n);
	int threshold = min(para.p * para.k, (int)v.size());
	vector<int> selected;
	
	int count = 0;
	while(count < threshold){
		int idx = rand() % v.size();
		selected.push_back(v[idx]);
		v.erase(v.begin() + idx);
		count++;
	}
	return selected;
}

// checking neighbour graph and updating ε graph
void Check_Neighborhood(int n, Graph& NG, Graph& EG, set<int>* temp){
	
	vector<int> N = random_selecting_nodes(NG,n);

	for(int v = 0; v < N.size(); v++){
		for(int u = 0; u < N.size(); u++){
			if(N[u] == N[v]){
				continue;
			}
			double w = distance(N[u], N[v]);
			temp[N[u]].insert(N[v]);
			if(w <= para.epsilon){
				EG.add_edge(N[u], N[v]);
			}
		}
	}
}

// reducing neighbour graph
void Reduce_NG(int u, Graph& NG, Graph& EG, int& delta){
	if(EG.edges[u].size() >= para.Mmax){
		NG.remove_node(u);
		delta++;
	}
	vector<int> l = NG.neighbours(u);
	
	priority_queue<pair<double,int>> pq;
	for(auto v:l){
		pq.push({distance(u,v),v});
	}
	while(pq.size() > para.k){
		pair<double,int> curr = pq.top();
		pq.pop();
		NG.remove_edge(u, curr.second);
	}
}

// checking termination condition
bool Terminate(Graph& NG, int delta){
	int no_of_nodes = NG.active.size();

	if(no_of_nodes < para.Tn && delta < para.Tr){
		return 1;
	}
	else {
		return 0;
	}
}

// Making the graph undirected
void Reverse_Map(int v, Graph& G){
	for(int u : G.neighbours(v)){
		G.add_edge(u, v);
	}
}

// initializing each node with k random edges
void Random_Initialisation(Graph& NG){
	for(int u = 0; u < NG.N; u++)
	{
		set<int> visited;
		visited.insert(u);
		int count = 0;
		while(count < para.k){
			int v = rand() % NG.N;
			if(visited.find(v) == visited.end()){
				NG.edges[u].insert(v);
				visited.insert(v);
				count++;
			} 
		}
	}
}

void print_graph(Graph& G, int total_points){
	for(int i = 0; i < total_points; i++){
		cout << i << ": ";
		for(auto u : G.edges[i]){
			cout << u << " ";
		}
		cout<<'\n';
	}
	cout<<'\n';
}

// creating epsilon graph
Graph epsilon_graph_construction(int total_points){
	Graph EG(total_points);		// epsilon graph 
	Graph NG(total_points);		// neighbour graph
	
	// initialising each node with k random edges
	Random_Initialisation(NG);
	
	// printing after NG after random initialisation
	// print_graph(NG,total_points);
	// cout<< '\n';

	// number of nodes removed in current iteration
	int delta = 0;
	
	int i = 0;
	while(i < para.iter && !Terminate(NG, delta))
	{
		delta = 0;
		for(int u : NG.active){
			Reverse_Map(u, NG);
		}

		// do in parallel
		set<int> temp[total_points];
		for(int u : NG.active){
			Check_Neighborhood(u, NG, EG, temp);	
		}
		for(int i = 0; i < total_points; i++){
			for(int u : temp[i]){
				NG.add_edge(i, u);
			}
		}

		set<int> c;
		for(auto it:NG.active){
			c.insert(it);
		}
		for(int u : c){
			Reduce_NG(u, NG, EG, delta);
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
	// printing EG
	// print_graph(EG,total_points);
	// cout<<'\n';

	return EG;
}
