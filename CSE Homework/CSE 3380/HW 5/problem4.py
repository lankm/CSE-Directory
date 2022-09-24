import numpy as np
import matplotlib.pyplot as plt

def proj(matrix):
    vec = np.zeros((m,1), dtype=float)

    numer = np.dot(matrix[1], matrix[0])
    denom = np.dot(matrix[0], matrix[0])
    coef=numer/denom

    vec = coef*matrix[0]
    return vec

m=3
n=2
#matrix[0] is the basis vector while matrix[1] is the point that will be projected
matrix = np.zeros((m,n+1),dtype=float)                    #creates 2 random vectors of dimention 2
for i in range(m):
    for j in range(n):
        matrix[i,j] = np.random.randint(-5,5)

matrix=np.transpose(matrix)
proj = proj(matrix)
matrix[2]=proj
print(matrix)
matrix=np.transpose(matrix)

ax = plt.figure().add_subplot(111, projection='3d')
ax.set_xlim([-5,5])
ax.set_ylim([-5,5])
ax.set_zlim([-5,5])
ax.quiver(0,0,0,matrix[0],matrix[1],matrix[2])

matrix=np.transpose(matrix)
ax.quiver(matrix[1,0],matrix[1,1],matrix[1,2],
          matrix[2,0]-matrix[1,0],matrix[2,1]-matrix[1,1],matrix[2,2]-matrix[1,2], color='r')
plt.show()
