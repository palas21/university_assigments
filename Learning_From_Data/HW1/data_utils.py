import numpy as np
import math

def generate_data():


	np.random.seed(0)
	nData = 200
	rmvRatio = 0.0

	# Raw data
	x = np.arange(0, nData, 1)
	x = np.expand_dims(x, axis=1)
	y = 3.1*x+2.5

	# Generate noisy data
	xData_noisy = x + np.random.normal(0, 10, size=(nData,1))
	yData_noisy = y + np.random.normal(0, 100, size=(nData,1))


	# Sparse data
	rmvIndx = np.random.randint(0, nData, int(nData*rmvRatio))
	xData = np.delete(xData_noisy, rmvIndx,   axis=0)
	yData = np.delete(yData_noisy, rmvIndx,   axis=0)
	
	
	return xData, yData, x, y
	
def generate_poly_data_q12():


	# Set seed for reproducibility
	np.random.seed(42)

	# Number of samples
	num_samples = 100

	# Generate random X values
	X = np.random.uniform(-5, 5, num_samples)

	# Define polynomial coefficients for a quadratic polynomial
	true_coefficients = [1, -2, 0.5]  # Adjust coefficients based on your polynomial degree
	# The coefficients are ordered as [bias, X, X^2]

	# Generate noise
	noise = np.random.normal(0, 2, num_samples)

	# Generate polynomial features
	X_poly = np.column_stack([X**i for i in range(len(true_coefficients))])

	# Generate target variable (y) using polynomial regression equation
	y = X_poly.dot(true_coefficients) + noise
	
	return np.expand_dims(X, axis=1), np.expand_dims(y, axis=1)

