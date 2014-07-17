import Image, ImageDraw
import sys
import struct
import os

## Background (scenario)
im = Image.open( sys.argv[1] )

## RRT file
myfile = open(sys.argv[2],"r")
lines = myfile.readlines()
myfile.close()

draw = ImageDraw.Draw(im)

green = "#00ff00"
red = "#ff0000" 
blue = "#0000ff"

has_a_goal = "goal" in lines[-1]

for i in range(len(lines)):
	s_coordinates = lines[i].split()
		
	if has_a_goal :
		if i==len(lines)-1:
			coorx = int(s_coordinates[1])
			coory = int(s_coordinates[2])
			draw.ellipse((coorx-2,coory-2,coorx+2,coory+2),fill = blue )
		else:
			coorx = int(s_coordinates[0])
			coory = int(s_coordinates[1])
			coorx2 = int(s_coordinates[2])
			coory2 = int(s_coordinates[3])

			if i==len(lines)-2 :
				color = green
			else:
				color = red

			draw.line((coorx,coory,coorx2,coory2),fill = color)
			draw.ellipse((coorx-1,coory-1,coorx+1,coory+1),fill = color )
			draw.ellipse((coorx2-1,coory2-1,coorx2+1,coory2+1),fill = red )
	else :	
		if i==len(lines)-1 :
			color = green
		else:
			color = red
		
		coorx = int(s_coordinates[0])
		coory = int(s_coordinates[1])
		coorx2 = int(s_coordinates[2])
		coory2 = int(s_coordinates[3])
		draw.line((coorx,coory,coorx2,coory2),fill = color)
		draw.ellipse((coorx-1,coory-1,coorx+1,coory+1),fill = color )
		draw.ellipse((coorx2-1,coory2-1,coorx2+1,coory2+1),fill = red )
	if i == 0:
		draw.line((coorx-3,coory,coorx+3,coory),fill = "#770077")
		draw.line((coorx,coory+3,coorx,coory-3),fill = "#770077")
		
#print frame number in right-bottom corner
(w,h) = im.size
(tw, th) = draw.textsize(sys.argv[3]) 
draw.text((w-20-tw,h-2-th),sys.argv[3],fill = "#000000")

del draw
im.save(os.path.splitext(sys.argv[2])[0]+".png", "PNG")
