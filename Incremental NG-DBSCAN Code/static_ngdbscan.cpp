#include "Static/phase2.cpp"
#include "resources_calculation.cpp"

void parameter_decision_for_static(double& xTn, double& xTr, int& k, int& Mmax, int& p, int& iter, double& epsilon, int& Minpts)
{
	cout << "Want to change the default parameters?\nEnter 1 for Yes and 0 for No\n";

	int parameterChange;
	cin >> parameterChange;
	
	iter = 15;
	xTn = 0.001;		// limits number of nodes in NG for termination
	xTr = 0.0001;		// limits number of removed nodes in current iteration in NG
	k = 15;				// represents degree of each node in neighbour graph
	Mmax = 20;			// used to reduce NG in phase-1 to reduce computation
	p = 2;				// limits nodes for which 2 hop distance is calculated in NG
	epsilon = 0.5;		// minimum distance b/w nodes 
	Minpts  = 10; 		// each core node is having degree at least Minpts − 1

	if(parameterChange == 1){
		cout << "Enter Parameters(If you want to keep default value then enter -1\n";
		cout << "Enter x for Tn(Tn = x*n)\n"; 	cin >> xTn; 
		cout << "Enter x for Tr(Tr = x*n)\n"; 	cin >> xTr;
		cout << "Enter k\n"; 					cin >> k;
		cout << "Enter Mmax\n"; 				cin >> Mmax;
		cout << "Enter p\n"; 					cin >> p;
		cout << "Enter iter\n"; 				cin >> iter;
		cout << "Enter epsilon\n"; 				cin >> epsilon;
		cout << "Enter Minpts\n"; 				cin >> Minpts;
	}
}

void save_clusters_info(Graph& G, int flag){
	fstream f;


	string filename = "";
	if(flag)
		filename = "Files/clusters_save1.txt";
	else 
		filename = "Files/clusters_save.txt";

	f.open(filename,ios::out);


	// number of clusters
	f << clusters.size() << "\n";

	for(int i = 0; i < clusters.size(); i++){

		// cluster number and number of points in each cluster
		f << i << " " << clusters[i].size() << '\n';
		
		// each point id in that cluster
		for(auto id : clusters[i]){
			f << id << " ";
		}
		f << "\n";
	}
}

void save_points_info(Graph& G, int flag)
{
	fstream f;
	string filename = "";
	
	if(flag){
		filename = "Files/points_save1.txt";
	}
	else {
		filename = "Files/points_save.txt";
	}
	
	f.open(filename, ios::out);

	f << G.N << " " << dimensions << "\n";

	for(int i = 0; i < G.N; i++){
		f << i << " " << node_from_id[i]->type << " ";
		for(int j = 0; j < dimensions; j++){
			f << fixed << setprecision(3) << coordinates[i][j] << " ";
		}
		f << "\n";
	}
}

void save_epsilon_graph(Graph& G, int flag)
{
	fstream f;
	string filename = "";
	
	if(flag){
		filename = "Files/epsilon_graph_save1.txt";
	}
	else {
		filename = "Files/epsilon_graph_save.txt";
	}

	f.open(filename,ios::out);

	for(int i = 0; i < G.N; i++){
		f << i << " ";
		for(auto u : G.edges[i]){
			f << u << " ";
		}
		f << "\n";
	}
}

void store_add_and_delete_points(map<vector<double>,bool>& to_add, map<vector<double>,bool>& to_delete){
	int tot_points;
	char type;

	fstream f;
	f.open("Files/queries.txt",ios::in);
	if(!f){
		return;	
	} 
	f >> tot_points;
	for(int j = 0; j < tot_points; j++)
	{
		f >> type;
		vector<double> v(dimensions);
		for(int i = 0; i < dimensions; i++){
			f >> v[i];
		}
		if(type == 'A'){
			to_add[v] = 1;
		}
		else {
			to_delete[v] = 1;
		}
	}
}



int main()
{
	Graph G(0);
	fstream f;
	double xTn, xTr, epsilon;
	int k, Mmax, p, iter, Minpts, n;

	// deciding parameters
	parameter_decision_for_static(xTn, xTr, k, Mmax, p, iter, epsilon, Minpts);
	
	f.open("Files/points.txt",ios::in);
	f >> n >> dimensions;
	
	// creating parameter
	Parameters parameter(xTn*n, xTr*n, k, Mmax, p, iter, epsilon, Minpts);
	
	// storing queries points
	map<vector<double>,bool> to_delete, to_add;
	int flag = 0;
	
	cout << "Do you have new data points to add/delete in dataset(0/1)?"; 
	cin >> flag;
	
	if(flag){
		store_add_and_delete_points(to_add, to_delete);
	}

	coordinates.clear();
	int idx = 0;

	// storing initial points
	for(int i = 0; i < n; i++){
		vector<double> v(dimensions);
		for(int j = 0; j < dimensions; j++){
			f >> v[j];
		}
		if(!to_delete.count(v)){
			coordinates.push_back(v);		
			idx++;
		}
	}

	// storing newly added points
	for(auto& it : to_add){
		vector<double> v = it.first;
		if(!to_delete.count(v)){
			coordinates.push_back(v);
			idx++;
		}
	}

	n = idx;

	auto start = chrono::system_clock::now();

	//Main functions to find the clusters
	Graph EG = epsilon_graph_construction(n, parameter);
	Graph T = Discovering_Dense_Regions(EG, n, parameter, G);

	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
	
	cout<<"Virtual Memory Used: "<<getValue_virtual_memory()<<endl;
	cout<<"Physical Memory Used: "<<getValue_physical_memory()<<endl;

	// saving data in files
	save_clusters_info(G, flag);
	save_points_info(G, flag);
	save_epsilon_graph(G, flag);

	return 0;
}