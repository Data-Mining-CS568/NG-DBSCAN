#include "metrics_functions.cpp"

// -------------------------------------------- STORING IN MAP -------------------------------------------------------------------------

void store_in_map()
{
	fstream f_points;
	string filename = "";

	filename = "../Files/new_points.txt";
	f_points.open(filename, ios::in);
	int pt_id, t = 0; 
	string pt_type;	
	f_points >> total_points >> dim;
	
	while(t++ < total_points)
	{
		f_points >> pt_id >> pt_type;
		vector<double> v(dim);
		for(int i = 0; i < dim; ++i){
			f_points >> v[i];
		}
		mp[pt_id] = v;
	}
	f_points.close();
}

// --------------------------------------------------------------------------------------------------------------------------------------


// --------------------------------------------- STORE CLUSTERS -------------------------------------------------------------------------

void store_clusters()
{
	fstream f_clusters;
	string filename = "";

	filename = "../Files/new_clusters.txt";
	f_clusters.open(filename, ios::in);
	f_clusters >> n_clusters;
	clusters.resize(n_clusters);

	for(int i = 0; i < n_clusters; ++i)
	{
		int size;
		f_clusters >> cluster_id >> size;
		clusters[i].resize(size);
		int pt_id; 
		for(int j = 0; j < size; ++j){
			f_clusters >> pt_id;
			if(mp.find(pt_id) != mp.end()){
				clusters[i][j] = mp[pt_id];
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ---------------------------------------------- MAIN FUNCTION --------------------------------------------------------------------------

int main(int argc, char* argv[])
{	
	if(argc < 2){
		cout << "Command Line Argument(s) is/are missing\n";
		return 0;
	} 
	
	int flag = 0;
	flag = atoi(argv[1]); 	// flag == 1, if we want to calculate for incremental version

	store_in_map(); 	// store points coordinate in map
	store_clusters();

	compactness.resize(n_clusters,0);
	separation.resize(n_clusters,vector<double>(n_clusters,0));

	Compactness(flag);
	Separation(flag);
	return 0;
}

// ----------------------------------------------------------------------------------------------------------------------------------------