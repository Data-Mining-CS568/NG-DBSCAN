#include "metrics_calculate.cpp"

void store_in_map(int flag)
{
	fstream f_points;


	string filename = "";

	if(flag){
		filename = "../Files/points_save1.txt";
	}
	else {
		filename = "../Files/points_save.txt";
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
		filename = "../Files/clusters_save1.txt";
	}
	else {
		filename = "../Files/clusters_save.txt";
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

void Compactness(int flag)
{
	for(int i = 0; i < n_clusters; ++i){
		compactness[i] = calculate_compactness(i);
		cout << compactness[i] << " ";
	}
	cout << "\n";


	string filename;
	if(flag){
		filename = "compactness_incr.txt";
	}
	else {
		filename = "compactness_static.txt";
	}


	fstream fout;
	fout.open(filename, ios::out);
	fout<<total_points<<"\n";
	for(int i = 0; i < n_clusters; ++i){
		fout << compactness[i] << " ";
	}
	fout.close();
	return;
}

void Separation(int flag)
{
	for(int i = 0; i < n_clusters; ++i){
		for(int j = 0; j < n_clusters; ++j){
			separation[i][j] = calculate_separation(i,j);
			cout << separation[i][j] << " ";
		}
		cout << "\n";
	}

	string filename;

	if(flag){
		filename = "separation_incr.txt";
	}
	else {
		filename = "separation_static.txt";
	}

	fstream fout;
	fout.open(filename, ios::out);
	fout<<total_points<<"\n";
	for(int i = 0; i < n_clusters; ++i){
		for(int j = 0; j < n_clusters; ++j){
			fout << separation[i][j] << " ";
		}
		fout<<"\n";
	}
	fout.close();
	return;
}


int main(int argc, char* argv[])
{

	
	if(argc < 2) {
		cout<<"Command Line Argument(s) is/are missing\n";
		return 0;
	} 
	
	int flag = 0;
	flag = atoi(argv[1]); //flag == 1, if there are queries to add or delete points

	store_in_map(flag); 	// store points coordinate in map
	store_clusters(flag);

	compactness.resize(n_clusters,0);
	separation.resize(n_clusters,vector<double>(n_clusters,0));

	cout << "\nPrinting compactness of each cluster: \n";	
	Compactness(flag);

	cout << "\nPrinting separation between (i,j)th clusters: \n";
	Separation(flag);

	return 0;
}