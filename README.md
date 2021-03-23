# About Static NG-DBSCAN

- Inside "Static NG-DBSCAN Code" folder, all the files to run are present.
- While plotting 2 and 3 dimensional datasets, try changing epsilon values to get better cluster quality.
- Images folder contains some of the clusters generated. 
- For synthetic datasets, we used moon, blob and circular datasets.

### Instructions to run the Static NG-DBSCAN Code:

<details>
<summary> Generate Synthetic Datasets </summary>
	 
	- Use dataset_generator.py. 

	- Enter number of points (or number of sentences in case of text dataset) and type of dataset.(use upto 10000 for fast running).

	- Run the following command and the dataset will be generated in points.txt file:
		- python3 dataset_generator.py

</details>

<details>
<summary> Run the Static NG-DBSCAN Algorithm </summary>

	- Run the main algorithm (NG-DBSCAN) using command: 
		- g++ phase2.cpp
		- ./a.out
	
	- It will create clusters.txt which contains all the clusters. 

	- Now to plot the clusters (for 2 and 3 dimensional datasets), use the following command:
		- python3 clusters_generator.py 

</details>

<details>
<summary> Calculate metrics and compare results of NG-DBSCAN and DBSCAN </summary>

	- We calculated these NG-DBSCAN metrics for comparison with DBSCAN: compactness, separation, recall. Use the following command for calculating NG-DBSCAN metrics. 
		- g++ metrics_main.cpp
		- ./a.out

	- Run DBSCAN algorithm (for comparison with NG-DBSCAN) over points.txt using dbscan_code.py using the following command:
		- python3 dbscan_code.py

	- We calculated the DBSCAN metrics: compactness, separation, recall. Use the following command for calculating DBSCAN metrics.
		- g++ dbscan_metrics_main.cpp
		- ./a.out

	- Using this we can compare between DBSCAN and NG-DBSCAN.
	
</details>

<details>
<summary> Code Files for Static NG-DBSCAN </summary>
	
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
  
</details>

#### Clusters Generated With 3-D Points
![Image of 3D Plot](https://github.com/Data-Mining-CS568/NG-DBSCAN/blob/main/Report%20Images/3d_dataset.png)
	


# About Incremental NG-DBSCAN

- Inside "Incremental NG-DBSCAN Code" folder, all the files to run are present.
- Try to tune the parameters while running on different datasets to get more accuracy.
- Inside each dataset of 2 dimension, images of cluster plotting are also present. 
- For synthetic datasets, we used moon, blob and circular datasets.

### Instructions to run the Incremental NG-DBSCAN Code:

<details>
<summary> Generate and Plot the already existing dataset (which is considered as database in real life) </summary>
	
	- First put the points.txt and queries.txt for the dataset you want the algorithm to run on.

	- Then first run the static version without considering the queries.txt using the following command. <first_argument> = 0 if you want to change the value of parameters and 1 otherwise. Second command line argument will be 0 here. 
		- g++ static_ngdbscan.cpp 
		- ./a.out <first_argument> 0

	- It will create old_epsilon_graph.txt, old_clusters.txt, old_points.txt and this will constitute our database.

	- To plot the clusters for the points present in database, we will run the following command:
		- python3 clusters_generator.py 0

</details>

<details>
<summary> Run and Plot the Incremental NG-DBSCAN algorithm over the existing dataset </summary>

	- Now to run the queries.txt over incremental version, use the following command. 
		- g++ incr_ngdbscan.cpp 
		- ./a.out 
	
	- After this, new_epsilon_graph.txt, new_clusters.txt, new_points.txt will be generated.

	- To plot the clusters for the points after considering queries.txt, we will run the following command:
		- python3 clusters_generator.py 1

</details>

<details>
<summary> Run and Plot the Static NG-DBSCAN algorithm over the existing dataset (for comparison with incremental version) </summary>

	- Now to run the queries.txt over incremental version (for comparison with incremental version), use the following command. <first_argument> = 0 if you want to change the value of parameters and 1 otherwise. Second command line argument will be 1 here. 
		- g++ static_ngdbscan.cpp  
		- ./a.out <first_argument> 1

	- After this, new_epsilon_graph.txt, new_clusters.txt, new_points.txt will be generated.

	- To plot the clusters for the points after considering queries.txt, we will run the following command:
		- python3 clusters_generator.py 1

</details>
	 
<details>
<summary> Calculate metrics on Incremental and Static Versions for comparison </summary>
	
	- To use metrics on the database (only considering points.txt), we will use the following command:
		- g++ metrics_main.cpp 
		- ./a.out 0

	- To use metrics on the updated dataset (after considering queries.txt), we will use the following command:
		- g++ metrics_main.cpp 
		- ./a.out 1

</details>

<details>
<summary> Code Files for Incremental NG-DBSCAN </summary>
	
	- incr_classes.h - contains all used classes in the incremental NG-DBSCAN algorithm.

	- incr_ngdbscan.cpp - contains the whole incremental NG-DBSCAN algorithm code.

	- static_ngdbscan.cpp - contains the main function for running the static NG-DBSCAN code while comparing with static NG-DBSCAN algorithm.

	- metrics_main.cpp - main method to calculate metrics for incremental and static NG-DBSCAN.

	- metrics_functions.cpp - contains all the main functions to calculate metrics.

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

</details>

