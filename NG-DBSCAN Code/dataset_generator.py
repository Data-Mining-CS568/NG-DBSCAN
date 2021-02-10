from sklearn.datasets import make_moons, make_blobs, make_circles
from matplotlib import pyplot
from pandas import DataFrame

def moon_dataset(no_of_points):
	# generate 2d classification dataset
	X, y = make_moons(n_samples = no_of_points, noise = 0.1)
	outputfile = open("points.txt","w")
	outputfile.write(str("galaxy") + " " + str(no_of_points) + " " + str(2) + "\n")
	for l1 in X:
		for l2 in l1:
			outputfile.write(str(l2) + " ")
		outputfile.write("\n")

def blob_dataset(no_of_points, dimension = 2):
	# generate 2d classification dataset
	X, y = make_blobs(n_samples = no_of_points, centers = 3, n_features = dimension)
	outputfile = open("points.txt","w")
	outputfile.write(str("galaxy") + " " + str(no_of_points) + " " + str(dimension) + "\n")
	for l1 in X:
		for l2 in l1:
			outputfile.write(str(l2) + " ")
		outputfile.write("\n")

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
	outputfile = open("points.txt","w")
	outputfile.write(str("galaxy") + " " + str(no_of_points) + " " + str(2) + "\n")
	for l1 in X:
		for l2 in l1:
			outputfile.write(str(l2) + " ")
		outputfile.write("\n")

def text_dataset(no_of_sentences):
	# generate 2d classification dataset

	inputfile  = open("healthTwitter.txt", "r")
	outputfile = open("points.txt","w")
	outputfile.write(str("text") + " " + str(no_of_sentences) + " " + str(0) + "\n") 
	for i in range(no_of_sentences):
				
		tempS = inputfile.readline();
		#print(tempS)
		s = ""
		cnt_pipe = 0;
		for element in range(0, len(tempS)):
			
			if cnt_pipe == 2:
				s += tempS[element] 

			if cnt_pipe < 2 and tempS[element] == '|':
				cnt_pipe += 1
			

		s1 = s.partition("http://") 		
		outputfile.write( s1[0] + "\n")
	
		#print(s)	
		#outputfile.write(s)
	
	outputfile.write("\n")

def main():
	pts = int(input("Enter number of points/text sentences: \n"))
	number = int(input("Which dataset you want to generate\n Enter 1 for moon dataset\n Enter 2 for blob dataset\n Enter 3 for circle dataset\n Enter 4 for text datasets \n"))
	if number == 1:
		moon_dataset(pts)	
	elif number == 2:
		dimension = int(input("Since dataset choosen is blob, enter number of dimensions\n"))
		blob_dataset(pts, dimension)
	elif number == 3:
		circle_dataset(pts)	
	else:
		text_dataset(pts)

if __name__ == "__main__":
    main()