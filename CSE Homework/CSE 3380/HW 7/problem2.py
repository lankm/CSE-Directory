import numpy as np
import matplotlib.pyplot as mp

A = [[1,-2],[-4,1]]
val, vec = np.linalg.eig(A)
vec=np.transpose(vec)

mp.plot([0,1],[0,0], "k-",[0,0],[0,1], "k-") #standard basis
mp.plot([0,A[0][0]],[0,A[1][0]], "b-",[0,A[0][1]],[0,A[1][1]], "b-") #col A
mp.plot([0,vec[0][0]],[0,vec[0][1]], "r-",[0,vec[1][0]],[0,vec[1][1]], "r-") #eigenbasis

mp.grid()
mp.xlim([-5,5])
mp.ylim([-5,5])
mp.show()
