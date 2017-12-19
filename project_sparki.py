from __future__ import print_function

from sparki_learning import *


import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
from scipy.interpolate import spline
import random


COMMAND = {
	'INIT': 'z'
	'LINE_FOLLOWING': 's'
	'FINISH': 'f'
}
def cost(i,j):
	x1=i//4
	y1=i%4
	x2=j//4
	y2=j%4
	if i==j:
		return 0
	if (grid[x1][y1] or grid[x2][y2]):#if obstacle		
		return 99
	co = abs(x1-x2)+abs(y1-y2)
	if co>1:
		return 99
	else:
		return co





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


def grid(obstacle):
	p = [0]*20
	g = [p]*20
	for i in obstacle:
		g[i[0]][i[1]] = 1
	return g

def cost(i,j):
	x1=i//4
	y1=i%4
	x2=j//4
	y2=j%4
	if i==j:
		return 0
	if (grid[x1][y1] or grid[x2][y2]):#if obstacle		
		return 99
	co = abs(x1-x2)+abs(y1-y2)
	if co>1:
		return 99
	else:
		return co

def dij(n,v,goal):
	flag = []
	dist = []
	go_to = []
	u=0
	for i in range (n):
		flag.append(0)
		dist.append(99)
		go_to.append(0)
	dist[goal] = 0
	count=1
	print(dist)
	while(count<=n):
		mini=99
		for w in range (n):
			if ((dist[w]<mini) and (not flag[w])):
				mini = dist[w]
				u = w
		flag[u] = 1
		count = count+1
		for w in range (n):
			if (((dist[u]+cost(u,w))<dist[w]) and (not flag[w])):
				dist[w]= dist[u] + cost(u,w)
				go_to[w] = u
	
	go_to[goal] = -1
	route = []
	while(v != -1):
		route.append[v]
		v = go_to[v]

	grid_route = []
	for i in route:
		grid_route.append((i//(n**(1/2)),i%(n**(1/2))))
	return grid_route


'''
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

setDebug(logging.DEBUG)

while not com_port:
    com_port = input("What is your com port or /dev/? ")

print("initializing")
init(com_port)




obstacle = []


obstacle.clear()
for i in range(10):
	obstacle.append((random.randint(5,15),random.randint(5,15)))
groute = dij(400,0,399)
draw(groute, obstacle)

sendSerial(COMMAND["LINE_FOLLOWING"])


c = getSerialChar()
while(c != COMMAND["FINISH"]):
	c = getSerialChar()	
	wait(0.1)
plt.close()





obstacle.clear()
for i in range(10):
	obstacle.append((random.randint(5,15),random.randint(5,15)))
groute = dij(400,399,0)
draw(groute, obstacle)

sendSerial(COMMAND["LINE_FOLLOWING"])

c = getSerialChar()
while(c != COMMAND["FINISH"]):
	c = getSerialChar()	
	wait(0.1)
plt.close()
