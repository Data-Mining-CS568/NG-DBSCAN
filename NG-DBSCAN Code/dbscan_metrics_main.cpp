#include "metrics_calculate.cpp"

int main()
{
	int total_points, dim = 0, n_clusters = 0;

	fstream f;
	f.open("numbered_dbscan_clusters.txt", ios::in);
	map<int, vector<int>> mp;
	f >> total_points;
	for(int i = 0; i < total_points; i++){
		int x;
		f >> x;
		if(x != -1){
			mp[x].push_back(i);
		}
		n_clusters = max(n_clusters,x+1);
	}
	clusters.resize(n_clusters);
	vector<double> compactness(n_clusters);
	vector<vector<double>> separation(n_clusters,vector<double>(n_clusters,0.0));
	
	fstream f1;
	string temp;
	f1.open("points.txt", ios::in);
	f1 >> temp >> total_points >> dim;

	vector<vector<double>> coordinates(total_points,vector<double>(dim));
	for(int i = 0; i < total_points; i++){
		for(int j = 0; j < dim; j++){
			f1 >> coordinates[i][j];
		}
	}
	for(auto it:mp){
		auto v = it.second;
		for(auto x:v){
			clusters[it.first].push_back(coordinates[x]);
		}
	}

	cout << "Printing compactness of ith clusters: \n";	
	for(int i = 0; i < n_clusters; ++i){
		compactness[i] = calculate_compactness(i);
		cout << compactness[i] << " ";
	}
	cout << "\n";

	cout << "Printing separation between (i,j)th clusters: \n";
	for(int i = 0; i < n_clusters; ++i){
		for(int j = 0; j < n_clusters; ++j){
			separation[i][j] = calculate_separation(i,j);
			cout << separation[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}