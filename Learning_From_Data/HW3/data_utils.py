import numpy as np

np.random.seed(42)

def generate_synthetic_data(num_samples_per_class, mean1, mean2, cov_matrix):
	np.random.seed(42)
	class1_samples = np.random.multivariate_normal(mean1, cov_matrix, num_samples_per_class)
	class2_samples = np.random.multivariate_normal(mean2, cov_matrix, num_samples_per_class)
	return class1_samples, class2_samples


def generate_data():
	np.random.seed(42)
	num_samples_per_class = 50
	mean_class1 = [2, 3]
	mean_class2 = [7, 6]
	covariance_matrix = [[1, 0.5], [0.5, 1]]

	# Generate synthetic data
	class1_data, class2_data = generate_synthetic_data(num_samples_per_class, mean_class1, mean_class2, covariance_matrix)

	# Labels for the classes (0 and 1)
	class1_labels = np.zeros(num_samples_per_class)
	class2_labels = np.ones(num_samples_per_class)

	# Combine the data and labels
	synthetic_data = np.concatenate([class1_data, class2_data], axis=0)
	synthetic_labels = np.concatenate([class1_labels, class2_labels])

	# Shuffle the data
	shuffle_indices = np.arange(synthetic_data.shape[0])
	np.random.shuffle(shuffle_indices)

	synthetic_data = synthetic_data[shuffle_indices]
	synthetic_labels = synthetic_labels[shuffle_indices]

	# Split the data into training and testing sets (80% training, 20% testing)
	split_ratio = 0.8
	num_train_samples = int(split_ratio * synthetic_data.shape[0])

	x_train = synthetic_data[:num_train_samples].T
	y_train = synthetic_labels[:num_train_samples].astype(int).reshape(1, -1)[0]

	x_test = synthetic_data[num_train_samples:].T
	y_test = synthetic_labels[num_train_samples:].astype(int).reshape(1, -1)[0]
	return x_train, x_test, y_train, y_test

class MinMaxScaler():
    def __init__(self, min_limit=0, max_limit=1):
        self.min_limit = min_limit
        self.max_limit = max_limit
        self.min = None
        self.max = None
  
    def fit(self, x):
        self.min = np.min(x, axis=1)
        self.max = np.max(x, axis=1)

    def transform(self, x):
        if self.min is None or self.max is None:
            raise ValueError("MinMaxScaler must be fit before transform.")
        ##############################################################################
        # TODO: Implement min max scaler function that scale a data range into       #
        # min_limit and max_limit                                                    #
        # https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.   #
        # MinMaxScaler.html                                                          #
        ##############################################################################
        # Replace "pass" statement with your code
        
        # Calculate the range for each feature
        feature_range = self.max - self.min
        
        # Create a copy of the input data
        x_scaled = x.copy()
        x_scaled_temp = np.zeros_like(x, dtype=float)
        
        
        # Scale non-zero range features
        non_zero_range_indices = np.where(feature_range != 0)[0]

        for i in non_zero_range_indices:
            
            temp = (x_scaled[i, :] - self.min[i]) / float(feature_range[i]) * (self.max_limit - self.min_limit) + self.min_limit
            indices = np.where(x_scaled[i, :] != 0)[0]
            x_scaled_temp[i, indices] = temp[indices]
            
        ##############################################################################
        #                             END OF YOUR CODE                               #
        ##############################################################################

        return x_scaled_temp
    
    def inverse_transform(self, x_scaled):
        
        if self.min is None or self.max is None:
            raise ValueError("MinMaxScaler must be fit before inverse_transform.")
        
        x = x_scaled
        
        ##############################################################################
        # TODO: Implement inverse min max scaler that scale a data range back into   #
        # previous range.                                                            #
        ##############################################################################
        # Replace "pass" statement with your code
        
        x = (x - self.min_limit) / (self.max_limit - self.min_limit) * (self.max - self.min) + self.min
        
        ##############################################################################
        #                             END OF YOUR CODE                               #
        ##############################################################################        
        return x
    
        ##############################################################################