import math
import numpy as np
from sklearn.cluster import DBSCAN
from sklearn import metrics
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler


l = []
input_file = open("points.txt","r")
x = input_file.readline()
a = x.split()
n = int(a[0])
#print(n)            
for j in range(n):
	x = input_file.readline()
	x = x.split(' ')
	p = [float(x[0]),float(x[1])]
	l.append(p)
print(l)





l = StandardScaler().fit_transform(l)

# #############################################################################
# Compute DBSCAN
db = DBSCAN(eps=0.1, min_samples=10).fit(l)
core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
core_samples_mask[db.core_sample_indices_] = True
labels = db.labels_

# Number of clusters in labels, ignoring noise if present.
n_clusters_ = len(set(labels)) - (1 if -1 in labels else 0)
n_noise_ = list(labels).count(-1)

print('Estimated number of clusters: %d' % n_clusters_)
print('Estimated number of noise points: %d' % n_noise_)
#print("Silhouette Coefficient: %0.3f" % metrics.silhouette_score(X, labels))

print(labels)
print(l)




