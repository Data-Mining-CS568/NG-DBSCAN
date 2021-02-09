class Node 
{
	public:
	int id;
	string type;
	Node(int id){
		this->id = id;
		this->type = "none";
	}
};

class Graph 
{
	public:
	int N;
	set<int> active;
	vector<set<int>> edges;

	void add_node(int id){
		active.insert(id);
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
};

class Parameters {
	public:
	double epsilon;	// minimum distance b/w nodes 
	int k;			// represents degree of each node in neighbour graph
	int Minpts; 	// each core node is having degree at least Minpts − 1
	double Tn;			// limits number of nodes in NG for termination
	double Tr;			// limits number of removed nodes in current iteration in NG
	int Mmax;		// used to reduce NG in phase-1 to reduce computation
	int p;			// limits nodes for which 2 hop distance is calculated in NG
	int iter;		// used to achieve convergence condition
	Parameters(){
		// initialise all with default values unless explicit values are given
		Tn = 10;
		Tr = 5;
		k = 20;
		Mmax = 20;
		p = 2;
		iter = 10;
		epsilon = 8;
		Minpts = 10;
	}
};

vector<vector<double>> coordinates;
map<int, Node*> node_from_id;
Parameters parameter;
int dimensions;
