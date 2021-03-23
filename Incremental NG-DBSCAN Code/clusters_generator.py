import sys
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d


argc = len(sys.argv)
flag = 0
if argc < 2:
	print("Command Line Argument Is Missing, Taking 0 As Default Argument:")
else:
	flag = int(sys.argv[1]) #1 is argument when we have queries to add and delete points

l = []
noise = []

filename_p = ""
filename_c = ""
if flag == 0:
	filename_p = "Files/points_save.txt"
	filename_c = "Files/clusters_save.txt"
else:
	filename_p = "Files/points_save1.txt"
	filename_c = "Files/clusters_save1.txt"


points_file = open(filename_p, "r")
x = points_file.readline()
a = x.split()
n = int(a[0])			 # number of points
dimension = int(a[1]) 	 # dimension of points

points = {}
points_type = {}
for i in range(n):
	lst = []
	x = points_file.readline()
	a = x.split(' ')
	pt_id = int(a[0])
	pt_type = a[1]
	points_type[pt_id] = pt_type
	for it in range(2, dimension+2):
		lst.append(float(a[it]))
	points[pt_id] = lst 
	if pt_type == "noise":
		noise.append(points[pt_id])

cluster_file = open(filename_c,"r")
x = cluster_file.readline()
a = x.split()
n = int(a[0]) 			# number of clusters

for i in range(n):
	lst = []
	x = cluster_file.readline()
	a = x.split()
	cluster_id = int(a[0])
	m = int(a[1]) 		# number of points in cluster i
	x = cluster_file.readline()
	points_id = x.split(' ')
	for i in range(m):
		pt_id = int(points_id[i])
		pt_type = points_type[pt_id]
		pt_coordinates = points[pt_id]
		if pt_type != "noise":
			lst.append(pt_coordinates)
	l.append(lst)

colours = ["green", "blue", "red", "orange", "yellow", "violet", "black", "pink", "grey", "cyan", "dark_green"]

if dimension == 2:
	fig, ax = plt.subplots()
	i = 0
	for cluster in l:
	    x = []
	    y = []
	    for point in cluster:
	        x.append(point[0])
	        y.append(point[1])
	    plt.scatter(x, y, label = "dots", color = colours[i], marker= ".", s = 50)
	    i = (i + 1) % 11
	for item in noise:
		plt.scatter(item[0], item[1], label = "dots", color = "black", marker = ".", s = 50)

elif dimension == 3:
	ax = plt.axes(projection='3d')
	i = 0
	for cluster in l:
	    x = []
	    y = []
	    z = []
	    for point in cluster:
	        x.append(point[0])
	        y.append(point[1])
	        z.append(point[2])
	    ax.scatter3D(x, y, z, zdir='z', s = 30, c = colours[i], marker= ".")
	    i = (i + 1) % 11
	for item in noise:
		ax.scatter3D(item[0], item[1], item[2], zdir='z', s = 30, c = "black", marker = ".")

# x-axis label 
plt.xlabel('x - axis') 

# frequency label 
plt.ylabel('y - axis') 

# plot title 
plt.title('Clusters plot!') 

# function to show the plot 
plt.show()
