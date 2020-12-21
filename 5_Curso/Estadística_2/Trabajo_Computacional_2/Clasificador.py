################################################################################
#   Authors:
#       · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
#       · Jose Manuel Chacon Aguilera - josem.chacon@estudiante.uam.es
#   File: Clasificador.py
#   Date: Dec. 23, 2020
#   Project: 2nd Computational Assignment of Statistics II
#   File Description: Implementation of severals machine learning models
#
################################################################################

import numpy as np



class RegresionLineal:
    '''
        Main references:
            [1] - LinearRegression scikit-learn library:
            https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.LinearRegression.html
    '''

    def __init__(self):
        self.Beta = None


    def fit(self, xdata, ydata):
        '''
            It calculates estimator Beta for given xdata matrix and ydata vector.
            It uses normal equation in order to fit the model.
        '''
        # Beta estimator = (X^T * X)^{-1} * X^T * Y
        xtx = np.linalg.inv(np.matmul(np.transpose(xdata), xdata))
        self.Beta = np.matmul(np.matmul(xtx, np.transpose(xdata)), ydata)

        return self


    def predict(self, xdata):
        '''
            Predict using the linear model.
        '''
        return np.matmul(xdata, self.Beta)


    def score(self, xdata, ydata):
        '''
            It calculates the coefficient of determination R^2 of the prediction.
            The coefficient R^2 is defined as (1 - u/v), where u is the residual
            sum of squares ((y_true - y_pred) ** 2).sum() and v is the total sum
            of squares ((y_true - y_true.mean()) ** 2).sum().
        '''
        # Calculating predictions
        y_pred = self.predict(xdata)
        # Calculating R^2 coefficient.
        u = ((ydata - y_pred) ** 2).sum()
        v = ((y_true - y_true.mean()) ** 2).sum()
        return 1 - u/v




class RegresionLogistica:
    '''
        Main references:
            [1] - LogisticRegression scikit-learn library:
            https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.LogisticRegression.html
    '''

    def __init__(self, learning_rate=0.001, nepochs=100):
        self.W = None
        self.lr = learning_rate
        self.nepochs = nepochs


    def fit(self, xdata, ydata):
        '''
            It calculates estimator W for given xdata matrix and ydata vector.
            It uses gradient descent algorithm.
        '''
        # number of train examples
        n_data = xdata.shape[0]
        # intercept = column of ones
        intercept = np.ones((n_data, 1))
        # stacking intercept + xdata
        xdata = np.hstack((intercept, xdata))
        # number of features
        n_feat = xdata.shape[1]

        # Generating random initial weights in [-0.5, 0.5]
        # Remeber n_feat includes intercept column
        self.W = np.random.uniform(-0.5, 0.5, size=n_feat)

        for epoch in range(self.nepochs):
            for j in range(n_data):
                # evaluating sigmoid function in W.T * x_j
                sig = sigmoid(np.dot(xdata[j,:], self.W))
                # updating weights
                self.W = self.W - self.lr*(sig - ydata[j])*xdata[j,:]

        return self


    def predict(self, xdata):
        '''
            Predict using the linear model.
        '''
        # number of train examples
        n_data = xdata.shape[0]
        # intercept = column of ones
        intercept = np.ones((n_data, 1))
        # stacking intercept + xdata
        xdata = np.hstack((intercept, xdata))

        y_pred = []
        for j in range(n_data):
            # calculate probability of belonging to class 1
            sig = sigmoid(np.dot(self.W, xdata[j,:]))
            if sig >= 0.5: # predicted class 1
                y_pred.append(1)
            else: # predicted class 0
                y_pred.append(0)

        return np.asarray(y_pred, dtype="object")


    def score(self, xdata, ydata):
        '''
            Return the mean accuracy on the given test data and labels.
        '''
        y_pred = self.predict(xdata)
        return sum(ydata == y_pred)/len(y_pred)
