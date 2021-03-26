import math
import numpy as np
from sklearn.cluster import DBSCAN
from sklearn import metrics
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler

l = []
input_file = open("Files/points.txt","r")
output_file = open("DBSCAN/numbered_dbscan_clusters.txt","w")
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
		if item == '':
			continue
		p.append(float(item))
	l.append(p)
l = StandardScaler().fit_transform(l)
X = l

# Compute DBSCAN
db = DBSCAN(eps=1, min_samples=10).fit(l)
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

##############################################################################
# Plot result
import pylab as pl
from itertools import cycle

pl.close('all')
pl.figure(1)
pl.clf()

# Black removed and is used for noise instead.
colors = cycle('bgrcmybgrcmybgrcmybgrcmy')
for k, col in zip(set(labels), colors):
    if k == -1:
        # Black used for noise.
        col = 'k'
        markersize = 6
    class_members = [index[0] for index in np.argwhere(labels == k)]
    cluster_core_samples = [index for index in db.core_sample_indices_
                            if labels[index] == k]
    for index in class_members:
        x = X[index]
        if index in db.core_sample_indices_ and k != -1:
            markersize = 6
        else:
            markersize = 6
        pl.plot(x[0], x[1], 'o', markerfacecolor=col,
                markeredgecolor='k', markersize=markersize)

pl.title('Estimated number of clusters: %d' % n_clusters_)
pl.show()
