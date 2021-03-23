#include "Static/phase2.cpp"
#include "Metrics/resources_calculation.cpp"

// --------------------------------- DECIDING PARAMETERS ---------------------------------------------------------------------------------

void parameter_decision_for_static(double& xTn, double& xTr, int& k, int& Mmax, int& p, int& iter, double& epsilon, int& Minpts, int parameterChange)
{
	// Change the default parameters if parameterChange == 1
	
	iter = 15;
	xTn = 0.001;		// limits number of nodes in NG for termination
	xTr = 0.0001;		// limits number of removed nodes in current iteration in NG
	k = 15;				// represents degree of each node in neighbour graph
	Mmax = 20;			// used to reduce NG in phase-1 to reduce computation
	p = 2;				// limits nodes for which 2 hop distance is calculated in NG
	epsilon = 0.5;		// minimum distance b/w nodes 
	Minpts  = 10; 		// each core node is having degree at least Minpts − 1

	if(parameterChange == 1){
		cout << "Enter Parameters (If you want to keep default value then enter -1)\n";
		cout << "Enter x for Tn (Tn = x*n)\n"; 	cin >> xTn; 
		cout << "Enter x for Tr (Tr = x*n)\n"; 	cin >> xTr;
		cout << "Enter k\n"; 					cin >> k;
		cout << "Enter Mmax\n"; 				cin >> Mmax;
		cout << "Enter p\n"; 					cin >> p;
		cout << "Enter iter\n"; 				cin >> iter;
		cout << "Enter epsilon\n"; 				cin >> epsilon;
		cout << "Enter Minpts\n"; 				cin >> Minpts;
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// -------------------------------------------------- SAVING DATA IN FILES ---------------------------------------------------------------

void save_clusters_info(Graph& G, int flag)
{
	fstream f;
	string filename = "";

	if(flag){
		filename = "Files/new_clusters.txt";
	}
	else {
		filename = "Files/old_clusters.txt";
	}
	f.open(filename, ios::out);

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
		filename = "Files/new_points.txt";
	}
	else {
		filename = "Files/old_points.txt";
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
		filename = "Files/new_epsilon_graph.txt";
	}
	else {
		filename = "Files/old_epsilon_graph.txt";
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

void save_data(Graph& G, int flag)
{
	save_clusters_info(G, flag);
	save_points_info(G, flag);
	save_epsilon_graph(G, flag);
}

// --------------------------------------------------------------------------------------------------------------------------------------


// ----------------------------------------- STORING POINTS TO ADD AND DELETE IN MAPS ---------------------------------------------------

void store_add_and_delete_points(map<vector<double>,bool>& to_add, map<vector<double>,bool>& to_delete)
{
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

// ---------------------------------------------------------------------------------------------------------------------------------------


// --------------------------------------- STORING RESOURCES OF MEMORY AND TIME IN FILES -------------------------------------------------

void resources_usage(Graph & G, chrono::system_clock::time_point start, chrono::system_clock::time_point end, int flag)
{
	chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "Finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << " seconds\n";

	cout << "Virtual Memory Used: " << getValue_virtual_memory() << " KB\n";
	cout << "Physical Memory Used: " << getValue_physical_memory() << " KB\n";

	// Writing Resources Used In Files
	string filename = "";
	if(flag){
		filename = "Metrics/time_new_static.txt";
	}
	else {
		filename = "Metrics/time_old_static.txt";
	}
	fstream fout;
	fout.open(filename, ios::app);
	fout << G.active.size() << " " << elapsed_seconds.count() << "\n";
	fout.close();

	if(flag){
		filename = "Metrics/memory_new_static.txt";
	}
	else {
		filename = "Metrics/memory_old_static.txt";
	}

	fout.open(filename, ios::app);
	fout << G.active.size() << " " << getValue_virtual_memory() << " " << getValue_physical_memory() << "\n";
	fout.close();
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ----------------------------------------- MAIN CALLING FUNCTION -----------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Graph G(0);
	fstream f;
	double xTn, xTr, epsilon;
	int k, Mmax, p, iter, Minpts, n;

	if(argc < 3){
		cout << "Command Line Argument(s) is/are missing\n";
		return 0;
	} 

	// deciding parameters
	int parameterChange = atoi(argv[1]);
	parameter_decision_for_static(xTn, xTr, k, Mmax, p, iter, epsilon, Minpts, parameterChange);
	
	f.open("Files/points.txt",ios::in);
	f >> n >> dimensions;
	
	// creating parameter
	Parameters parameter(xTn*n, xTr*n, k, Mmax, p, iter, epsilon, Minpts);
	
	// storing queries points
	map<vector<double>,bool> to_delete, to_add;

	int flag = 0;
	flag = atoi(argv[2]); 	// flag == 1, if there are queries to add or delete points
	
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

	// Main functions to find the clusters
	Graph EG = epsilon_graph_construction(n, parameter);
	Graph T = Discovering_Dense_Regions(EG, n, parameter, G);

	auto end = chrono::system_clock::now();

	// calculating and storing time and memory in files
	resources_usage(G, start, end, flag);

	// saving data in files
	save_data(G, flag);

	return 0;
}

// ---------------------------------------------------------------------------------------------------------------------------------------