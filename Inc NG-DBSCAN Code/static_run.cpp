#include "phase2.cpp"

void parameter_decision_for_static(double& xTn, double& xTr, int& k, int& Mmax, int& p, double& epsilon, int& Minpts)
{
	cout << "Want to change the default parameters?\nEnter 1 for Yes and 0 for No\n";

	int parameterChange;
	cin >> parameterChange;
	
	xTn = 0.001;		// limits number of nodes in NG for termination
	xTr = 0.0001;		// limits number of removed nodes in current iteration in NG
	k = 20;				// represents degree of each node in neighbour graph
	Mmax = 20;			// used to reduce NG in phase-1 to reduce computation
	p = 2;				// limits nodes for which 2 hop distance is calculated in NG
	iter = 10;
	epsilon = 1.0;		// minimum distance b/w nodes 
	Minpts  = 10; 		// each core node is having degree at least Minpts − 1

	if(parameterChange == 1){
		cout << "Enter Parameters(If you want to keep default value then enter -1\n";
		cout << "Enter x for Tn(Tn = x*n)\n"; 	cin >> xTn; 
		cout << "Enter x for Tr(Tr = x*n)\n"; 	cin >> xTr;
		cout << "Enter k\n"; 					cin >> k;
		cout << "Enter Mmax\n"; 				cin >> Mmax;
		cout << "Enter p\n"; 					cin >> p;
		cout << "Enter iter\n"; 				cin >> iter;
		cout << "Enter epsilon\n"; 				cin >> epsilon;
		cout << "Enter Minpts\n"; 				cin >> Minpts;
	}
}



int main()
{
	double xTn, xTr, epsilon;
	int k, Mmax, p, iter, Minpts;
	parameter_decision_for_static(xTn, xTr, k, Mmax, p, iter, epsilon, Minpts);
	
	fstream f;
	f.open("points.txt",ios::in);
	
	int n; 
	f >> n >> dimensions;
	
	Parameters parameter(xTn*n, xTr*n, k, Mmax, p, iter, epsilon, Minpts);
	
	coordinates.resize(n, vector<double>(dimensions));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < dimensions; j++){
			f >> coordinates[i][j];
		}
	}
	f.close();

	Graph EG = epsilon_graph_construction(n, parameter);
	Graph T = Discovering_Dense_Regions(EG, n, parameter);
	
	return 0;
}