import math

l = []
input_file = open("clusters.txt","r")
x = input_file.readline()
a = x.split()
n = int(a[0])

for i in range(n):
	lst = []
	x = input_file.readline()
	m = int(x[0])
	for j in range(m):
		x = input_file.readline()
		a = x.split()
		t = list()
		for pt in a:
			t.append(pt)
		p = tuple(t)
		lst.append(p)
	l.append(lst)	

print(l)