import pandas as pd


def generate():
	csv_file = pd.read_csv("Traffic.csv", "r")
	location = csv_file['location']
	#print(location)
	total_pts = 5000
	cnt = 0
	dimension = 2
	points_file = open("points.txt", "w")
	queries_file = open("queries.txt", "w")
	points_file.write(str(total_pts))
	points_file.write(" ")
	points_file.write(str(dimension))
	add_x = [] #this points will be add in the data set
	add_y = []
	del_x = []
	del_y = []
	for i in range(20000):	
		temp = location[i].split(',')
		x_cor = temp[0].split('(')
		y_cor = temp[1].split(')')
		if cnt == 5000:
			break
		#removing unnecessary boundary points
		if float(x_cor[1]) < 42.7 or float(x_cor[1]) > 43.2 or float(y_cor[0]) > -78.7 :
			continue

		#adding points which we will add to our dataset to test incremental algorithm	
		if float(x_cor[1]) <=43 and float(x_cor[1]) >= 42.86 and float(y_cor[0]) <= -78.73 and float(y_cor[0]) >= -78.78:
			add_x.append(float(x_cor[1]))
			add_y.append(float(y_cor[0]))
			continue

		if float(x_cor[1]) <=43.2 and float(x_cor[1]) >= 43.1 and float(y_cor[0]) <= -78.70 and float(y_cor[0]) >= -78.90:
			add_x.append(float(x_cor[1]))
			add_y.append(float(y_cor[0]))
			continue

		#point which will be deleted from our dataset
		if float(x_cor[1]) <=42.81 and float(x_cor[1]) >= 42.79 and float(y_cor[0]) <= -78.70 and float(y_cor[0]) >= -78.90:
			del_x.append(float(x_cor[1]))
			del_y.append(float(y_cor[0]))
			

		cnt += 1
		points_file.write("\n")
		points_file.write(str(x_cor[1]))
		points_file.write(" ")
		points_file.write(str(y_cor[0]))
	print(cnt);	

	queries_file.write(str(len(add_x)+len(del_x)))
	queries_file.write("\n")
	for i in range(len(add_x)):
		queries_file.write('A')
		queries_file.write(" ")
		queries_file.write(str(add_x[i]))
		queries_file.write(" ")
		queries_file.write(str(add_y[i]))
		queries_file.write("\n")	

	for i in range(len(del_x)):
		queries_file.write('D')
		queries_file.write(" ")
		queries_file.write(str(del_x[i]))
		queries_file.write(" ")
		queries_file.write(str(del_y[i]))
		queries_file.write("\n")	


if __name__ == "__main__":
	generate()

