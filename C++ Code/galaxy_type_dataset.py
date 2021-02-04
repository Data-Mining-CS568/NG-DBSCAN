import random
import math

# radius of the circle
circle_r = 10
#starting radius
start_r = 5
# center of the circle (x, y)
circle_x = 5
circle_y = 7

points = 100

circledata = []

outputfile = open("points.txt","w")
outputfile.write(str(points) + '\n')

while(points > 0):
    # random angle
    alpha = 2 * math.pi * random.random()
    # random radius
    r = (circle_r - start_r) * math.sqrt(random.random()) + start_r
    # calculating coordinates
    x = r * math.cos(alpha) + circle_x
    y = r * math.sin(alpha) + circle_y
    circledata.append((x,y))
    outputfile.write(str(x) + " " + str(y) + '\n')
    points = points - 1

outputfile.close()
