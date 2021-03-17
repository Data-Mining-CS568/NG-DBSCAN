class Node {
	public:
	int id;
	string type;
	vector<double> coordinate;
	Node(int id, string type, vector<double> d){
		this->id = id;
		this->type = type;
		this->coordinate = d;
	}
};

class Graph {
	public:
	int N;
	int dimension;
	set<int> active;
	set<int> unused_indices;
	map<int, set<int>> edges;
	map<int,Node*> id_to_node;
	
	map<int,vector<double>> node_index_to_coordinates;
	map<vector<double>,int> coordinates_to_node_index;

	set<int> core, noncore;
	map<int,vector<int>> clusters;
	map<int,int> cluster_identification;

	void add_node(int id){
		active.insert(id);
	}
	Graph(int total_nodes){
		edges.clear();
		for(int i = 0;i < total_nodes; i++){
			add_node(i);
		}
		this->N = total_nodes;
		for(int i = 0; i < 10000; i++){
			this->unused_indices.insert(i);
		}
	}
	int vertices_count(){
		return edges.size();
	}
	void remove_node(int id){
		active.erase(id);
		edges[id].clear();
	}
	void remove_edge(int x, int y){
		edges[x].erase(y);
	}
	void add_edge(int x, int y){
		edges[x].insert(y);
	};
	vector<int> neighbours(int x){
		vector<int> n;
		for(auto u : edges[x]){
			n.push_back(u);
		}
		return n;
	}
	void clean_graph(){
		for(int i = 0; i < N; i++){
			edges[i].clear();
		}
	}
	// deletes occurrence of node x from graph
	void delete_entries(int x){ 
		if(active.find(x) != active.end()){
			active.erase(x);	
		} 
		unused_indices.insert(x);
		id_to_node.erase(x);
		node_index_to_coordinates.erase(x);
		if(core.find(x) != core.end()){
			core.erase(x);
		} 
		if(noncore.find(x) != noncore.end()){
			noncore.erase(x);
		} 
		cluster_identification.erase(x);
		edges[x].clear();
	}
};

class Parameters {
	public:
	int k;			
	int Mmax;	
	int iter;
	double epsilon;	 
	int Minpts; 
	int threshold;

	Parameters(int k = 20, int Mmax = 20, int iter = 10, double epsilon = 8, int Minpts = 10, int threshold = 100){
		this->k = k;
		this->Mmax = Mmax;
		this->iter = iter;
		this->epsilon = epsilon;
		this->Minpts = Minpts;
		this->threshold = threshold;
	}
};

vector<vector<double>> coordinates;