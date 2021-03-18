#include "metrics_calculate.cpp"

void store_in_map(int flag)
{
	fstream f_points;


	string filename = "";

	if(flag){
		filename = "Files/points_save1.txt";
	}
	else {
		filename = "Files/points_save.txt";
	}


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

void store_clusters(int flag)
{
	fstream f_clusters;
	
	string filename = "";

	if(flag){
		filename = "Files/clusters_save1.txt";
	}
	else {
		filename = "Files/clusters_save.txt";
	}

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

void Compactness()
{
	for(int i = 0; i < n_clusters; ++i){
		compactness[i] = calculate_compactness(i);
		cout << compactness[i] << " ";
	}
	cout << "\n";
}

void Separation()
{
	for(int i = 0; i < n_clusters; ++i){
		for(int j = 0; j < n_clusters; ++j){
			separation[i][j] = calculate_separation(i,j);
			cout << separation[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{

	int flag;
	
	cout << "Do you have new data points to add/delete in dataset(0/1)?\n"; 
	cin >> flag;

	store_in_map(flag); 	// store points coordinate in map
	store_clusters(flag);

	compactness.resize(n_clusters,0);
	separation.resize(n_clusters,vector<double>(n_clusters,0));

	cout << "\nPrinting compactness of each cluster: \n";	
	Compactness();

	cout << "\nPrinting separation between (i,j)th clusters: \n";
	Separation();

	return 0;
}