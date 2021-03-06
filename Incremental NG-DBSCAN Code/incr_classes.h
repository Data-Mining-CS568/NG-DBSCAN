
// -------------------------------------------------- CLASS FOR EACH NODE ----------------------------------------------------------------

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

// ---------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------- CLASS FOR EACH GRAPH ---------------------------------------------------------------

class Graph {
	public:
	int N;
	int dimension;
	set<int> dataset_pts;
	set<int> unused_indices;
	map<int, set<int>> edges;
	map<int,Node*> id_to_node;
	
	map<int,vector<double>> node_index_to_coordinates;
	map<vector<double>,int> coordinates_to_node_index;

	set<int> core, noncore;
	map<int,vector<int>> clusters;
	map<int,int> cluster_identification;

	void add_node(int id){
		dataset_pts.insert(id);
	}
	Graph(int total_nodes){
		edges.clear();
		for(int i = 0;i < total_nodes; i++){
			add_node(i);
		}
		this->N = total_nodes;
	}
	void store_indices(int max_indices){
		for(int i = 0; i < max_indices; i++){
			this->unused_indices.insert(i);
		}
	}
	int vertices_count(){
		return edges.size();
	}
	void remove_node(int id){
		dataset_pts.erase(id);
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
		for(auto i : dataset_pts){
			edges[i].clear();
		}
		dataset_pts.clear();
	}

	// deletes occurrence of node x from graph
	void delete_entries(int x){ 
		if(dataset_pts.find(x) != dataset_pts.end()){
			dataset_pts.erase(x);	
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
		if(cluster_identification.count(x)){
			int cluster_no = cluster_identification[x];
			auto it = find(clusters[cluster_no].begin(),clusters[cluster_no].end(),x);
			if(it != clusters[cluster_no].end()){
				clusters[cluster_no].erase(it);
			}
			cluster_identification.erase(x);	
		}
		vector<int> v;
		for(auto it : edges[x]){
			v.push_back(it);
		}
		for(auto u : v){
			edges[u].erase(x);
		}
		edges[x].clear();
	}
};

// ---------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------- CLASS FOR EACH PARAMETER --------------------------------------------------------------------

class Parameters {
	public:
	int k;
	int Mmax;
	int iter;
	double epsilon;
	int Minpts;
	int threshold;

	Parameters(int k = 15, int Mmax = 20, int iter = 15, double epsilon = 0.5, int Minpts = 4, int threshold = 100){
		this->k = k;
		this->Mmax = Mmax;
		this->iter = iter;
		this->epsilon = epsilon;
		this->Minpts = Minpts;
		this->threshold = threshold;
	}
};

// ---------------------------------------------------------------------------------------------------------------------------------------
