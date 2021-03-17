###  n-dimensional datasets  ###
import random
import math
dim = 8
num_of_points = 2000
n_dim = []
file = open("n-dim_data.txt","w")
file.write(str(num_of_points)+' '+str(dim)+'\n')
for i in range(num_of_points):
    point = []
    for j in range(dim):
        k = 10*random.random()
        point.append(k)
        file.write(str(k)+' ')
    file.write('\n')
    n_dim.append(point)
file.close()
        
###  deleting from n-dim  ###
numd = 100
file = open("n-dim_queries.txt","w")
file.write("200 " + str(dim)+'\n')
for i in range(numd):
    d = math.floor(len(n_dim)*random.random())
    file.write("D ")
    for i in range(n):
        file.write(str(n_dim[d][i])+' ')
    file.write('\n')
file.close()

###  adding to n-dim  ###
numa = 100
file=open("n-dim_queries.txt","a")
for i in range(numa):
    point = []
    file.write("A ")
    for j in range(n):
        k = 10*random.random()
        point.append(k)
        file.write(str(k)+" ")
    file.write('\n')
    n_dim.append(point)
file.close()
