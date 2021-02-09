#include<bits/stdc++.h>
using namespace std;

vector<vector<vector<double>>> clusters;

double calculateCompactness(int n){
	double ans = 0; int cnt =0;
	int size = clusters[n].size();
	for(int i=0;i<size;++i){
		for(int j = i+1; j<size; ++j){
			double temp1 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[n][j].begin(), 0);
			double temp2 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[n][i].begin(), 0);
			double temp3 = inner_product(clusters[n][j].begin(), clusters[n][j].end(), clusters[n][j].begin(), 0);
			double temp4 = temp1/(sqrt(temp2)*sqrt(temp3));
			ans += temp4;
			cnt++;
		}
	}

	return (ans/cnt);
}

double calculateSimilarity(int n, int m){
	//calculates similarity between different clusters
	double ans = 0; int cnt =0;
	int sizen = clusters[n].size();
	int sizem = clusters[m].size();

	for(int i=0;i<sizen;++i){
		for(int j = 0; j<sizem; ++j){
			double temp1 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[m][j].begin(), 0);
			double temp2 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[n][i].begin(), 0);
			double temp3 = inner_product(clusters[m][j].begin(), clusters[m][j].end(), clusters[m][j].begin(), 0);
			double temp4 = temp1/(sqrt(temp2)*sqrt(temp3));
			ans += temp4;
			cnt++;
		}
	}

	return (ans/cnt);
}