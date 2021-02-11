# NG-DBSCAN

- Inside "NG-DBSCAN Code" folder, all the files to run are present.

# Instructions to run the code

	- First generate the random dataset using dataset_generator.py. 

	- It asks for number of points(or number of sentences in case of text dataset) we want in the dataset (use upto 10000 for fast running) and then asks for type of dataset. 

	- Running the following command and entering the required inputs will generate required dataset in points.txt file:
		1. python3 dataset_generator.py

	- Now run the main algorithm (NG-DBSCAN) code using the following command: 
		1. Compile: g++ phase2.cpp
		2. Execute: ./a.out
	- It will create clusters.txt which contains all the clusters 

	- Now to plot the clusters (for 2D and 3D dataset), use the following command:
		1. python3 clusters_generator.py 

	- We calculate the metrics for comparison, compactness, separation, recall
		1. Compile: g++ metric_main.cpp
		2. Execute: ./a.out

Note: 1) For 3-D dataset try changing epsilon values to get better cluster quality	




# Code Files  

	- classes.h - contains all the used classes in the algorithm.

	- phase1.cpp - contains the phase-1 code which will be used to create 𝜖-graph.

	- phase2.cpp - used to create the propagation tree and list of clusters.

	- epsilon_graph.txt - represents the epsilon graph used in the algorithm.

	- propagation_tree.txt - represents the propagation tree generated by the algorithm.

	- points.txt - contains the randomly generated points used as input in phase2.cpp.

	- clusters.txt - contains the lists of list of clusters.

	- numbered_clusters.txt - contains the lists of list of clusters, where elements of list are node number instead of data values.

	- dataset_generator.py - contains the python code to generate the random points.

	- clusters_generator.py - plots the clusters in 2-dimension in different colours using clusters.

	- metric_main.cpp - Main method to calculate metrics

	- metric_calculate.cpp - Contains Functions to contain metrics.

	- jaro_winkler_distance.cpp: It calculates Jaro Winkler Distance between two strings

	- health_twitter.txt & sms_spam_collection.txt: Text Datasets 










