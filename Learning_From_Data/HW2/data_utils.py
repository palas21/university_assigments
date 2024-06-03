import numpy as np
import math

class MinMaxScaler():
    def __init__(self, x, min_limit=0, max_limit=1):
        self.x = x
        self.min = np.min(x, axis=0)
        self.max = np.max(x, axis=0)
        self.min_limit = min_limit
        self.max_limit = max_limit

    def transform(self, x):
    
        x_scaled = x
        ##############################################################################
        # TODO: Implement min max scaler function that scale a data range into       #
        # min_limit and max_limit                                                    #
        # https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.   #
        # MinMaxScaler.html                                                          #
        ##############################################################################
        # Replace "pass" statement with your code
        
        x_std = (x - self.min) / (self.max - self.min)
        
        x_scaled = x_std * (self.max_limit - self.min_limit) + self.min_limit
        
        ##############################################################################
        #                             END OF YOUR CODE                               #
        ##############################################################################
        
        return x_scaled
    
    def inverse_transform(self, x_scaled):
        
        x = x_scaled
        
        ##############################################################################
        # TODO: Implement inverse min max scaler that scale a data range back into   #
        # previous range.                                                            #
        ##############################################################################
        # Replace "pass" statement with your code
        
        x_std = (x - self.min_limit) / (self.max_limit - self.min_limit)
        
        x = x_std * (self.max - self.min) + self.min
        
        ##############################################################################
        #                             END OF YOUR CODE                               #
        ############################################################################## 
        return x


def generate_data(train_ratio=0.8):
    np.random.seed(0)
    nData = 500
    rmvRatio = 0.0

    # Raw data
    x = np.arange(0, nData, 1)
    x = np.expand_dims(x, axis=1)
    y = 3.1 * x + 2.5

    # Generate noisy data
    xData_noisy = x + np.random.normal(0, 20, size=(nData, 1))
    yData_noisy = y + np.random.normal(0, 200, size=(nData, 1))

    # Sparse data
    rmvIndx = np.random.randint(0, nData, int(nData * rmvRatio))
    xData = np.delete(xData_noisy, rmvIndx, axis=0)
    yData = np.delete(yData_noisy, rmvIndx, axis=0)

    # Shuffle indices to randomize data
    indices = np.arange(nData)
    np.random.shuffle(indices)

    # Split data into training and testing sets
    train_size = int(len(xData) * train_ratio)
    train_indices = indices[:train_size]
    test_indices = indices[train_size:]

    xTrain, yTrain = xData[train_indices], yData[train_indices]
    xTest, yTest = xData[test_indices], yData[test_indices]

    
    return xTrain, yTrain, xTest, yTest
