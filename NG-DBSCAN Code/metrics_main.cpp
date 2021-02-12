#include "metrics_calculate.cpp"

int main()
{
	int total_points, dim = 0, n_clusters;

	fstream f;
	f.open("clusters.txt", ios::in);

	f >> n_clusters >> dim;
	clusters.resize(n_clusters);

	vector<double> compactness(n_clusters);
	vector<vector<double>> separation(n_clusters,vector<double>(n_clusters,0));

	// Storing Clusters in an array
	for(int i = 0; i < n_clusters; ++i){
		int size;
		f >> size;
		clusters[i].resize(size,vector<double>(dim));
		for(int j = 0; j < size; ++j){
			for(int k = 0; k < dim; ++k){
				f >> clusters[i][j][k];	
			}
			string temp;
			f >> temp;
		}
	}

	cout << "Printing compactness of each cluster: \n";	
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
	f.close();
	return 0;
}