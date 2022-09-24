import numpy as np
import matplotlib.pyplot as plot


def l1v(vec):   #assume u-v is given as a vector
    l1 = np.sum(np.abs(vec))
    return l1
def l2v(vec):
    l2 = np.sum(np.square(vec))
    return l2



matrix = np.zeros((2,2),dtype=float)                    #creates 2 random vectors of dimention 2
for i in range(2):
    for j in range(2):
        matrix[i,j] = np.random.randint(-6,6)
print("Matrix:\n",matrix)
print("l1:", l1v(matrix[0]-matrix[1]))
print("l2:", l2v(matrix[0]-matrix[1]))




step=100    #amount of data points generated
y1 = np.zeros(step, dtype=float)
for i in range(0,step,1):
    x=(i-step/2)/(step/2)
    y1[i]=l1v(x)

y2 = np.zeros(step, dtype=float)
for i in range(0,step,1):
    x=(i-step/2)/(step/2)
    y2[i]=l2v(x)

plot.plot(np.linspace(-1, 1, step), y1, 'ro',np.linspace(-1, 1, step), y2, 'bo')
plot.show()
