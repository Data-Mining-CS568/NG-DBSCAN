class Node {
	int id;
	int degree;
	int coreness;
	string coordinates;
	string type;
	Node(id){
		this.id = id;
		this.type = "none";
	}
};

class Graph {
	int N;
	set<Node> active;
	set<pair<Node,int>> edges[N+1];
	Graph(int total_nodes){
		this.active = ;
		this.N = total_nodes;
	}
	void remove_node(Node ID);
	void add_node(Node ID);
	void remove_edge(x, y, w);
	void remove_edge(x, y);
	void add_edge(x, y);
	void add_edge(x, y, w);
	vector<Node> neighbours(Node x);
};

class Parameters {
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
}