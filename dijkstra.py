#from sparki_learning import *
#import numpy
import math
grid=[[0,0,0,0],[1,1,0,1],[0,0,0,0],[1,0,1,0]]
dist = []
go_to = []
pos=0 #robot position given as index on the graph
goal=13 #desired position
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

"""
def init_adjm(sample[4][4], adjm[16][16]):
	x_i = 0;
	y_i = 0;
	x_j = 0;
	y_j = 0;
	count = 0;
	for i in range(0,16):
		for j in range(0,16):
			adjm[i][j]=999
	for i in range(0,16):
		for j in range(0,16):
		x_i = xindex(i);
		y_i = yindex(i);
		x_j = xindex(j);
		y_j = yindex(j);
		if sample[x_i][y_i] and sample[x_i][x_j]:
			count = abs(x_i-x_j)+abs(y_i-y_j)
			if count = 1:
				adjm[i][j]=1
			if count =0:
				adjm[i][j]=0;
	return None
"""
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
		grid_route.append((i//n,i%n))
	return grid_route




def loop(pos):
	dij(16,goal,dist)
	print(go_to)
	route = [pos]
	pos = go_to[pos]

	while(pos != 0):
		route.append(pos)
		pos = go_to[pos]
	print(route)
loop(pos)

