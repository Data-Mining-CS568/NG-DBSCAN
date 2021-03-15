from sklearn.datasets import make_moons, make_blobs, make_circles
from matplotlib import pyplot
import matplotlib.pyplot as plt
from pandas import DataFrame
import numpy as np
from sklearn.cluster import DBSCAN
from sklearn import metrics
from sklearn.preprocessing import StandardScaler
import random

pts = int(input("Enter number of points: \n"))
dimension = int(input("Since dataset choosen is blob, enter number of dimensions\n"))

# generate 2d classification dataset
X, y = make_blobs(n_samples = pts, centers = [(1,5),(5,10),(10,5)], n_features = dimension)

# writing in file
outputfile = open("points.txt","w")
outputfile.write(str(pts) + " " + str(dimension) + "\n")

for l1 in X:
    for l2 in l1:
        outputfile.write(str(l2) + " ")
    outputfile.write("\n")

# graphing
df = DataFrame(dict(x=X[:,0], y=X[:,1], label=y))
colors = {0:'red', 1:'blue', 2:'green'}
fig, ax = pyplot.subplots()
grouped = df.groupby('label')
for key, group in grouped:
    group.plot(ax=ax, kind='scatter', x='x', y='y', label=key, color=colors[key])
pyplot.show()

# Applying DBSCAN
l = StandardScaler().fit_transform(X)
db = DBSCAN(eps=0.1, min_samples=10).fit(l)
core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
core_samples_mask[db.core_sample_indices_] = True
labels = db.labels_

# number of clusters
n_clusters_ = len(set(labels))
print(n_clusters_)

list_of_clusters=[]
fake_list=[]

for i in range(n_clusters_):
    list_of_clusters.append(fake_list)

i = 0
for label in labels:
    if label == -1:
        list_of_clusters[n_clusters_-1].append(X[i])
    else:
        list_of_clusters[label].append(X[i])
    i = i + 1

clr = ["green","blue","red","orange","yellow","violet","pink"]
x = []
y = []
k = 0

# deleting some points
num = int(input("Enter number of points to be deleted: \n"))
x1 = 8
x2 = 10
y1 = 4
y2 = 6

outputfile = open("del.txt","w")
outputfile.write(str(num) + '\n')
count = 0

for i in range(pts):
    if x1 <= X[i][0] <= x2 and y1 <= X[i][1] <= y2 and count < num:
        count = count + 1
        # X.remove(i)
        outputfile.write(str(X[i][0]) + ' ' + str(X[i][1]) + '\n')

outputfile.close()

# Adding new points
num = int(input("Enter number of points to be added: \n"))
x1 = 2
x2 = 4
y1 = 6
y2 = 8

outputfile = open("add.txt","w")
outputfile.write(str(num) +'\n')

for i in range(num):
    x = x1 + (x2-x1) * random.random()
    y = y1 + (y2-y1) * random.random()
    outputfile.write(str(x) + " " + str(y) + '\n')

outputfile.close()