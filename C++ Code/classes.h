class Node 
{
	public:
	int id;
	int degree;
	int coreness;
	string coordinates;
	string type;
	Node(int id){
		this->id = id;
		this->type = "none";
		this->degree = 0;
	}
};

class Graph 
{
	public:
	int N;
	set<int> active;
	vector<set<int>> edges;
	vector<set<int>> reverse_edges;
	map<int,Node*> node_from_id;

	void add_node(int id){
		active.insert(id);
		node_from_id[id] = new Node(id);
	}

	Graph(int total_nodes){
		edges.resize(total_nodes,set<int>());
		for(int i = 0;i < total_nodes; i++){
			add_node(i);
		}
		this->N = total_nodes;
	}
	
	void remove_node(int id){
		active.erase(id);
		for(auto v : reverse_edges[id]){
			reverse_edges[id].erase(v);
			edges[v].erase(id);
		}
	}
	
	void remove_edge(int x, int y){
		edges[x].erase(y);
		reverse_edges[y].erase(x);
	}

	void add_edge(int x, int y){
		edges[x].insert(y);
		reverse_edges[y].insert(x);
	};
	
	vector<int> neighbours(int x){
		vector<int> n;
		for(auto u : edges[x]){
			n.push_back(u);
		}
		return n;
	}
};

class Parameters {
	public:
	int epsilon;	// minimum distance b/w nodes 
	int k;			// represents degree of each node in neighbour graph
	int Minpts; 	// each core node is having degree at least Minpts − 1
	int Tn;			// limits number of nodes in NG for termination
	int Tr;			// limits number of removed nodes in current iteration in NG
	int Mmax;		// used to reduce NG in phase-1 to reduce computation
	int p;			// limits nodes for which 2 hop distance is calculated in NG
	int iter;		// used to achieve convergence condition
	Parameters() {
		// initialise all with default values unless explicit values are given
	}
};