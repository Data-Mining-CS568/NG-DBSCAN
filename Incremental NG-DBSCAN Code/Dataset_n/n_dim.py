import random
def ndim(n,num,centre,r):
	file = open("ndim_points","w")
	file.write(str(num)+'\n')
	for x in range(num):
		for y in range(n):
			k = centre[y]+r*random.random()
			s = str(round(k,3))
			d=0
			f=0
			for i in range(len(s)):
				if f==1:
					d=d+1
				if s[i]=='.':
					f=1
			if d==1:
				s=s+"00"
			if d==2:
				s=s+"0"
			file.write(s+' ')
		file.write('\n')

ndim(4,1000,[1,2,3,4],4)