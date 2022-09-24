import sympy as sp

#converts coordinates Xb in basis B to the standard basis. 
#Since B is a change of coordinate matrix a simple multiplication can give the result.
def basis_coords(B, Xb):
    X = B*Xb    #Pg 221 of the book. x=Pb*[x]b
    return X

B=sp.Matrix([[0,-4,6],
             [-1,0,6],
             [-1,0,3]])
Xb=sp.Matrix([-2,6,1])

print(basis_coords(B, Xb))  #prints the answer
