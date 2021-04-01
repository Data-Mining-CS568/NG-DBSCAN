#Folders
Files = ./Files
Metrics = ./Metrics
Datasets = ./Datasets/Dataset_1 ./Datasets/Dataset_2 ./Datasets/Dataset_3  ./Datasets/Traffic_Data  

metrics = ./Metrics/Compactness ./Metrics/Seperation ./Metrics/Time  ./Metrics/Memory  ./Metrics/CPU
dataset = ./Datasets/Dataset_1/points.txt ./Datasets/Dataset_1/queries.txt


do: clean_metrics main 

clean_metrics:
	for metric_i in $(metrics) ;  do \
		rm -f  $$metric_i/*.txt ; \
	done

main: 
	for d in $(Datasets) ; do\
		echo " " ;\
		echo "----------------- DATASET FOLDER CONTAINS -----------------------------\n" ;\
		ls $$d/ ;\
		rm -f  $(Files)/*.txt ;\
		cp -f $$d/points.txt  $(Files) ;\
		cp -f $$d/queries.txt  $(Files) ;\
		cp -f $$d/parameters_static  $(Files) ;\
		cp -f $$d/parameters_incr  $(Files) ;\
		echo " " ;\
		echo "----------------- RUNNING STATIC ON OLD DATASET -----------------------\n" ;\
		g++ static_ngdbscan.cpp ;\
		./a.out 1 0 ;\
		echo " "  ;\
		echo "----------------- PLOTTING CLUSTERS -----------------------------------\n" ;\
		python3 clusters_generator.py 0 $$d/Plot_Images/old_static.png ; \
		echo " " ;\
		echo "----------------- RUNNING STATIC ON MODIFIED DATASET ------------------\n" ;\
		./a.out 1 1 ;\
		echo " " ;\
		echo "----------------- CALCULATING METRICS ---------------------------------\n" ;\
		g++ -o ./Metrics/a.out ./Metrics/metrics_main.cpp ;\
		cd ./Metrics && ./a.out 0 && cd ..;\
		echo " " ;\
		echo "----------------- PLOTTING CLUSTERS -----------------------------------\n";\
		python3 clusters_generator.py 1 $$d/Plot_Images/new_static.png ;\
		echo " " ;\
		echo "----------------- RUNNING INCREMENTAL ---------------------------------\n" ;\
		g++ incr_ngdbscan.cpp ;\
		./a.out 1;\
		echo " " ;\
		echo "----------------- PLOTTING CLUSTERS -----------------------------------\n" ;\
		python3 clusters_generator.py 1 $$d/Plot_Images/incr.png;\
		echo " " ;\
		echo "----------------- CALCULATING METRICS ---------------------------------\n"  ;\
		g++ -o ./Metrics/a.out ./Metrics/metrics_main.cpp ;\
		cd ./Metrics && ./a.out 1  && cd ..;\
	done


