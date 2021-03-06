#include "NG-DBSCAN/phase1.cpp"

// return maximum core node from the list
int Max_Core_Node(vector<int> list, Graph& G)
{
	// returns node from list having maximum coreness value
	vector<pair<int,int>> v;
	for(auto it:list){
		v.push_back({-G.edges[it].size(), it});
	}
	sort(v.begin(), v.end());
	return v[0].second;
}

// convert graph to identify all nodes and return it
Graph Coreness_Dissemination(Graph EG, int total_nodes, Parameters parameter)
{
	// Here we identify the core, boundary and noise points of the input ε-graph.
	for(auto v : EG.active){
		if(EG.edges[v].size() >= parameter.Minpts - 1){
			node_from_id[v]->type = "core"; 							// Make it a core node
		}
	}
	for(auto v : EG.active){
		if(node_from_id[v]->type != "core"){
			for(auto u : EG.neighbours(v)){
				if(node_from_id[u]->type == "core"){
					node_from_id[v]->type = "border"; 					// Make it a border node
				}
			}	
		}
	}
	set<int> s;
	for(auto it: EG.active){
		s.insert(it);
	}
	for(auto v : s){
		if(node_from_id[v]->type != "core" && node_from_id[v]->type != "border"){
			node_from_id[v]->type = "noise";							// Mark them as noise points
			EG.remove_node(v);											// We need to remove all the noise points from G
		}
	}
	return EG;
}

void Max_Selection_Step(int u, Graph& G, Graph& H){
	vector<int> NNg = G.neighbours(u);
	NNg.push_back(u);
	
	int umax = Max_Core_Node(NNg,G);

	if(node_from_id[u]->type != "core"){
		H.active.insert(u);
		H.add_edge(u, umax);
	}
	else {
		for(auto v : NNg){
			H.active.insert(v);
			H.add_edge(v, umax);
		}
	}
	H.active.insert(umax);
	H.add_edge(umax, umax);
}

// in pruning, nodes not proposed as seeds(those with no incoming edges) are deactivated
void Pruning_Step(int u, Graph& T, Graph& H, Graph& G)
{
	vector<int> NNh = H.neighbours(u);
	int umax = Max_Core_Node(NNh, H);
	
	if(node_from_id[u]->type != "core"){
		G.remove_node(u);
		T.add_edge(umax, u);
	}
	else {
		bool f = 0;
		for(auto v : NNh){
			if(v != umax){
				G.add_edge(v, umax);
				G.add_edge(umax, v);	
			}
			if(v == u){
				f = 1;
			}
		}
		// if u not present in NNh
		if(f == 0){
			G.remove_node(u);
			T.add_edge(umax, u);
		}
	}
}

void dfs(int curr, Graph& T, vector<bool>& visited, vector<int>& v){
	if(visited[curr]){
		return;
	}
	v.push_back(curr);
	visited[curr] = 1;
	for(auto it:T.edges[curr]){
		dfs(it,T,visited,v);
	}
}

Graph Seed_Propagation(set<int> seeds, Graph T, Parameters parameter)
{
	vector<bool> visited(T.N,0);
	vector<vector<int>> list; //declared it in classes.h, need to be removed later

	for(auto it:seeds){
		vector<int> v;
		dfs(it,T,visited,v);
		list.push_back(v);
	}

	fstream out, f;
	out.open("Files/clusters.txt",ios::out);
	f.open("Files/numbered_clusters.txt",ios::out);

	// printing clusters using numbering only
	f << list.size() << " " << parameter.epsilon << '\n';
	for(int i = 0; i < list.size(); i++){
		f << list[i].size() << '\n';
		for(auto it:list[i]){
			f << it << " ";
		}
		f << "\n";
	}

	// printing all clusters in clusters.txt
	out << list.size() << " " << dimensions << '\n';

	int noise = 0;
	for(int i = 0; i < T.N; i++){
		if(node_from_id[i]->type == "noise"){
			noise++;
		}
	}
	
	if(dataset_type == "non_text")
	{
		for(int i = 0; i < list.size(); i++){
			out << list[i].size() << "\n";
			for(auto it:list[i]){ 
				for(int j = 0; j < dimensions; j++){
					out << coordinates[it][j] << " ";	
				}
				out << node_from_id[it]->type << '\n';
			}
		}
		out << noise << '\n';
		for(int i = 0; i < T.N; i++){
			if(node_from_id[i]->type == "noise"){
				for(int j = 0; j < dimensions; j++){
					out << coordinates[i][j] << " ";	
				}
				out << node_from_id[i]->type << '\n';
			}
		}

	}
	else if(dataset_type == "text")
	{
		for(int i = 0; i < list.size(); i++){
			out << list[i].size() << "\n";
			for(auto it:list[i]){ 
				out << sentences[it] << " ";					
				out << node_from_id[it]->type << '\n';
			}
		}
		out << noise << '\n';
		for(int i = 0; i < T.N; i++){
			if(node_from_id[i]->type == "noise"){
				out << sentences[i]<< " ";	
				out << node_from_id[i]->type << '\n';
			}
		}
	}
	// The final output will be a list of lists where each list corresponds to a separate cluster
	return T;
}

