import Image
import sys
import struct

im = Image.open( sys.argv[1] )

myfile = open(sys.argv[2],"wb")


s = struct.pack("<ii",im.size[0],im.size[1])
myfile.write(s)

print im.size

for y in range(im.size[1]):
	for x in range(im.size[0]):
		pixel = im.getpixel((x,y))
		color = 255
		for k in range(len(pixel)):
			if pixel[k]<50:
				color = 0
		myfile.write(chr(color))
myfile.close()
