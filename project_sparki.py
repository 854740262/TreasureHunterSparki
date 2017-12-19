from __future__ import print_function

from sparki_learning import *


import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
from scipy.interpolate import spline
import random







def draw(a, b):
        lims = (0,20)
        #plt.ion()
        #a=[(5,5),(5,6),(6,6),(6,7),(7,7),(7,8),(8,8),(8,9),(9,9),(9,10)]

        x = []
        y = []
        count = -1
        for i in range(len(a)):
                if(a[i][0] != count):
                        x.append(a[i][0])
                        y.append(a[i][1])
                        count = a[i][0]


        x = np.array(x)
        y = np.array(y)



        x_smooth = np.linspace(x.min(),x.max(),300)
        y_smooth = spline(x,y, x_smooth)



        fig1 = plt.figure(figsize=(13,8))
        ax1 = fig1.add_subplot(111, aspect='equal')

        #for j in range(0,2):
                #ax1.add_patch(patches.Rectangle((random.randint(0,9), random.randint(0,9)), 1, 1, facecolor='red'))
        for j in b:
                ax1.add_patch(patches.Rectangle((j[0],j[1]),1,1,facecolor='red'))
        
        ax1.plot(x_smooth,y_smooth,linewidth=30.0, color="black")

        plt.ylim(lims)
        plt.xlim(lims)
        #plt.axis('off')

        plt.show(block = False)

        





draw([(5,5),(5,6),(6,6),(6,7),(7,7),(7,8),(8,8),(8,9),(9,9),(9,10)],[(1,3),(6,2)])
for i in range(1000000):
	if(i == 500000):
		plt.close()
	print(i)
draw([(5,5),(5,6),(6,6),(6,7),(7,7),(7,8),(8,8),(8,9),(9,9),(9,10)],[(7,3),(3,8)])
for i in range(1000000):
        	print(i)













'''


com_port = None     # replace with your COM port or /dev/

while not com_port:
    com_port = input("What is your com port or /dev/? ")


print("initializing")
init(com_port)
'''
