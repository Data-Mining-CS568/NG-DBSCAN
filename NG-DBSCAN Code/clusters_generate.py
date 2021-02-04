import matplotlib.pyplot as plt
clr=["green","blue","red","orange","yellow","violet","black","pink"]
i=0
for cluster in l:
    x=[]
    y=[]
    for point in cluster:
        x.append(point[0])
        y.append(point[1])
    # plotting points as a scatter plot 
    plt.scatter(x, y, label= "stars", color= clr[i],marker= "*", s=30)
    i=(i+1)%6
    a=[]
    b=[]
    for point in noise:
        a.append(point[0])
        b.append(point[1])
    #print(noise)
    plt.scatter(a, b, label= "stars", color= "lightblue",marker= "*", s=30)
  
# x-axis label 
plt.xlabel('x - axis') 
# frequency label 
plt.ylabel('y - axis') 
# plot title 
plt.title('Clusters plot!') 
# function to show the plot 
plt.show()