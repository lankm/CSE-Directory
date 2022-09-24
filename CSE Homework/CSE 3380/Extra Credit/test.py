import os

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import ImageGrid
from PIL import Image

# Load raw images
data_dir = "CSE Homework/CSE 3380/Extra Credit/faces/"
file_names = os.listdir(data_dir)
images = [np.asarray(Image.open(data_dir + file_names[i])) for i in range(len(file_names))]
images = np.array(images)

# Visualize some of the faces
fig = plt.figure(figsize=(8, 8))
grid = ImageGrid(fig, 111, nrows_ncols=(8, 8), axes_pad=0)

for ax, im in zip(grid, images[:64]):
    ax.imshow(im)
    ax.axis('off')

# Calculate the mean face
# face_mean = # TODO: Fill in the code to get the mean face image
face_mean = images.mean(0)

fig = plt.figure()
ax = fig.add_subplot(111)
ax.imshow(face_mean)

num_images, height, width = images.shape

def compute_pca(data, data_mean):
    # 1. Subtract the mean image from all images

    # 2. Vectorize the images to a 400 x 10304 matrix -- use reshape

    # 3. Create the covariance matrix -- don't forget to divide by 1 less than the number of samples

    # 4. Compute the eigendecomposition -- try np.linalg.eig

    # 5. Calculate the eigenfaces: U = XV -- you may have to multiply these differently based on the shape

    # 6. Normalize the eigenfaces to that they are unit vectors -- np.lingalg.norm helps here!
    
    # 7. Compute the weights by projected the centered data onto the eigenfaces
    
    # 8. Return the normalized eigenfaces and weights
    return eigenfaces, weights

# Compute PCA and visualize
eigenfaces, weights = compute_pca(images, face_mean)

# Visualize some eigenfaces
fig = plt.figure(figsize=(8, 8))
grid = ImageGrid(fig, 111, nrows_ncols=(4, 4), axes_pad=0)

for ax, im in zip(grid, eigenfaces[:16]):
    ax.imshow(im.reshape(height, width))
    ax.axis('off')

def reconstruct(weights, eigenfaces, X_mean, img_size, img_idx, n_comps=400):
    """TODO: Reconstruct the image given by `img_idx` using `n_comps` eigenfaces.
    Don't forget to reshape the image so that it is no longer a vector!
    """
    return recovered_img

img_idx = 200
n_comps = 400

recovered_img = reconstruct(weights, eigenfaces, face_mean.reshape(-1), [height, width], img_idx, n_comps)

# Visualize original and reconstructed
fig = plt.figure()
ax1 = fig.add_subplot(121)
ax2 = fig.add_subplot(122)
ax1.imshow(images[img_idx])
ax2.imshow(recovered_img)
