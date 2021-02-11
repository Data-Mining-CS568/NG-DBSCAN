import math
import numpy as np
from sklearn.cluster import DBSCAN
from sklearn import metrics
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler

l = []
input_file = open("points.txt","r")
output_file = open("numbered_dbscan_clusters.txt","w")
x = input_file.readline()
a = x.split()
n = int(a[1])
dim = int(a[2])
for j in range(n):
	x = input_file.readline()
	x = x.strip()
	x = x.split(' ')
	p = []
	for item in x:
		p.append(float(item))
	l.append(p)
l = StandardScaler().fit_transform(l)

# Compute DBSCAN
db = DBSCAN(eps=0.1, min_samples=10).fit(l)
core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
core_samples_mask[db.core_sample_indices_] = True
labels = db.labels_

# Number of clusters in labels, ignoring noise if present.
n_clusters_ = len(set(labels)) - (1 if -1 in labels else 0)
n_noise_ = list(labels).count(-1)

output_file.write(str(n) + "\n")
for i in labels:
	output_file.write(str(i) + " ")
output_file.write("\n")
