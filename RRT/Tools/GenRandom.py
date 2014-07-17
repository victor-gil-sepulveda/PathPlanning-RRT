##
## Generates a list of random numbers
## Call it as: python GenRandom.py total max
## Where total is the number of random numbers on your list
## and max is the maximum value of these numbers

import random
import sys

total = int(sys.argv[1])
max = int(sys.argv[2])


random.seed()
for i in range(0,total):
	print random.randint(0,max)

