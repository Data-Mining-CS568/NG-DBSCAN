import pandas as pd


def generate():
	csv_file = pd.read_csv("Traffic.csv", "r")
	location = csv_file['location']
	#print(location)
	total_pts = 5000
	cnt = 0
	dimension = 2
	points_file = open("points.txt", "w")
	points_file.write(str(total_pts))
	points_file.write(" ")
	points_file.write(str(dimension))
	for i in range(20000):	
		temp = location[i].split(',')
		temp1 = temp[0].split('(')
		temp2 = temp[1].split(')')
		if cnt == 5000:
			break
		if float(temp1[1]) < 42.7 or float(temp1[1]) > 43.2 or float(temp2[0]) > -78.7 :
			continue
		cnt += 1
		points_file.write("\n")
		points_file.write(str(temp1[1]))
		points_file.write(" ")
		points_file.write(str(temp2[0]))
	print(cnt);	

if __name__ == "__main__":
	generate()

