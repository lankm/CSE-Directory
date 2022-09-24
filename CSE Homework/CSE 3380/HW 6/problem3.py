import scipy.linalg
import numpy as np

A = [[1,0,4],[-2,3,-2],[-2,0,6]]
Q, R = scipy.linalg.qr(A)

print(Q,"\n\n",R,"\n")
print(np.dot(np.transpose(Q),A))
