

#Folders
Files = ./Files
Metrics = ./Metrics


metrics = ./Metrics/Compactness ./Metrics/Seperation ./Metrics/Time  ./Metrics/Memory  ./Metrics/CPU
dataset_1 = ./Datasets/Dataset_1/points.txt ./Datasets/Dataset_1/queries.txt

do: clean_metrics clean_files copy execute plot

clean_metrics:
	for metric_i in $(metrics) ;  do \
		rm -f  $$metric_i/*.txt ; \
	done

clean_files:
	rm -f  $(Files)/*.txt
	
copy: $(dataset_1)
	for u in $(dataset_1); do echo $$uu; cp -f $$u $(Files); done

execute: a.out
	./a.out 0 0

a.out: static_ngdbscan.cpp
	g++ static_ngdbscan.cpp

plot: clusters_generator.py
	python3 clusters_generator.py


