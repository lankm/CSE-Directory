import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

def normalize(v):
    norm = np.linalg.norm(v)
    if norm == 0:
        return v
    return v / norm

def look_at(src, to, up):
    """Creates a camera matrix located at `src` looking towards `to`."""
    forward = normalize(src - to)
    right = np.cross(normalize(up), forward)
    up = np.cross(forward, right)

    forward = -forward

    camera_matrix = np.array([
        [right[0], right[1], right[2], -np.dot(right, src)],
        [up[0], up[1], up[2], -np.dot(up, src)],
        [forward[0], forward[1], forward[2], -np.dot(forward, src)],
        [0, 0, 0, 1]
    ])
    return camera_matrix
    

camera = np.array([0.0, 1.0, 0.0])
at = np.array([0.0, 0.0, 0.0])
up = np.array([1.0, 0.0, 0.0])

# Build camera matrix
camera_matrix = look_at(camera, at, up)
print(camera_matrix)
