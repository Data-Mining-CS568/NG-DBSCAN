#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<double>>> clusters;

void print(vector<double> &d){
	for(int i = 0; i < d.size(); ++i){
		cout << d[i] << " ";
	}
	cout << "\n";
}

double calculate_compactness(int n)
{
	double ans = 0; 
	int cnt = 0;
	int size = clusters[n].size();
	for(int i = 0; i < size; ++i){
		for(int j = i+1; j < size; ++j){
			double temp1 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[n][j].begin(), 0.0);
			double temp2 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[n][i].begin(), 0.0);
			double temp3 = inner_product(clusters[n][j].begin(), clusters[n][j].end(), clusters[n][j].begin(), 0.0);
			double temp4 = temp1/(sqrtf(temp2)*sqrtf(temp3));
			ans += temp4;
			cnt++;
		}
	}
	return ans/cnt;
}

// calculates separation between different clusters
double calculate_separation(int n, int m)
{
	double ans = 0; 
	int cnt = 0;
	int sizen = clusters[n].size();
	int sizem = clusters[m].size();
	for(int i = 0; i < sizen; ++i){
		for(int j = 0; j < sizem; ++j){
			double temp1 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[m][j].begin(), 0.0);
			double temp2 = inner_product(clusters[n][i].begin(), clusters[n][i].end(), clusters[n][i].begin(), 0.0);
			double temp3 = inner_product(clusters[m][j].begin(), clusters[m][j].end(), clusters[m][j].begin(), 0.0);
			double temp4 = temp1/(sqrtf(temp2)*sqrtf(temp3));
			ans += temp4;
			cnt++;
		}
	}
	return ans/cnt;
}

double distance(vector<double> a, vector<double> b){
	double ans = 0;
	for(int j = 0; j < a.size(); j++){
		ans += (a[j] - b[j]) * (a[j] - b[j]);
	}
	return sqrtf(ans);
}
