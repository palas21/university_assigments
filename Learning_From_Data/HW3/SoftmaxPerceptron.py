import numpy as np
from tqdm import tqdm
import matplotlib.pyplot as plt

np.random.seed(42)  # Set random seed if needed
class SoftmaxPerceptron:
    def __init__(self, weights, learning_rate=0.01, max_iter=1000):
        self.learning_rate = learning_rate
        self.max_iter = max_iter
        self.weights_ = weights
        
    def F(self, x):
        
        return x.T @ self.weights + self.bias
     
    def sigmoid(self, Z):
        """
        Computes the sigmoid value for all values in vector Z.
        """                                  
        
        sigmoid_val = 1 / (1 + np.exp(-Z))

        return sigmoid_val

    def h_theta(self, X):
        """
        Computes the value of the hypothesis according to the logistic regression rule.
        """                                
        
        h_theta = self.sigmoid(self.F(X))
        
        return h_theta 

    def predict(self, X):
        if self.weights is None:
            raise ValueError("Model has not been trained yet.")

        predictions = np.sign(np.dot(X.T, self.weights).flatten() + self.bias)
        return predictions
    
    def evaluationMetrics(self,y_true, y_pred):
        # Return the evaluation metrics for 2 classes
        
        true_pos_1 = np.sum((y_pred == 1) & (y_true == 1))
        true_neg_1 = np.sum((y_pred != 1) & (y_true != 1))
        false_pos_1 = np.sum((y_pred == 1) & (y_true != 1))
        false_neg_1 = np.sum((y_pred != 1) & (y_true == 1))
        
        true_pos_2 = np.sum((y_pred == -1) & (y_true == -1))
        true_neg_2 = np.sum((y_pred != -1) & (y_true != -1))
        false_pos_2 = np.sum((y_pred == -1) & (y_true != -1))
        false_neg_2 = np.sum((y_pred != -1) & (y_true == -1))
        
        accuracy_1 = (true_pos_1 + true_neg_1) / (true_pos_1 + true_neg_1 + false_pos_1 + false_neg_1)
        accuracy_2 = (true_pos_2 + true_neg_2) / (true_pos_2 + true_neg_2 + false_pos_2 + false_neg_2)
        accuracy_ = (accuracy_1, accuracy_2)
        
        precision_1 = true_pos_1 / (true_pos_1 + false_pos_1)
        precision_2 = true_pos_2 / (true_pos_2 + false_pos_2)
        precision_ = (precision_1, precision_2)
        
        recall_1 = true_pos_1 / (true_pos_1 + false_neg_1)
        recall_2 = true_pos_2 / (true_pos_2 + false_neg_2)
        recall_ = (recall_1, recall_2)
        
        f1_1 = 2 * (precision_1 * recall_1) / (precision_1 + recall_1)
        f1_2 = 2 * (precision_2 * recall_2) / (precision_2 + recall_2)
        f1_ = (f1_1, f1_2)
        
        return accuracy_, precision_, recall_, f1_
        
    def fit_sgd(self, X, y, x_test = None, y_test = None, metricMatrix = False):
        np.random.seed(42)

        num_features, num_samples = X.shape  # Get the shape of the input data

        # Initialize weights
        self.weights = self.weights_[1:].reshape(-1, 1)
        self.bias = self.weights_[0]
        
        accuracy_history_train = []  # Initialize loss history
        accuracy_history_test = []  # Initialize loss history
        ##############################################################################
        # TODO: Implement stochastic gradient descent (SGD) to train the logistic    #
        # regression model.                                                          #
        ##############################################################################
        # This function implements stochastic gradient descent (SGD) to train a      #
        # perceptron model. It iterates over the training samples for a              #
        # specified number of iterations (given by max_iter), updating the model     #
        # parameters (weights and bias) after processing each sample. SGD is a       #
        # variant of gradient descent that updates the parameters based on the       #
        # gradient of the loss function computed with respect to each individual     #
        # sample. This makes it computationally more efficient than batch gradient   #
        # descent, particularly for large datasets. The function computes the        #
        # logistic loss and its gradient for each sample, and updates the weights    #
        # and bias accordingly. The accuracy on the training set is computed after   #
        # each iteration and stored in the accuracy_history list. The function       #
        # returns this accuracy history to monitor the training progress.            #
        ##############################################################################

        # 1/N sum log (1 + e^(-y * (xT.w + b))) 
        
        # weight_history = []
        cost_history = []
        train_metrics = []
        test_metrics = []

        # Stochastic Gradient Descent
        for k in tqdm(range(0,self.max_iter), desc="Epoch"):
            
            X_copy = X.copy()
            while not X_copy.shape[1] == 0:
                
                idx = np.random.randint(0, X_copy.shape[1])
                x = X_copy[:, idx].reshape(-1, 1)
                X_copy = np.delete(X_copy, idx, axis=1)
                
                grad_w = - y[idx] / float(np.exp(y[idx] * self.F(x)) + 1) / num_samples * x 
                
                grad_b = - y[idx] / float(np.exp(y[idx] * self.F(x)) + 1) / num_samples
            
                self.weights -= self.learning_rate * grad_w
                self.bias -= self.learning_rate * grad_b 
            
            cost = np.sum(np.log(1 + np.exp(-y.reshape(-1,1) * self.F(X)))) / num_samples # DOGRU OLAN BU
            
            cost_history.append(cost)
                
            if metricMatrix:
                # Calculate Metrics
                train_predictions = self.predict(X)
                train_accuracy, train_precision, train_recall, train_f1 = self.evaluationMetrics(y, train_predictions)
                train_metrics.append([train_accuracy, train_precision, train_recall, train_f1]) # Hold as 2D array
                
                if x_test is not None and y_test is not None:
                    
                    test_predictions = self.predict(x_test)
                    test_accuracy, test_precision, test_recall, test_f1 = self.evaluationMetrics(y_test, test_predictions)
                    test_metrics.append([test_accuracy, test_precision, test_recall, test_f1])
            
            # Calculate predictions for training set
            train_predictions = self.predict(X)
            correctly_classified_train = np.sum(train_predictions == y) # np.sign function for -1, 1
            percent_correct_train = (correctly_classified_train / len(y)) * 100
            accuracy_history_train.append(percent_correct_train)
            
            if x_test is not None and y_test is not None:
                test_predictions = self.predict(x_test)
                correctly_classified_test = np.sum(test_predictions == y_test)
                percent_correct_test = (correctly_classified_test / len(y_test)) * 100
                accuracy_history_test.append(percent_correct_test)
                
            k += 1
            
        if metricMatrix:
            return accuracy_history_train, accuracy_history_test, train_metrics, test_metrics

        return accuracy_history_train, accuracy_history_test
      
    def fit_gd_regularized(self, X, y, regularization_strength, x_test = None, y_test = None, metricMatrix = False):
        np.random.seed(42)
        num_features, num_samples = X.shape  # Get the shape of the input data
        X_with_bias = X
        self.weights = self.weights_[1:].reshape(-1, 1)
        self.bias = self.weights_[0]

        accuracy_history_train = []  # Initialize empty list to store accuracy history
        accuracy_history_test = []  # Initialize empty list to store accuracy history
        ##############################################################################
        # TODO: Implement regularized gradient descent (GD) to train the softmax      #
        # perceptron model. The regularization_strength parameter controls the        #
        # strength of regularization applied to the model. Regularization helps      #
        # prevent overfitting by penalizing large parameter values. The function      #
        # iterates over the training samples for a specified number of iterations    #
        # (given by max_iter), updating the model parameters (weights and bias)       #
        # after processing each sample. The loss function used is the cross-entropy  #
        # loss with L2 regularization. It computes the loss and its gradient for     #
        # each sample, including a regularization term to penalize large weights.    #
        # The weights excluding the bias term are regularized using L2 regularization.#
        # The accuracy on the training set is computed after each iteration and      #
        # stored in the accuracy_history list. The function returns this accuracy    #
        # history to monitor the training progress.                                  #
        ##############################################################################

        # 1/N sum log (1 + e^(-y * (xT.w + b))) + lambda * w^2 

        cost_history = []
        train_metrics = []
        test_metrics = []

        # Stochastic Gradient Descent
        X_copy = X.copy()
        y_copy = y.copy().reshape(-1, 1)
          
        for k in tqdm(range(0,self.max_iter), desc="Epoch"):
            
            # Calculate the gradient
            grad_w = - X_copy @ (y_copy / (np.exp(y_copy * self.F(X_copy)) + 1)) / num_samples + regularization_strength * self.weights / num_samples
            
            grad_b = - np.sum(y_copy / (np.exp(y_copy * self.F(X_copy)) + 1)) / num_samples
            
            self.weights -= self.learning_rate * grad_w
            self.bias -= self.learning_rate * grad_b

            cost = np.sum(np.log(1 + np.exp(-y.reshape(-1,1) * self.F(X_copy)))) / num_samples + regularization_strength * np.sum(self.weights ** 2) / num_samples
            
            cost_history.append(cost)
                
            if metricMatrix:
                train_predictions = self.predict(X)
                train_accuracy, train_precision, train_recall, train_f1 = self.evaluationMetrics(y, train_predictions)
                train_metrics.append([train_accuracy, train_precision, train_recall, train_f1]) # Hold as 2D array
                
                if x_test is not None and y_test is not None:
                    
                    test_predictions = self.predict(x_test)
                    test_accuracy, test_precision, test_recall, test_f1 = self.evaluationMetrics(y_test, test_predictions)
                    test_metrics.append([test_accuracy, test_precision, test_recall, test_f1])
                        
            # Calculate predictions for training set
            train_predictions = self.predict(X)
            correctly_classified_train = np.sum(np.sign(train_predictions) == y) # np.sign function for -1, 1
            percent_correct_train = (correctly_classified_train / len(y)) * 100
            accuracy_history_train.append(percent_correct_train)
            
            if x_test is not None and y_test is not None:
                test_predictions = self.predict(x_test)
                correctly_classified_test = np.sum(np.sign(test_predictions) == y_test)
                percent_correct_test = (correctly_classified_test / len(y_test)) * 100
                accuracy_history_test.append(percent_correct_test)
        
            k += 1
        
        if metricMatrix:
            return accuracy_history_train, accuracy_history_test, train_metrics, test_metrics
        
        return accuracy_history_train, accuracy_history_test