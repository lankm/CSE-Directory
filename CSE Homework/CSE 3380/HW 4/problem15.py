import sympy as sp

#just determines the size of the 2d array. The sizes are the dimentions.
A = sp.Matrix([[0, 2, 3],
               [1, 1,-2],
               [4, 1, 0],
               [3,-1,-1]])
n = A.cols
m = A.rows
print("the dimentionality of A is R^%d*%d\n" % (m,n))

#Assuming you want the basis for the columnspace and not the null space.
#A basis is just the pivot columns of a rref matrix
#The formatting of the output isn't great but this is a class about linalg not python
B = sp.Matrix(A.rref()[0]).columnspace()
print("Basis for A: {}".format(B))
