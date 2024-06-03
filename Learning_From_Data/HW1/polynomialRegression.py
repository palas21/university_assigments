import numpy as np

def rel_error(x, y):
    return np.max(np.abs(x - y) / (np.maximum(1e-8, np.abs(x) + np.abs(y))))

def leastSquares(X, Y, degree,vermonde=None):

    """
    Input:
    X and Y are two-dim numpy arrays.
    X dims: (N of samples, feature dims)
    Y dim: (N of samples, response dims)
    degree: Degree of the polynomial
    Output:
    Weight (Coefficient) vector
    Vandermonde Matrix
    """
    # Add a column of ones for the intercept
    if degree < 1:
        raise ValueError("Polynomial degree must be greater than or equal to 1.")
   
        
    ##############################################################################
    # TODO: Implement least square theorem for polynomial regression.            #
    #                                                                            #
    # You may not use any built in function which directly calculate             #
    # Least squares except matrix operation in numpy.  			    #
    # You need to define and compute Vandermonde matrix first.                   #
    ##############################################################################
    # Replace "pass" statement with your code
    
    # X.shape:  (100, 1)
    # Y.shape:  (100, 1)
    
    # Vermonde_matrix.shape = (100,degree+1) [1, X, X^2, ... X^degree]
    if vermonde is None:
        X_poly = X.copy()
        X_poly = np.hstack((np.ones((X.shape[0],1)), X_poly))
        
        for i in range(2, degree+1):
            X_poly = np.hstack((X_poly, X**i))
    else:
        X_poly = vermonde
        
    W = np.matmul(np.linalg.inv(np.matmul(X_poly.T, X_poly)), np.matmul(X_poly.T, Y))
    ##############################################################################
    #                             END OF YOUR CODE                               #
    ##############################################################################
    
    return W, X_poly

class gradientDescent():

    def __init__(self, x, y, w, lr, num_iters,vandermonde_matrix=None):
        if vandermonde_matrix is not None:
            self.x = vandermonde_matrix
        else:
            self.x = np.c_[np.ones((x.shape[0], 1)), x]
        self.y = y
        self.lr = lr
        self.num_iters = num_iters
        self.epsilon = 1e-4
        self.w = w.copy()
        self.weight_history = [self.w]
        self.cost_history = [np.sum(np.square(self.predict(self.x)-self.y))/self.x.shape[0]]    
    
    def gradient(self):
        gradient = np.zeros_like(self.w)
        
        ##############################################################################
        # TODO: Calculate gradient of gradient descent algorithm.                    #
        #                                                                            #
        ##############################################################################
        #  Replace "pass" statement with your code
        
        gradient = np.matmul(self.x.T, (self.predict(self.x)) - self.y) / self.x.shape[0]
        
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
        # !!WARNING-1: Use Mean Square Error between predicted and  actual y values #
        # for cost calculation.                                                      #
        #                                                                            #
        # !!WARNING-2: Be careful about lr can takes "diminishing". It will be used  #
        # for further test in the jupyter-notebook. If it takes lr decrease with     #
        # iteration as (lr =(1/k+1), here k is iteration).                           #
        ##############################################################################

        # Replace "pass" statement with your code
        
        while k < n_iterations:
            if lr == "diminishing":
                self.lr = (1/k+1)
                
            self.w -= self.lr * self.gradient()
            
            self.weight_history.append(self.w)
            
            self.cost_history.append(np.sum(np.square(self.predict(self.x)-self.y))/self.x.shape[0])
            
            if abs(self.cost_history[-1]) < self.epsilon:
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