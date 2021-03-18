from sklearn.datasets import make_moons,make_blobs, make_circles
from matplotlib import pyplot
from pandas import DataFrame

def moon_dataset(no_of_points):
    # generate 2d classification dataset
    X, y = make_moons(n_samples = no_of_points, noise = 0.1)
    outputfile = open("data.txt","a")
    outputfile.write(str(no_of_points)+" 2\n")
    for point in X:
        a = str(round(point[0]+6,3))
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
        b = str(round(point[1]+5,3))
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
        outputfile.write(a+' '+b+'\n')
    outputfile.close()

def blob_dataset(no_of_points, dimension = 2):
    # generate 2d classification dataset
    X, y = make_blobs(n_samples = no_of_points, centers = [(0,5),(-3,-5),(4.5,0)], n_features = dimension)
    outputfile = open("data.txt","a")
    outputfile.write(str(no_of_points) + " " + str(dimension) + "\n")
    for l1 in X:
        for l2 in l1:
            a = str(round(l2,3))
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
            outputfile.write(a + " ")
        outputfile.write("\n")
    outputfile.close()

    df = DataFrame(dict(x=X[:,0], y=X[:,1], label=y))
    colors = {0:'red', 1:'blue', 2:'green'}
    fig, ax = pyplot.subplots()
    grouped = df.groupby('label')
    for key, group in grouped:
        group.plot(ax=ax, kind='scatter', x='x', y='y', label=key, color=colors[key])
    pyplot.show()

def circle_dataset(no_of_points):
    # generate 2d classification dataset
    X, y = make_circles(n_samples = no_of_points, noise = 0.05, factor=0.7)
    outputfile = open("data.txt","a")
    outputfile.write(str(no_of_points) + " " + str(2) + "\n")
    for l1 in X:
        for l2 in l1:
            a = str(round(l2,3))
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
            outputfile.write(a + " ")
        outputfile.write("\n")
    outputfile.close()
    
outputfile = open("data.txt","w")
outputfile.write("3\n")
outputfile.close()

moon_dataset(300)
blob_dataset(1000,2)
circle_dataset(200)

datafile = open("data.txt","r")
t=int(datafile.readline())
data = []
while t:
    t=t-1
    n=int(datafile.readline().split(" ")[0])
    while n:
        n=n-1
        line = datafile.readline().split(" ")
        data.append([float(line[0]),float(line[1])])
datafile.close()

x = []
y = []
for point in data:
    x.append(point[0])
    y.append(point[1])
import matplotlib.pyplot as plt
plt.scatter(x, y, label= "stars", color="red",marker= ".", s=30)
plt.xlabel('x - axis') 
plt.ylabel('y - axis') 
plt.title('Dataset') 
plt.show()
print(data)

###  Adding points  ###
import random
import math
queries = []
for i in range(123):
    newx=2*random.random()-1
    newy=4*random.random()
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
    data.append([float(a),float(b)])
    queries.append("A "+a+' '+b+'\n')
print(len(data))
###  Deleting points  ###
count = 100
for point in data:
    if 0<=point[0]<=3 and -2<=point[1]<=2 and count!=0:
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
        queries.append("D "+a+' '+b+'\n')
        data.remove(point)
        count=count-1
print(len(data))
random.shuffle(queries)
file = open("queries.txt","w")
file.write(str(len(queries))+"\n")
for ln in queries:
    file.write(ln)
file.close()
