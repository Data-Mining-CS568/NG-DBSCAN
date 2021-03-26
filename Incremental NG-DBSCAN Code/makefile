

#Folders
Files = ./Files
Metrics = ./Metrics
Datasets = ./Datasets/Dataset_1 ./Datasets/Dataset_2 
#./Datasets/Dataset_3 ./Datasets/Traffic_Data  

metrics = ./Metrics/Compactness ./Metrics/Seperation ./Metrics/Time  ./Metrics/Memory  ./Metrics/CPU
dataset = ./Datasets/Dataset_1/points.txt ./Datasets/Dataset_1/queries.txt


do: clean_metrics main 

clean_metrics:
	for metric_i in $(metrics) ;  do \
		rm -f  $$metric_i/*.txt ; \
	done

main: 
	for d in $(Datasets) ; do\
		ls $$d/ ;\
		rm -f  $(Files)/*.txt ;\
		cp -f $$d/points.txt  $(Files) ;\
		cp -f $$d/queries.txt  $(Files) ;\
		g++ static_ngdbscan.cpp ;\
		./a.out 0 0 ;\
		python3 clusters_generator.py 0; \
		./a.out 0 1 ;\
		g++ -o ./Metrics/a.out ./Metrics/metrics_main.cpp ;\
		cd ./Metrics && ./a.out 0 && cd ..;\
		python3 clusters_generator.py 1 ;\
		g++ incr_ngdbscan.cpp ;\
		./a.out ;\
		python3 clusters_generator.py 1 ;\
		g++ -o ./Metrics/a.out ./Metrics/metrics_main.cpp ;\
		cd ./Metrics && ./a.out 1  && cd ..;\
	done

# clean_files:
# 	rm -f  $(Files)/*.txt
	
# copy: $(dataset)
# 	for u in $(dataset); do echo $$uu; cp -f $$u $(Files); done

# execute: a.out
# 	./a.out 0 0

# a.out: static_ngdbscan.cpp
# 	g++ static_ngdbscan.cpp

# plot: clusters_generator.py
# 	python3 clusters_generator.py