void initialize_nodes(int total_nodes){
	for(int i = 0; i < total_nodes; i++){
		node_from_id[i] = new Node(i);
	}
}

void print_node_type(int total_nodes){
	for(int i = 0; i < total_nodes; i++){
		cout << node_from_id[i]->type << " ";
	}
	cout << '\n';
}

// finding all the clusters
Graph Discovering_Dense_Regions(Graph EG, int total_nodes, Parameters parameter)
{
	// writing epsilong graph in file epsilon_graph.txt
	fstream f;
	f.open("Files/epsilon_graph.txt",ios::out);
	print_graph(EG, total_nodes, f);
	f.close();

	initialize_nodes(total_nodes);

	Graph T(total_nodes);
	Graph G = Coreness_Dissemination(EG, total_nodes, parameter);

	int i = 0;
	while(i < parameter.iter && G.active.size() > 0)
	{
		Graph H(total_nodes);
		H.active.clear();

		// Seed identification process
		for(auto n : G.active){
			Max_Selection_Step(n, G, H);	
		}
		
		G.clean_graph();

		// do in parallel
		set<int> s;
		for(auto n : H.active){
			s.insert(n);
		}
		for(auto n : s){
			Pruning_Step(n, T, H, G);	
		}
		i++;
	}

	// printing propagation tree in file propagation_tree.txt
	f.open("Files/propagation_tree.txt",ios::out);
	print_graph(T, total_nodes, f);
	f.close();
	
	return Seed_Propagation(G.active, T, parameter);
}

int main()
{
	cout << "Want to change the default parameters?\nEnter 1 for Yes and 0 for No\n";

	int parameterChange;
	cin >> parameterChange;
	double xTn = 0.001;			// limits number of nodes in NG for termination
	double xTr = 0.0001;		// limits number of removed nodes in current iteration in NG
	int k = 20;					// represents degree of each node in neighbour graph
	int Mmax = 20;				// used to reduce NG in phase-1 to reduce computation
	int p = 2;					// limits nodes for which 2 hop distance is calculated in NG
	int iter = 10;
	double epsilon = 1.0;		// minimum distance b/w nodes 
	int Minpts  = 10; 			// each core node is having degree at least Minpts − 1
	
	if(parameterChange == 1)
	{
		cout << "Enter Parameters(If you want to keep default value then enter -1\n";
		cout << "Enter x for Tn(Tn = x*n)\n"; 	cin >> xTn; 
		cout << "Enter x for Tr(Tr = x*n)\n"; 	cin >> xTr;
		cout << "Enter k\n"; 					cin >> k;
		cout << "Enter Mmax\n"; 				cin >> Mmax;
		cout << "Enter p\n"; 					cin >> p;
		cout << "Enter iter\n"; 				cin >> iter;
		cout << "Enter epsilon\n"; 			cin >> epsilon;
		cout << "Enter Minpts\n"; 				cin >> Minpts;
	}

	fstream f;
	f.open("Files/points.txt",ios::in);
	int n; 
	
	f >> dataset_type >> n >> dimensions;
	
	Parameters parameter(xTn*n, xTr*n, k, Mmax, p, iter, epsilon, Minpts);
	
	if(dataset_type == "non_text")
	{
		coordinates.resize(n,vector<double>(dimensions));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < dimensions; j++){
				f >> coordinates[i][j];
			}
		}
	}
	else if(dataset_type == "text")
	{
		sentences.resize(n);
		for(int i = 0; i < n; ++i){
			string temp;
			getline(f, temp);
			sentences[i].clear(); 
			sentences[i] = temp;
		}
	}

	Graph EG = epsilon_graph_construction(n, parameter);
	Graph T = Discovering_Dense_Regions(EG, n, parameter);
	f.close();
	return 0;
}