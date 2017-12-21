from __future__ import print_function

#from sparki_learning import *


import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
from scipy.interpolate import spline
import random


COMMAND = {
	'INIT': 'z',
	'LINE_FOLLOWING': 's',
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



        #x_smooth = np.linspace(x.min(),x.max(),300)
        #y_smooth = spline(x,y, x_smooth)



        fig1 = plt.figure(figsize=(20,7))
        ax1 = fig1.add_subplot(111, aspect='equal')

        #for j in range(0,2):
                #ax1.add_patch(patches.Rectangle((random.randint(0,9), random.randint(0,9)), 1, 1, facecolor='red'))
        for j in b:
                ax1.add_patch(patches.Rectangle((j[0],j[1]),1,1,facecolor='red'))
        
        ax1.plot(x,y,linewidth=30.0, color="black")

        plt.ylim((-1,20))
        plt.xlim((-1,20))
        plt.axis('off')

        plt.show()


def create_grid(obstacle):
	#g = [[0]*20]*20
	g = []
	for i in range(20):
		g.append([0]*20)
	#print(g)
	for i in obstacle:
		g[i[0]][i[1]] = 1
	return g

def cost(i,j,g):
	x1=i//20
	y1=i%20
	x2=j//20
	y2=j%20
	#print(x1,y1)
	#print(x2,y2)
	if i==j:
		return 0
	if (g[x1][y1] or g[x2][y2]):#if obstacle		
		return 99
	if((abs(x1-x2) == 1) and (abs(y1-y2) == 1)):
		return 1
	co = abs(x1-x2)+abs(y1-y2)
	if co>1:
		return 99
	else:
		return co

def create_hazard(obstacle):
	hazard = []
	index =[]
	for i in range(-2,3):
		for j in range(-2,3):
			index.append((i,j))
	for i in index:
		hazard.append((obstacle[0]+i[0],obstacle[1]+i[1]))
	return hazard

def dij(n,v,goal,g):
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
	while(count<=n):
		mini=99
		for w in range (n):
			if ((dist[w]<mini) and (not flag[w])):
				mini = dist[w]
				u = w
		flag[u] = 1
		count = count+1
		for w in range (n):
			if (((dist[u]+cost(u,w,g))<dist[w]) and (not flag[w])):
				dist[w]= dist[u] + cost(u,w,g)
				go_to[w] = u
	
	go_to[goal] = -1
	route = []
	while(v != -1):
		route.append(v)
		v = go_to[v]
	sqrt_n = int(n**(1/2))
	grid_route = []
	for i in route:
		grid_route.append((i//sqrt_n,i%sqrt_n))
	return grid_route

obstacle = []
hazard = []


obstacle.clear()
hazard.clear()
for i in range(10):
	obstacle.append((random.randint(3,16),random.randint(3,16)))
print(obstacle)

for i in obstacle:
	h = create_hazard(i)
	for j in h:
		hazard.append(j)

g = create_grid(hazard)
for i in g:
	print(i)
groute = dij(400,0,399,g)
print(groute)

draw(groute, obstacle)


'''
with open('graph2.txt', 'a') as out:
    out.write('groute = '+ str(groute)+'\n')
    out.write('obstacle = '+str(obstacle)+'\n')


plt.savefig('testplot2.png')
'''