# NG-DBSCAN

- Inside "NG-DBSCAN Code" folder, all the files to run are present.

# Instructions to run the code

	- First generate the random dataset using dataset_generator.py. It asks for number of points we want in the dataset (use upto 10000 for fast running) and then asks for type of dataset. Running the following command and entering the required inputs will generate required dataset in points.txt file:
		1. python3 dataset_generator.py

	- Now run the main algorithm (NG-DBSCAN) code using the following command: 
		1. Compile: g++ phase2.cpp
		2. Execute: ./a.out
	- It will create clusters.txt which contains all the clusters 

	- Now to plot the clusters (for 2D and 3D dataset), use the following command:
		1. python3 clusters_generator.py 

