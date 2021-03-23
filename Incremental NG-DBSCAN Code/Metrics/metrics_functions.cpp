#include <bits/stdc++.h>
using namespace std;

int total_points, dim, n_clusters, cluster_id;
map<int, vector<double>> mp;
vector<vector<vector<double>>> clusters;
vector<double> compactness;
vector<vector<double>> separation;

// ---------------------------------------------- PRINTING A VECTOR ----------------------------------------------------------------------

void print(vector<double> &d)
{
	for(int i = 0; i < d.size(); ++i){
		cout << d[i] << " ";
	}
	cout << "\n";
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// --------------------------------------------- CALCULATING COMPACTNESS -----------------------------------------------------------------

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
			if(temp2 == 0 || temp3 == 0){
				continue;	
			} 
			double temp4 = temp1/(sqrt(temp2)*sqrt(temp3));
			ans += temp4;
			cnt++;
		}
	}
	return ans/cnt;
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
		filename = "Metrics/Compactness/compactness_incr.txt";
	}
	else {
		filename = "Metrics/Compactness/compactness_static.txt";
	}
	fstream fout;
	fout.open(filename, ios::out);
	fout << total_points << "\n";
	for(int i = 0; i < n_clusters; ++i){
		fout << compactness[i] << " ";
	}
	fout.close();
}

// ---------------------------------------------------------------------------------------------------------------------------------------


// ----------------------------------------- CALCULATING SEPERATION BETWEEN DIFFERENT CLUSTERS -------------------------------------------

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
			if(temp2 == 0 || temp3 == 0){
				continue;	
			} 
			double temp4 = temp1/(sqrt(temp2)*sqrt(temp3));
			ans += temp4;
			cnt++;
		}
	}
	return ans/cnt;
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
		filename = "Metrics/Seperation/separation_incr.txt";
	}
	else {
		filename = "Metrics/Seperation/separation_static.txt";
	}

	fstream fout;
	fout.open(filename, ios::out);
	fout << total_points << "\n";
	for(int i = 0; i < n_clusters; ++i){
		for(int j = 0; j < n_clusters; ++j){
			fout << separation[i][j] << " ";
		}
		fout << "\n";
	}
	fout.close();
}

// ----------------------------------- CALCULATING DISTANCE BETWEEN 2 POINTS --------------------------------------------------------------

double distance(vector<double> a, vector<double> b)
{
	double ans = 0;
	for(int j = 0; j < a.size(); j++){
		ans += (a[j] - b[j]) * (a[j] - b[j]);
	}
	return sqrt(ans);
}

// ----------------------------------------------------------------------------------------------------------------------------------------
