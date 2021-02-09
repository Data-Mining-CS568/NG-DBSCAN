import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

l = []
noise = []
core = []
border = []

input_file = open("clusters.txt","r")
x = input_file.readline()
a = x.split()
n = int(a[0])
dimensions = int(a[1])

for i in range(n):
	lst = []
	x = input_file.readline()
	a = x.split()
	m = int(a[0])
	for j in range(m):
		x = input_file.readline()
		x = x.split(' ')
		p = []
		for item in x:
			if item == "noise\n":
				noise.append(item)
			elif item == "core\n":
				core.append(item)
			elif item == "border\n":
				border.append(item)
			else:
				p.append(float(item))
		lst.append(p)
	l.append(lst)

colours = ["green", "blue", "red", "orange", "yellow", "violet", "black", "pink", "grey", "cyan", "black", "dark_green"]

if dimensions == 2:
	i = 0
	for cluster in l:
	    x = []
	    y = []
	    for point in cluster:
	        x.append(point[0])
	        y.append(point[1])
	    plt.scatter(x, y, label = "dots", color = colours[i], marker= ".", s = 30)
	    i = (i + 1) % 12

elif dimensions == 3:
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
	    i = (i + 1) % 12

# x-axis label 
plt.xlabel('x - axis') 

# frequency label 
plt.ylabel('y - axis') 

# plot title 
plt.title('Clusters plot!') 

# function to show the plot 
plt.show()
