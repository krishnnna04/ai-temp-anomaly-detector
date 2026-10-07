import numpy as np

# Normal temperature readings in degrees C (replace with your own data if you have it)
temps = np.array([27.1, 27.4, 27.8, 28.0, 28.3, 27.6, 27.9, 28.1, 27.5, 27.7])

mean = temps.mean()
std = temps.std()
print(f"const float MEAN = {mean:.2f}f;")
print(f"const float STD = {std:.4f}f;")
