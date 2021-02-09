import random
import math

def galaxy_generator(points, circle_r, start_r, circle_x, circle_y, generated_data):
    outputfile = open("points.txt","a")

    while(points > 0):
        # random angle
        alpha = 2 * math.pi * random.random()
        # random radius
        r = (circle_r-start_r) * math.sqrt(random.random()) + start_r
        # calculating coordinates
        x = r * math.cos(alpha) + circle_x
        y = r * math.sin(alpha) + circle_y
        p = [x,y]
        generated_data.append(p)
        outputfile.write(str(x) + " " + str(y) + '\n')
        points = points - 1

    outputfile.close()

def rectangle_generator(points, length, width, cx, cy, generated_data):
    outputfile = open("points.txt","a")

    while(points > 0):
        # random coordinates
        x = length * math.sqrt(random.random()) + cx
        y = width * math.sqrt(random.random()) + cy
        p = [x,y]
        generated_data.append(p)
        outputfile.write(str(x) + " " + str(y) + '\n')
        points = points - 1
    
    outputfile.close()

def main():
    outputfile = open("points.txt","w")    
    outputfile.write("5000" + '\n')
    outputfile.close()
    generated_data = []
    galaxy_generator(1000,70,30,0,0,generated_data)
    galaxy_generator(1000,100,30,50,200,generated_data)
    galaxy_generator(1000,50,30,200,0,generated_data)
    rectangle_generator(1000,50,40,330,0,generated_data)
    rectangle_generator(1000,50,40,100,50,generated_data)

if __name__ == "__main__":
    main()
