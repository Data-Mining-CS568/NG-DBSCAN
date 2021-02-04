import math
import matplotlib.pyplot as plt

l = []
noise = []
input_file = open("clusters.txt","r")
x = input_file.readline()
a = x.split()
n = int(a[0])

for i in range(n):
	lst = []
	x = input_file.readline()
	a = x.split()
	m = int(a[0])            
	for j in range(m):
		x = input_file.readline()
		x = x.split(' ')
		p = [float(x[0]),float(x[1])]
		if(x[2] == "noise\n"):
			noise.append(p)
		else:
			lst.append(p)
	l.append(lst)

clr = ["green","blue","red","orange","yellow","violet","black","pink"]
i = 0
for cluster in l:
    x = []
    y = []
    for point in cluster:
        x.append(point[0])
        y.append(point[1])

    # plotting points as a scatter plot 
    plt.scatter(x, y, label = "stars", color = clr[i], marker= "*", s = 30)
    i = (i + 1) % 6
    a = []
    b = []
    for point in noise:
        a.append(point[0])
        b.append(point[1])
    plt.scatter(a, b, label = "stars", color = "lightblue", marker= "*", s = 30)

# x-axis label 
plt.xlabel('x - axis') 

# frequency label 
plt.ylabel('y - axis') 

# plot title 
plt.title('Clusters plot!') 

# function to show the plot 
plt.show()