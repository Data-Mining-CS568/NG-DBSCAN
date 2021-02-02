#include <bits/stdc++.h>
#include "classes.cpp"
using namespace std;

Parameters p;

void Reverse_Map(Node n, Graph& G){
	// Making the graph undirected
	for(Node u : G.neighbours(n)){
		w = distance(v, u);
		G.add_edge(u, v, w);
	}
}

// checking neighbour graph and updating ε graph
void Check_Neighborhood(Node n, Graph NG, Graph εG) {
	N = Random selection of at most ρk nodes from NG.neighbours(n)
	for each vertex v in N {
		for each vertex u in N\{v} {
			w = distance(u, v)
			NG.add_edge(u, v, w)
			if(w <= ε)
				εG.add_edge(u, v, w)
		}
	}
}

// reducing neighbour graph
void Reduce_NG(Node u, Graph& NG, Graph& EG, int& delta){
	if(EG.neighbours(u).size() >= p.Mmax){
		NG.remove_node(u);
		delta = delta + 1;
	}
	vector<Node> l = NG.neighbours(u);
	// remove from l the k edges with smallest weights using priority queue
	
	for(auto {u,v,w} : l){
		NG.delete_edge(u, v, w);
	}
}

// checking termination condition
bool Terminate(Graph& NG, int delta){
	int no_of_nodes = NG.active.size();

	if(no_of_nodes < p.Tn && delta < p.Tr){
		return 1;
	}
	else {
		return 0;
	}
}

// initializing each node with k random edges
void Random_Initialisation(Graph& NG){
	for(int u = 0; u < NG.N; u++)
	{
		set<int> visited;
		visited.insert(u);
		int count = 0;
		while(count < p.k){
			int v = rand() % NG.N;
			if(visited.find(v) != visited.end()){
				NG.edges[u].insert(v);
				visited.insert(v);
				count++;
			} 
		}
	}
}

Graph epsilon_graph_construction(int total_points){
	Graph EG(total_points);		// epsilon graph 
	Graph NG(total_points);		// neighbour graph
	
	// initialising each node with k random edges
	Random_Initialisation(NG);
	
	// number of nodes removed in current iteration
	int delta = 0;
	
	int i = 0;
	while(i < p.iter && !Terminate(NG, delta)){
		for(Node u : NG.active){
			Reverse_Map(u, NG);
		}
		for(Node u : NG.active){
			Check_Neighborhood(u, NG, EG);	
		}
		for(Node u : NG.active){
			Reduce_NG(u, NG, EG, delta);
		}
		i++;
	}
	return EG;
}

int main()
{

	return 0;
}