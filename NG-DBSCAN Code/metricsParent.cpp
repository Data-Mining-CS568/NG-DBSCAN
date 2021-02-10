#include "metricsCalculation.cpp"


int main(){
	
	int dim = 0;
	
	fstream f;


	f.open("clusters.txt", ios::in);
	int n_clusters; f>>n_clusters>>dim;
	//cout<<n_clusters<<dim;
	clusters.resize(n_clusters);

	vector<double> compactness(n_clusters);
	vector<vector<double>> similarity(n_clusters, vector<double>(n_clusters, 0));

	//Storing Clusters in an array
	for(int i=0;i<n_clusters;++i){

		int size;
		f>>size;
		clusters[i].resize(size, vector<double>(dim));
		for(int j=0;j<size;++j){
			
			for(int k=0;k<dim;++k){
				
				f>>clusters[i][j][k];
	//			cout<<clusters[i][j][k]<<" ";			
			}
			
			string temp;
			f>>temp;
	//		cout<<temp<<"*"<<endl;
		}

	}



	cout<<"Printing Compactness Of The Clusters: \n";	
	for(int i=0;i<n_clusters;++i){
		compactness[i] = calculateCompactness(i);
		cout<<compactness[i]<<" ";
	}
	cout<<endl;



	cout<<"Printing Similarity Of The Clusters: \n";

	for(int i=0;i<n_clusters;++i){
		for(int j= 0; j<n_clusters; ++j){
			similarity[i][j] = calculateSimilarity(i,j);
			cout<<similarity[i][j]<<"    ";
		}
		cout<<endl;
	}


	f.close();

	return 0;
}