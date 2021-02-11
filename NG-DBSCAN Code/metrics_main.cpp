#include "metrics_calculate.cpp"

int main()
{
	int total_points, dim = 0, n_clusters;

	fstream f;
	f.open("clusters.txt", ios::in);

	f >> n_clusters >> dim;
	clusters.resize(n_clusters);

	vector<double> compactness(n_clusters);
	vector<vector<double>> similarity(n_clusters,vector<double>(n_clusters,0));

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

	cout << "Printing Compactness Of The Clusters: \n";	
	for(int i = 0; i < n_clusters; ++i){
		compactness[i] = calculate_compactness(i);
		cout << compactness[i] << " ";
	}
	cout << "\n";

	cout << "Printing Similarity Of The Clusters: \n";
	for(int i = 0; i < n_clusters; ++i){
		for(int j = 0; j < n_clusters; ++j){
			similarity[i][j] = calculate_similarity(i,j);
			cout << similarity[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "Printing recall: \n";
	cout << calculate_recall() << '\n';
	f.close();
	return 0;
}