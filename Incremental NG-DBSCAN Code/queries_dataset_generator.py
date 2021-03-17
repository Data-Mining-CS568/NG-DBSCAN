import random
from sklearn.datasets import make_moons, make_blobs, make_circles
from matplotlib import pyplot
import matplotlib.pyplot as plt
from pandas import DataFrame
import numpy as np
from sklearn.cluster import DBSCAN
from sklearn import metrics
from sklearn.preprocessing import StandardScaler

pts = int(input("Enter number of points: \n"))
dimension = int(input("Since dataset choosen is blob, enter number of dimensions\n"))

# generate 2d classification dataset
X, y = make_blobs(n_samples = pts, centers = [(1,5),(5,10),(10,5)], n_features = dimension)

# writing in file
outputfile = open("points.txt","w")
outputfile.write(str(pts) + " " + str(dimension) + "\n")
for l1 in X:
    for l2 in l1:
        s = str(round(l2,3))
        d=0
        f=0
        for i in range(len(s)):
            if f==1:
                d=d+1
            if s[i]=='.':
                f=1
        if d==1:
            s=s+"00"
        if d==2:
            s=s+"0"
        outputfile.write(s + " ")
    outputfile.write("\n")

#graphing
df = DataFrame(dict(x=X[:,0], y=X[:,1], label=y))
colors = {0:'red', 1:'blue', 2:'green'}
fig, ax = pyplot.subplots()
grouped = df.groupby('label')
for key, group in grouped:
    group.plot(ax=ax, kind='scatter', x='x', y='y', label=key, color=colors[key])
pyplot.show()

l = []
for point in X:
    l.append([point[0],point[1]])
#print(l)

# Applying DBSCAN
dl = StandardScaler().fit_transform(X)
db = DBSCAN(eps=0.2, min_samples=10).fit(dl)
core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
core_samples_mask[db.core_sample_indices_] = True
labels = db.labels_


# number of sets
n_clusters = len(set(labels))

#print(len(dic_of_clusters[0]))
clr=["green","blue","red","orange","yellow","violet","pink"]
x = []
y = []
nx = []
ny = []
for k in range(n_clusters):
    i=0
    for label in labels:
        if label==k:
            x.append([l[i][0]])
            y.append([l[i][1]])
        if label==-1:
            nx.append([l[i][0]])
            ny.append([l[i][1]])
        i=i+1
    if k == (n_clusters-1):
        plt.scatter(nx, ny, label= "stars", color= "black",marker= ".", s=20)
    else :
        plt.scatter(x, y, label= "stars", color= clr[k%7],marker= ".", s=30)
    x=[]
    y=[]

plt.xlabel('x - axis') 
plt.ylabel('y - axis') 
plt.title('Clusters plot!') 
plt.show()


queries = []


# deleting some points
numd = int(input("Enter number of points to be deleted: \n"))
x1=8
x2=10
y1=4
y2=6
#outputfile = open("del.txt","w")
#outputfile.write(str(num) + '\n')
count=0
for point in l:
    if x1<=point[0]<=x2 and y1<=point[1]<=y2 and count<numd:
        count=count+1
        l.remove(point)
        a = str(round(point[0],3))
        d=0
        f=0
        for i in range(len(a)):
            if f==1:
                d=d+1
            if a[i]=='.':
                f=1
        if d==1:
            a=a+"00"
        if d==2:
            a=a+"0"
        b = str(round(point[1],3))
        d=0
        f=0
        for i in range(len(b)):
            if f==1:
                d=d+1
            if b[i]=='.':
                f=1
        if d==1:
            b=b+"00"
        if d==2:
            b=b+"0"
        queries.append("D "+a+" "+b+'\n')
        #outputfile.write(a+' '+b+'\n')
#outputfile.close()

print(len(l))

# Applying DBSCAN
dl = StandardScaler().fit_transform(l)
db = DBSCAN(eps=0.2, min_samples=10).fit(dl)
core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
core_samples_mask[db.core_sample_indices_] = True
labels = db.labels_


# number of sets
n_clusters = len(set(labels))

#print(len(dic_of_clusters[0]))
clr=["green","blue","red","orange","yellow","violet","pink"]
x = []
y = []
nx = []
ny = []
for k in range(n_clusters):
    i=0
    for label in labels:
        if label==k:
            x.append([l[i][0]])
            y.append([l[i][1]])
        if label==-1:
            nx.append([l[i][0]])
            ny.append([l[i][1]])
        i=i+1
    if k == (n_clusters-1):
        plt.scatter(nx, ny, label= "stars", color= "black",marker= ".", s=20)
    else :
        plt.scatter(x, y, label= "stars", color= clr[k%7],marker= ".", s=30)
    x=[]
    y=[]

plt.xlabel('x - axis') 
plt.ylabel('y - axis') 
plt.title('Clusters plot!') 
plt.show()


#Adding new points
numa = int(input("Enter number of points to be added: \n"))
x1=2
x2=5
y1=6
y2=9
#outputfile = open("add.txt","w")
#outputfile.write(str(num)+'\n')
for i in range(numa):
    newx=x1+(x2-x1)*random.random()
    newy=y1+(y2-y1)*random.random()
    l.append([newx,newy])
    a = str(round(newx,3))
    d=0
    f=0
    for i in range(len(a)):
        if f==1:
            d=d+1
        if a[i]=='.':
            f=1
    if d==1:
        a=a+"00"
    if d==2:
        a=a+"0"
    b = str(round(newy,3))
    d=0
    f=0
    for i in range(len(b)):
        if f==1:
            d=d+1
        if b[i]=='.':
            f=1
    if d==1:
        b=b+"00"
    if d==2:
        b=b+"0"
    queries.append("A "+a+' '+b+'\n')
    #outputfile.write(a+' '+b+'\n')
#outputfile.close()

queryfile = open("queries.txt","w")
queryfile.write(str(len(queries))+'\n')
random.shuffle(queries)
for query in queries:
    queryfile.write(query)
queryfile.close()

print(len(l))

# Applying DBSCAN
dl = StandardScaler().fit_transform(l)
db = DBSCAN(eps=0.2, min_samples=10).fit(dl)
core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
core_samples_mask[db.core_sample_indices_] = True
labels = db.labels_


# number of sets
n_clusters = len(set(labels))

#print(len(dic_of_clusters[0]))
clr=["green","blue","red","orange","yellow","violet","pink"]
x = []
y = []
nx = []
ny = []
for k in range(n_clusters):
    i=0
    for label in labels:
        if label==k:
            x.append([l[i][0]])
            y.append([l[i][1]])
        if label==-1:
            nx.append([l[i][0]])
            ny.append([l[i][1]])
        i=i+1
    if k == (n_clusters-1):
        plt.scatter(nx, ny, label= "stars", color= "black",marker= ".", s=20)
    else :
        plt.scatter(x, y, label= "stars", color= clr[k%7],marker= ".", s=30)
    x=[]
    y=[]

plt.xlabel('x - axis') 
plt.ylabel('y - axis') 
plt.title('Clusters plot!') 
plt.show()
