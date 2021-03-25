# importing mplot3d toolkits, numpy and matplotlib 
from mpl_toolkits import mplot3d 
import numpy as np 
import matplotlib.pyplot as plt
import random
from sklearn.datasets import make_blobs

### generating data ###
n = int(input("Enter the dimension:"))
n1 = int(input("Enter no. of points of 1st cube:"))
n2 = int(input("Enter no. of points of 2nd cube:"))
b  = int(input("Enter no. of points of blob:"))

data = []

# First cube #
centre = [1,1,1]
for i in range(n1):
    point = []
    for y in range(n):
        k = centre[y]+3*random.random()
        point.append(k)
    data.append(point)

# Second cube #
centre = [5,5,3]
for i in range(n2):
    point = []
    for y in range(n):
        k = centre[y]+3*random.random()
        point.append(k)
    data.append(point)
    
# Blobs #
X, y = make_blobs(n_samples = b, centers = [(-2,-2,-2),(4,-2,-3)], n_features = 3)
for l1 in X:
    point = []
    for l2 in l1:
        point.append(l2)
    data.append(point)

delete = []
# Delete blob #
X, y = make_blobs(n_samples = 800, centers = [(2,-2,-2)], n_features = 3)
for l1 in X:
    point = []
    for l2 in l1:
        point.append(l2)
    data.append(point)
    delete.append(point)

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



file = open("points.txt","w")
file.write(str(len(data))+" 3\n")
for point in data:
    q = ""
    for x in point:
        s = str(round(x,3))
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
    q = q + '\n'
    file.write(q)
file.close()
        
        

    
add = []
# Add cube #
centre = [3,3,1.5]
for x in range(1000):
    point = []
    for y in range(3):
        k = centre[y]+4*random.random()
        point.append(k)
    add.append(point)
    data.append(point)

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

for point in delete:
    data.remove(point)
    
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

queries = []
for point in add:
    s = "A "
    for x in point:
        s = s + str(x) + ' '
    s = s + '\n'
    queries.append(s)
    
for point in delete:
    s = "D "
    for x in point:
        s = s + str(x) + ' '
    s = s + '\n'
    queries.append(s)
    
random.shuffle(queries)

file = open("queries.txt","w")
file.write(str(len(queries))+" 3\n")
for query in queries:
    file.write(query)
file.close()
