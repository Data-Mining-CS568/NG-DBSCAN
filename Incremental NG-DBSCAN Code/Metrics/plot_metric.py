import matplotlib.pyplot as plt 

def plot_graph():

	# ------ Plot Time --------
	filename0 = "Time/time_new_static.txt"
	filename1 = "Time/time_incr.txt"	
	x0 = []
	y0 = []
	x1 = []
	y1 = []

	with open(filename0) as metric_file:
		for line in metric_file:
			coordinates = line.split()
			x0.append(int(coordinates[0]))
			y0.append(float(coordinates[1]))

	with open(filename1) as metric_file:
		for line in metric_file:
			coordinates = line.split()
			x1.append(int(coordinates[0]))
			y1.append(float(coordinates[1]))

	plot_time = plt.figure(1)			
	plt.plot(x0,y0,label = "Static NG-DBSCAN")
	plt.plot(x1,y1,label = "Incremental NG-DBSCAN")
	plt.xlabel('Number Of Data Points')
	metric = 'Time in seconds'
	plt.ylabel(metric)
	Title = 'Time Plot (Static vs Incremental)'
	plt.title(Title)
	plt.legend(loc ="upper right", prop={"size":8})
	plt.savefig('Plot Images/time_plot.png', dpi = 50, bbox_inches='tight')
	

	# ------ Plot Memory --------
	filename0 = "Memory/memory_new_static.txt"
	filename1 = "Memory/memory_incr.txt"	
	x0 = []
	y0 = []
	z0 = []
	x1 = []
	y1 = []
	z1 = []

	with open(filename0) as metric_file:
		for line in metric_file:
			coordinates = line.split()
			x0.append(int(coordinates[0]))
			y0.append(float(coordinates[1]))
			z0.append(float(coordinates[2]))

	with open(filename1) as metric_file:
		for line in metric_file:
			coordinates = line.split()
			x1.append(int(coordinates[0]))
			y1.append(float(coordinates[1]))
			z1.append(float(coordinates[2]))

	plot_time = plt.figure(2)
	
	# dashed for virtual memory			

	# plt.plot(x0,y0, color = 'blue', linestyle = 'dashed', label = "Virtual Memory Static")
	plt.plot(x0,z0, color = 'blue', label = "Static NG-DBSCAN")
	# plt.plot(x1,y1, color = 'red' , linestyle = 'dashed', label = "Virtual Memory Incremental")
	plt.plot(x1,z1, color = 'red' , label = "Incremental NG-DBSCAN")
	plt.xlabel('Number Of Data Points')
	metric = 'Memory in KB'
	plt.ylabel(metric)
	Title = 'Memory Plot (Static vs Incremental)'
	plt.title(Title)
	plt.legend(loc ="lower right", prop={"size":8})
	plt.savefig('Plot Images/memory_plot.png', dpi = 50, bbox_inches='tight')	

	plt.show()


if __name__ == "__main__":
	plot_graph()
