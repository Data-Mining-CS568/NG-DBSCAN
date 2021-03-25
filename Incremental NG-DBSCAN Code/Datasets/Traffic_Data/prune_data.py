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
	delete_x = []
	delete_y = []
	for i in range(20000):	
		temp = location[i].split(',')
		x_cor = temp[0].split('(')
		y_cor = temp[1].split(')')
		if cnt == 5000:
			break
		if float(x_cor[1]) < 42.7 or float(x_cor[1]) > 43.2 or float(y_cor[0]) > -78.7 :
			continue

		if float(x_cor[1]) <=42.95 and float(x_cor[1]) >= 42.86 and float(y_cor[0]) <= -78.75 and float(y_cor[0]) >= -78.78:
			delete_x.append(float(x_cor[1]))
			delete_y.append(float(y_cor[0]))
			continue

		cnt += 1
		points_file.write("\n")
		points_file.write(str(x_cor[1]))
		points_file.write(" ")
		points_file.write(str(y_cor[0]))
	print(cnt);	

	queries_file.write(str(len(delete_x)))
	queries_file.write(" ")
	queries_file.write(str(dimension))
	queries_file.write("\n")
	for i in range(len(delete_x)):
		queries_file.write("A ")
		queries_file.write(str(delete_x[i]))
		queries_file.write(" ")
		queries_file.write(str(delete_y[i]))
		queries_file.write("\n")	


if __name__ == "__main__":
	generate()

