import random
def ndim(n,num,centre,r):
	file = open("ndim_points.txt","a")
	for x in range(num):
		for y in range(n):
			k = centre[y]+r*random.random()
			s = str(round(k,3))
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
			file.write(s+' ')
		file.write('\n')
	file.close()
	
from sklearn.datasets import make_blobs
def blobs(pts,centre,dim):
    X, y = make_blobs(n_samples = pts, centers = centre, n_features = dim)
    outputfile = open("ndim_points.txt","a")
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
    outputfile.close()

### generating data ###
n = int(input("Enter the dimension:"))
n1 = int(input("Enter no. of points of 1st cube:"))
n2 = int(input("Enter no. of points of 2nd cube:"))
#n3 = int(input("Enter no. of points of 3rd cube:"))
b  = int(input("Enter no. of points of blob:"))

file = open("ndim_points.txt","w")
total = 0
total = n1+n2+b
file.write(str(total)+' '+str(n)+'\n')
ndim(n,n1,[1,1,1],3)
ndim(n,n2,[5,5,3],3)
#ndim(n,n3,[3,3,1.5],4)
blobs(b,[(-1,-2,-2),(0,4,9),(2,-2,-3)],n)

datafile = open("ndim_points.txt","r")
t=datafile.readline().split(" ")
p = int(t[0])
n = int(t[1])
data = []
while p:
    p=p-1
    line = datafile.readline().split(" ")
    point = []
    for i in range(n):
        point.append(float(line[i]))
    data.append(point)
datafile.close()

# importing mplot3d toolkits, numpy and matplotlib 
from mpl_toolkits import mplot3d 
import numpy as np 
import matplotlib.pyplot as plt 
  
fig = plt.figure() 
  
# syntax for 3-D projection 
ax = plt.axes(projection ='3d')
x=[]
y=[]
z=[]
for point in data:
    x.append(point[0])
    y.append(point[1])
    z.append(point[2])
ax.scatter(x, y, z,'black',s=1)

# plotting  
ax.set_title('3D plot') 
plt.show()
#print(data)


### generating queries ###
queries = []
#file = open("ndim_queries.txt","w")
centre = [3,3,1.5]
for x in range(200):
    q = "A "
    for y in range(3):
        k = centre[y]+4*random.random()
        s = str(round(k,3))
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
        q = q+s+' '
    queries.append(q)
    
for point in data:
    if -0.5<=point[0]<=0.5:
        q = "D "
        for i in range(3):
            s = str(round(point[i],3))
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
            q = q + s + ' '
        queries.append(q)
random.shuffle(queries)
file = open("ndim_queries.txt","w")
file.write(str(len(queries))+'\n')
for query in queries:
    file.write(query+'\n')
file.close()
