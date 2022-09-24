import matplotlib.pyplot as mp
import numpy as np

data = np.loadtxt("CSE Homework\CSE 3380\HW 6\dataset1.txt")    #change as needed. Only works on my machine.
data = np.transpose(data)
x=data[0]
y=data[1]

A = np.vstack([x, np.ones(len(x))]).T
m, c = np.linalg.lstsq(A, y, rcond=None)[0]

mp.plot(x, y, "bo")
mp.plot(x, m*x+c, "r")
mp.show()
