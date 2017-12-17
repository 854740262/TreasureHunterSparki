lims = (0, 20)
#import sparki_learning
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import random
a=[(14,14),(15,15),(2,7),(3,6)]

    

#plt.ion()

fig1 = plt.figure(figsize=(13,8))
ax1 = fig1.add_subplot(111, aspect='equal')

             
for i in range(len(a)):
    ax1.add_patch(
    patches.Rectangle((a[i][0], a[i][1]), 1, 1, facecolor='black'))
             
for j in range(0,2):
    ax1.add_patch(
    patches.Rectangle((random.randint(0,9), random.randint(0,9)), 1, 1, facecolor='red'))
plt.ylim(lims)
plt.xlim(lims)
plt.axis('off')
plt.show()




fig2 = plt.figure(figsize=(10,7))
ax2 = fig2.add_subplot(111, aspect='equal')

             
for i in range(len(a)):
    ax2.add_patch(
    patches.Rectangle((a[i][0], a[i][1]), 1, 1, facecolor='black'))
             
for j in range(0,2):
    ax2.add_patch(
    patches.Rectangle((random.randint(0,9), random.randint(0,9)), 1, 1, facecolor='red'))
plt.ylim(lims)
plt.xlim(lims)
plt.axis('off')
plt.show()

