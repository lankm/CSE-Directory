import numpy as np
import matplotlib.pyplot as mp

N=2
M=2

#X=np.random.randint(5, size=(N,M))  # A)
X=np.random.randint(5, size=(N,M)) 

cov = np.dot(np.transpose(X),X)                 # B)
val, vec = np.linalg.eig(cov)

u = np.dot(X,vec)                 # C)
u = np.transpose(u)
u[0]= u[0]/np.linalg.norm(u[0])
u[1]= u[1]/np.linalg.norm(u[1])
u = np.transpose(u)

U,S,V = np.linalg.svd(X, full_matrices=False)   # D)

print("===Problem 3===")                        # E)
print("x:\n", X)
print("x.t*x:\n", cov)
print("eigenvectors:\n", vec)
print("=====================")
print("X*eigenvectors:\n", u)   # U and u are equal. sometimes nan pops up tho. the negative sign on values are different sometimes. the matricies are flipped sometimes.
print("U=(1/o)Xv:\n", U)        # U and u are symettric
print("=====================")
print("eigenvalues:", val)  #the singular vaues are the square root of the eigenvalues. this is expected
print("o:\n", S)