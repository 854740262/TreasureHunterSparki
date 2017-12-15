lims = (0, 20)
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import random
a=[(14,14),(15,15),(2,7),(3,6)]

    



fig1 = plt.figure()
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
fig1.show()
