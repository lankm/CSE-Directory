import numpy as np
import matplotlib.pyplot as plot

n=10     #vectors
m=4      #dim
def cosSim(matrix):
    matrix=np.transpose(matrix) #done because inexes are row-column instead of column-row
    sim = np.zeros((n,n),dtype=float)
    for i in range(n):
        for j in range(n):
            numer=np.dot(matrix[i],matrix[j])
            denom=(np.linalg.norm(matrix[i])*np.linalg.norm(matrix[j]))
            sim[i,j]=numer/denom
    return sim
    


matrix = np.zeros((m,n),dtype=float)                    #creates random m by n matrix of random values -1.0 to 1.0
for i in range(m):
    for j in range(n):
        matrix[i,j] = np.random.random_sample()*2-1

matrix = cosSim(matrix)
plot.matshow(matrix, cmap=plot.cm.bwr)
plot.show()
