import pandas as pd


def generate():
	csv_file = pd.read_csv("Traffic.csv", "r")
	location = csv_file['location']
	#print(location)
	total_pts = 2000
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
	already_taken = {}
	for i in range(20000):	
		temp = location[i].split(',')
		x_cor = temp[0].split('(')
		y_cor = temp[1].split(')')
		if cnt == 2000:
			break
		#removing unnecessary boundary points
		if float(x_cor[1]) < 42.7 or float(x_cor[1]) > 43.2 or float(y_cor[0]) > -78.7 :
			continue
		
		x1 = round(float(x_cor[1]),3)
		y1 = round(float(y_cor[0]),3)
		if already_taken.__contains__((x1,y1)):
			continue
		else:
			already_taken[(x1,y1)] = 1	
		#adding points which we will add to our dataset to test incremental algorithm	
		if float(x_cor[1]) <=43 and float(x_cor[1]) >= 42.86 and float(y_cor[0]) <= -78.73 and float(y_cor[0]) >= -78.78:
			add_x.append(x1)
			add_y.append(y1)
			continue

		if float(x_cor[1]) <=43.2 and float(x_cor[1]) >= 43.1 and float(y_cor[0]) <= -78.70 and float(y_cor[0]) >= -78.90:
			add_x.append(x1)
			add_y.append(y1)
			continue

		#point which will be deleted from our dataset
		if float(x_cor[1]) <=42.81 and float(x_cor[1]) >= 42.74 and float(y_cor[0]) <= -78.70 and float(y_cor[0]) >= -78.90:
			del_x.append(x1)
			del_y.append(y1)
			

		cnt += 1
		points_file.write("\n")
		points_file.write(f'{x1:.3f}')
		points_file.write(" ")
		points_file.write(f'{y1:.3f}')
	print(cnt);	

	queries_file.write(str(len(add_x)+len(del_x)))
	queries_file.write("\n")
	for i in range(len(add_x)):
		queries_file.write('A')
		queries_file.write(" ")
		queries_file.write(f'{add_x[i]:.3f}')
		queries_file.write(" ")
		queries_file.write(f'{add_y[i]:.3f}')
		queries_file.write("\n")	

	for i in range(len(del_x)):
		queries_file.write('D')
		queries_file.write(" ")
		queries_file.write(f'{del_x[i]:.3f}')
		queries_file.write(" ")
		queries_file.write(f'{del_y[i]:.3f}')
		queries_file.write("\n")	


if __name__ == "__main__":
	generate()

