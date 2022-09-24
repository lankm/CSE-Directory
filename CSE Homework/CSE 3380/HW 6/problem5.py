import matplotlib.pyplot as mp
import numpy as np

data = np.loadtxt("CSE Homework\CSE 3380\HW 6\dataset2.txt")    #change as needed. Only works on my machine.
data = np.transpose(data)
x=data[0]
y=data[1]

A = np.vstack([x **2, x, np.ones(len(x))]).T
m, n, c = np.linalg.lstsq(A, y, rcond=None)[0]

mp.plot(x, y, "bo")
mp.plot(x, m*x**2+n*x+c, "r")
mp.show()
