#formatting of output fol col space could be better but this isn't a class on python

import sympy as sp

A = sp.Matrix([[3,8,-5],
              [3,-6,-7],
              [3,4,2]])
B = sp.Matrix([-1,-1,3])

R = A.col_insert(3,B).rref()[0]
print("RREF: {}".format(R))  #gets rref and prints it

#A = np.array(A).astype(np.float64)  #converts matrix to array. don't need to convert back

C = A.columnspace()                                 #columnspace
print("\ncol space: {}".format(C))

S = A.LUsolve(B)                                    #solutions
print("\nsolutions: {}".format(S))

N = A.nullspace()                                   #null space
print("\nnull space: {}".format(N))
