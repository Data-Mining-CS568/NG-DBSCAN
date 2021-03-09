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

	while(!f.eof()){
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
int main()
{
	vector<int> to_remove;
	vector<int> to_add;
	reading_queries(G,to_add,to_remove);
	return 0;
}