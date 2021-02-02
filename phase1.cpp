#include <bits/stdc++.h>
#include "classes.cpp"
using namespace std;

Parameters para;

double distance(int u,int v){

}

// Random selection of at most ρk nodes from NG.neighbours(n)
vector<int> random_selecting_nodes(Graph& NG, int n){
	vector<int> v = NG.neighbours(n);
	int threshold = min(para.p * para.k, v.size());
	vector<int> selected;
	
	int count = 0;
	while(count < threshold){
		int idx = rand() % v.size();
		selected.push_back(v[idx]);
		v.erase(v[idx]);
		count++;
	}
	return selected;
}

// checking neighbour graph and updating ε graph
void Check_Neighborhood(int n, Graph& NG, Graph& EG){
	
	vector<int> N = random_selecting_nodes(NG,n);

	for(int v = 0; v < N.size(); v++){
		for(int u = 0; u < N.size(); u++){
			if(u == v){
				continue;
			}
			double w = distance(u, v);
			NG.add_edge(u, v);
			if(w <= para.epsilon){
				EG.add_edge(u, v);
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
	
	priority_queue<pair<int,int>> pq;
	for(auto v:l){
		pq.insert({distance(u,v),v});
	}
	while(pq.size() > para.k){
		pair<int,int> curr = pq.top();
		pq.pop();
		NG.delete_edge(u, curr.second);
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
			if(visited.find(v) != visited.end()){
				NG.edges[u].insert(v);
				visited.insert(v);
				count++;
			} 
		}
	}
}

// creating epsilon graph
Graph epsilon_graph_construction(int total_points){
	Graph EG(total_points);		// epsilon graph 
	Graph NG(total_points);		// neighbour graph
	
	// initialising each node with k random edges
	Random_Initialisation(NG);
	
	// number of nodes removed in current iteration
	int delta = 0;
	
	int i = 0;
	while(i < para.iter && !Terminate(NG, delta)){
		for(int u : NG.active){
			Reverse_Map(u, NG);
		}
		for(int u : NG.active){
			Check_Neighborhood(u, NG, EG);	
		}
		for(int u : NG.active){
			Reduce_NG(u, NG, EG, delta);
		}
		i++;
	}
	return EG;
}