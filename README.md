# About Static NG-DBSCAN

- Inside "Static NG-DBSCAN Code" folder, all the files to run are present.
- While plotting 2-D and 3-D datasets, try changing epsilon values to get better cluster quality.
- Images folder contains some of the clusters generated. 
- For synthetic datasets, we used moon, blob and circular datasets.

- Instructions to run the Static NG-DBSCAN Code:

	- First generate the random dataset using dataset_generator.py. 

	- It asks for number of points(or number of sentences in case of text dataset) we want in the dataset (use upto 10000 for fast running) and then asks for type of dataset. 

	- Running the following command and entering the required inputs will generate required dataset in points.txt file:
		- python3 dataset_generator.py

	- Now run the main algorithm (NG-DBSCAN) code using the following command: 
		- g++ phase2.cpp
		- ./a.out
	- It will create clusters.txt which contains all the clusters. 

	- Now to plot the clusters (for 2D and 3D dataset), use the following command:
		- python3 clusters_generator.py 

	- We calculated the NG-DBSCAN metrics for comparison with DBSCAN: compactness, separation, recall 
		- g++ metrics_main.cpp
		- ./a.out

	- Ran DBSCAN algorithm (for comparison with NG-DBSCAN) over points.txt using dbscan_code.py using the following command:
		- python3 dbscan_code.py

	- We calculated the DBSCAN metrics: compactness, separation, recall 
		- g++ dbscan_metrics_main.cpp
		- ./a.out
	- Using this we can compare between DBSCAN and NG-DCSCAN.

- Code Files for Static NG-DBSCAN 

	- classes.h - contains all the used classes in the algorithm.

	- phase1.cpp - contains the phase-1 code which will be used to create epsilon graph.

	- phase2.cpp - used to create the propagation tree and list of clusters.

	- metric_main.cpp - main method to calculate metrics for NG-DBSCAN.

	- metric_calculate.cpp - contains Functions to contain metrics.

	- dbscan_metrics_main.cpp - main method to calculate metrics for DBSCAN.

	- jaro_winkler_distance.cpp: it calculates Jaro Winkler Distance between two strings.

	- dbscan_code.py - main method to create the DBSCAN clusters and numbered_dbscan_clusters.txt file.

	- dataset_generator.py - contains the python code to generate the random points.

	- clusters_generator.py - plots the clusters in 2-dimension in different colours using clusters. 

	- epsilon_graph.txt - represents the epsilon graph used in the algorithm.

	- propagation_tree.txt - represents the propagation tree generated by the algorithm.

	- points.txt - contains the randomly generated points used as input in phase2.cpp.

	- clusters.txt - contains the lists of list of clusters.

	- numbered_clusters.txt - contains the lists of list of clusters, where elements of list are node number instead of data values.

	- numbered_dbscan_clusters.txt - contains all the points of DBSCAN, where ith point represents in which cluster number it lies.

	- health_twitter.txt & sms_spam_collection.txt: text datasets


# About Incremental NG-DBSCAN

- Inside "Incremental NG-DBSCAN Code" folder, all the files to run are present.
- Try to tune the parameters while running on different datasets to get more accuracy.
- Inside each dataset of 2 dimension, images of cluster plotting are also present. 
- For synthetic datasets, we used moon, blob and circular datasets.

- Instructions to run the Incremental NG-DBSCAN Code:

	- First put the points.txt and queries.txt for the dataset you want the algorithm to run on.

	- Then first run the static version without considering the queries.txt using the following command:
		- g++ static_ngdbscan.cpp 
		- ./a.out 0
	- It will create old_epsilon_graph.txt, old_clusters.txt, old_points.txt and this will constitute our database.

	- To plot the clusters for the points present in database, we will run the following command:
		- python3 clusters_generator.py 0

	- Now to run the queries.txt over incremental version, use the following command. 
		- g++ incr_ngdbscan.cpp 
		- ./a.out 
	- After this, new_epsilon_graph.txt, new_clusters.txt, new_points.txt will be generated.

	- To plot the clusters for the points after considering queries.txt, we will run the following command:
		- python3 clusters_generator.py 1

	- Now to run the queries.txt over incremental version (for comparison with incremental version), use the following command. 
		- g++ static_ngdbscan.cpp  
		- ./a.out 1
	- After this, new_epsilon_graph.txt, new_clusters.txt, new_points.txt will be generated.

	- To plot the clusters for the points after considering queries.txt, we will run the following command:
		- python3 clusters_generator.py 1 

	- To use metrics on the database (only considering points.txt), we will use the following command:
		- g++ metrics_main.cpp 
		- ./a.out 0

	- To use metrics on the updated dataset (after considering queries.txt), we will use the following command:
		- g++ metrics_main.cpp 
		- ./a.out 1	 

- Code Files for Incremental NG-DBSCAN:
	
	- incr_classes.h - contains all used classes in the incremental NG-DBSCAN algorithm.

	- incr_ngdbscan.cpp - contains the whole incremental NG-DBSCAN algorithm code.

	- static_ngdbscan.cpp - contains the main function for running the static NG-DBSCAN code while comparing with static NG-DBSCAN algorithm.

	- metric_main.cpp - main method to calculate metrics for incremental and static NG-DBSCAN.

	- metric_calculate.cpp - contains all the main functions to calculate metrics.

	- resources_calculation.cpp - contains the main functions to calculate time, memory, CPU usage etc for static and incremental versions.

	- clusters_generator.py - used to plot the clusters of static and incremental NG-DBSCAN versions.
	
	- points.txt - contains the database points (clusters would be formed using these points in real scenario) used as input in static_ngdbscan.cpp and incr_ngdbscan.cpp.

	- queries.txt - contains the points to add or delete from the existing dataset (points.txt).

	- old_epsilon_graph.txt - contains the epsilon graph for the old dataset.

	- new_epsilon_graph.txt - contains the epsilon graph for the updated dataset (after considering queries.txt).

	- old_points.txt - contains the information of each point in the old dataset.

	- new_points.txt - contains the information of each point in the updated dataset (after considering queries.txt).

	- old_clusters.txt - contains the clusters for the old dataset.

	- new_clusters.txt - contains the clusters for the new dataset (after considering queries.txt).
