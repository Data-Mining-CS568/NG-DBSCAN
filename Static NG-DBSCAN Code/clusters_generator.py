import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

l = []
noise = []

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
			if item == "core\n":
				pass
			elif item == "border\n":
				pass
			else:
				p.append(float(item))
		lst.append(p)
	l.append(lst)

x = input_file.readline()
a = x.split()
noise_p = int(a[0])

for i in range(noise_p):
	x = input_file.readline()
	x = x.split(' ')
	p = []
	for item in x:
		if item == "noise\n":
			noise.append(p)
		else:
			p.append(float(item))

colours = ["green", "blue", "red", "orange", "yellow", "violet", "black", "pink", "grey", "cyan", "dark_green"]
if dimensions == 2:
	fig, ax = plt.subplots()
	i = 0
	for cluster in l:
	    x = []
	    y = []
	    for point in cluster:
	        x.append(point[0])
	        y.append(point[1])
	    plt.scatter(x, y, label = "dots", color = colours[i], marker= ".", s = 100)
	    i = (i + 1) % 11
	for item in noise:
		plt.scatter(item[0], item[1], label = "dots", color = "black", marker = ".", s = 100)

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
