import math
import sys

myfile = open(sys.argv[1],"r")
lines = myfile.readlines()
myfile.close()

for i in range(len(lines)):
	s_coordinates = lines[i].split()
	coorx = int(s_coordinates[0])
	coory = int(s_coordinates[1])
	if len(s_coordinates)==4:
		coorx2 = int(s_coordinates[2])
		coory2 = int(s_coordinates[3])
		
		print math.sqrt((coorx2-coorx)*(coorx2-coorx) + (coory2-coory)*(coory2-coory))
		
