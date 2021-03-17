#include <bits/stdc++.h>
using namespace std;

int total_points, dim, n_clusters, cluster_id;
map<int, vector<double>> mp;
vector<vector<vector<double>>> clusters;
vector<double> compactness;
vector<vector<double>> separation;



void print(vector<double> &d){
	for(int i = 0; i < d.size(); ++i){
		cout << d[i] << " ";
	}
	cout << "\n";
}


// ------------ Calculating Compactness ------------ 
double calculate_compactness(int n)
{
	double ans = 0.0; 
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







double calculate_recall()
{
	int n_clusters, dim, n_points, count = 0;
	string type;
	double epsilon;
	map<int, int> mp;
	map<int, vector<double>> um;

	fstream f,p;
	f.open("numbered_clusters.txt", ios::in);
	p.open("points.txt", ios::in);
	
	p >> type >> n_points >> dim;
	for(int i = 0; i < n_points; i++){
		vector<double> v;
		for(int j = 0; j < dim; j++){
			double x;
			cin >> x;
			v.push_back(x);
		}
		um[i] = v;
	}

	f >> n_clusters >> epsilon;
	for(int i = 0; i < n_clusters; i++){
		int size;
		f >> size;
		for(int j = 0; j < size; j++){
			int point_number;
			f >> point_number;
			mp[point_number] = i;
		}
	}

	for(int i = 0; i < min((int)mp.size(), 10000); i++){
		int point_number1 = rand() % mp.size();
		int point_number2 = rand() % mp.size();
		if(distance(um[point_number1],um[point_number2]) <= epsilon){
			if(mp[point_number1] == mp[point_number2]){
				count++;
			}
		}
		else {
			if(mp[point_number1] != mp[point_number2]){
				count++;
			}
		}
	}
	return (double)count/(int)mp.size();
}