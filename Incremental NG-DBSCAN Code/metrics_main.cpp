#include "metrics_calculate.cpp"



void store_in_map(){

	fstream f_points;
	f_points.open("points_save.txt", ios::in);
	int pt_id ,  t = 0 ; 
	string pt_type;  
	
	f_points >> total_points >> dim;
	while(t++<total_points){
		f_points >> pt_id >> pt_type;
		vector<double> v(dim);
		for(int i=0; i<dim; ++i){
			f_points >> v[i];
		}
		mp[pt_id] = v;
	}
	
	f_points.close();
	return;

}



void store_clusters(){

	fstream f_clusters;
	f_clusters.open("clusters_save.txt", ios::in);

	f_clusters >> n_clusters;
	clusters.resize(n_clusters);

	for(int i = 0; i < n_clusters; ++i){
		int size;
		f_clusters >> cluster_id >> size;
		clusters[i].resize(size,vector<double>(dim));
		int pt_id;
		for(int j = 0; j < size; ++j){
			f_clusters >> pt_id;
			if(mp.find(pt_id) != mp.end())
			clusters[i][j] = mp[pt_id];
		}
	}

	return;
}


void Compactness(){

	for(int i = 0; i < n_clusters; ++i){
		compactness[i] = calculate_compactness(i);
		cout << compactness[i] << " ";
	}
	cout << "\n";
}


void Separation(){

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

	store_in_map(); //store points coordinate in map
	store_clusters();

	compactness.resize(n_clusters,0);
	separation.resize(n_clusters,vector<double>(n_clusters,0));


	cout << "\n Printing compactness of each cluster: \n";	
	Compactness();

	cout << "\n Printing separation between (i,j)th clusters: \n";
	Separation();

	return 0;
}