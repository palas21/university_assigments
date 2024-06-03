import numpy as np

def rel_error(x, y):
    return np.max(np.abs(x - y) / (np.maximum(1e-8, np.abs(x) + np.abs(y))))


def leastSquares(X, Y):
    """
    Input:
    X and Y are two-dim numpy arrays.
    X dims: (N of samples, feature dims)
    Y dim: (N of samples, response dims)
    
    Output:
    Weight (Coefficient) vector
    
    """
    ##############################################################################
    # TODO: Implement least square theorem.                                      #
    #                                                                            #
    # You may not use any built in function which directly calculate             #
    # Least squares except matrix operation in numpy.                            #
    ##############################################################################
    # Replace "pass" statement with your code
    
    X = np.hstack((np.ones((X.shape[0],1)), X)) # [1,X]
    
    #w = np.matmul(np.linalg.inv(np.matmul(X.T, X)), np.matmul(X.T, Y)) # [b,W]
    w = np.dot(np.dot(np.linalg.inv(np.dot(X.T, X)), X.T), Y) 
    ##############################################################################
    #                             END OF YOUR CODE                               #
    ##############################################################################
    return w

class gradientDescent():
    def __init__(self, x, y, w, lr, num_iters):
        self.x = np.c_[np.ones((x.shape[0], 1)), x]
        self.y = y
        self.lr = lr
        self.num_iters = num_iters
        self.epsilon = 1e-4
        self.w = w.copy()
        self.weight_history = [self.w]
        self.cost_history = [np.sum(np.square(self.predict(self.x)-self.y))/self.x.shape[0]]
        
    def gradient(self):
        gradient = np.zeros_like(self.w) # [b,W]
        ##############################################################################
        # TODO: Calculate gradient of gradient descent algorithm.                    #
        #                                                                            #
        ##############################################################################
        #  Replace "pass" statement with your code
        
        gradient = np.matmul(self.x.T, self.predict(self.x) - self.y) / self.x.shape[0] # I ommit the -2 since it is a scalar factor that can be change with the learning rate. 
        
        ##############################################################################
        #                             END OF YOUR CODE                               #
        ##############################################################################
        
        return gradient
    
    
    def fit(self,lr=None, n_iterations=None):
        k = 0
        if n_iterations is None:
            n_iterations = self.num_iters
        if lr != None and lr != "diminishing":
            self.lr = lr
            
        ##############################################################################
        # TODO: Implement gradient descent algorithm.                                #
        #                                                                            #
        # You may not use any built in function which directly calculate             #
        # gradient.                                                                  #
        # Steps of gradient descent algorithm:                                       #
        #   1. Calculate gradient of cost function. (Call gradient() function)       #
        #   2. Update w with gradient.                                               #
        #   3. Log weight and cost for plotting in weight_history and cost_history.  #
        #   4. Repeat 1-3 until the cost change converges to epsilon or achieves     #
        # n_iterations.                                                              #
        # !!WARNING-1: Use Mean Square Error between predicted and  actual y values  #
        # for cost calculation.                                                    #
        #                                                                            #
        # !!WARNING-2: Be careful about lr can takes "diminishing". It will be used  #
        # for further test in the jupyter-notebook. If it takes lr decrease with     #
        # iteration as (lr =(1/k+1), here k is iteration).                           #
        ##############################################################################

        # Replace "pass" statement with your code
   
        

        while k < n_iterations:
            
            if lr == "diminishing":
                self.lr = 1/(k+1)
                
            gradient = self.gradient()
            
            self.w -= self.lr * gradient
            
            self.weight_history.append(self.w)
            
            self.cost_history.append(np.sum(np.square(self.predict(self.x)-self.y))/self.x.shape[0])
            
            if np.abs(self.cost_history[-1]) < self.epsilon:
                break
            
            k += 1
        
        ##############################################################################
        #                             END OF YOUR CODE                               #
        ##############################################################################
        return self.w, k
    
    def predict(self, x):
        
        y_pred = np.zeros_like(self.y)

        y_pred = x.dot(self.w)
        
        return y_pred