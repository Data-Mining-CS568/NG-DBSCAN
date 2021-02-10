
double jaroDistance(string &a, string &b){

	if(a==b) return 1.0;

	int lena = a.length();
	int lenb = b.length();

	if(lena == 0 || lenb == 0){
		return 0.0;
	}

	//max dis for matching
	int max_dis = floor(max(lena, lenb)/2)-1;

	//count of matches
	int match = 0;

	vector<bool> hash_a(lena, false), hash_b(lenb, false);

	for(int i=0;i<lena;++i){

		for(int j = max(0, i-max_dis); j < min(lenb, i+max_dis+1); ++j){

			if(a[i] == b[j] && hash_b[j] == false){
				hash_b[j] = true;
				hash_a[i] = true;
				match++;
				break;
			}

		}
	}

	// If there is no match
	if(match == 0) return 0.0;

	//Number of transposition
	double t = 0;
	int point =0;

	// Count number of occurances 
    // where two characters match but 
    // there is a third matched character 
    // in between the indices 
    for (int i = 0; i < lena; i++) 
        if (hash_a[i]) { 
  
            // Find the next matched character 
            // in second string 
            while (hash_b[point] == 0) 
                point++; 
  
            if (a[i] != b[point++]) 
                t++; 
        } 
  
    t /= 2; 


    return (
    		((double)match)/((double)lena) + 

    		((double)match)/((double)lenb) + 

    		((double)match - t)/((double)match)

    		)/3.0;


}

double jaro_winkler(string &a, string &b){

	double jaro_dis = jaroDistance(a,b);

	//if jaro distance is above a threshold
	//then jaro_winkler = 1 - (jaro_distance + scaling_factor*prefix*(1-jaro_distance))
	//else jaro_winkler = 1 - jaro_distance
	double jaro_winklerDis = 0.0, scaling_factor = 0.1;
	if(jaro_dis>0.7){

		int prefix = 0;
		for(int i=0; i<min(a.length(), b.length()); ++i){
			if(a[i]==b[i]) prefix++;
			else break;
		}
		//cout<<"Here";
		prefix = min(4, prefix);
		jaro_winklerDis = 1 - (jaro_dis + scaling_factor*prefix*(1-jaro_dis));
	}
	else jaro_winklerDis = 1-jaro_dis;

	return jaro_winklerDis;


}


/*int main(){

	string s1 = "TRATE", s2 = "TRACE"; 
  
    // Print jaro Similarity of two strings 
    cout << jaroDistance(s1, s2) << endl; 
    cout << jaro_winkler(s1, s2) << endl; 
  
  
    return 0; 
}*/