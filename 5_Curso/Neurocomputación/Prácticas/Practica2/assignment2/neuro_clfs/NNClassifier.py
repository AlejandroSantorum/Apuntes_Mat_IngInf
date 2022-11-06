'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: NNClassifier.py
    Date: Mar. 11, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of abstract class NNClassifier, whose
        goal is to specify the design of future neural networks that have any learning procedure.

'''

from abc import ABCMeta,abstractmethod
import numpy as np


class NNClassifier:
    '''
        Implementation of abstract class NNClassifier, whose
        goal is to specify the design of future neural networks that have any learning procedure.
    '''

    # abstract class
    __metaclass__ = ABCMeta

    @abstractmethod
    def train(self, xtrain, ytrain):
        '''
            Its functionality must be specified in inherited classes.

            :param xtrain: data input matrix of size (n_examples, n_features).
            :param ytrain: target matrix of size (n_examples, n_classes)
            :return: None
        '''
        pass

    @abstractmethod
    def predict(self, xtest):
        '''
            Its functionality must be specified in inherited classes.

            :param xtest: data test matrix of size (n_test_examples, n_features).
            :return: data matrix of predicted classes of size (n_test_examples, n_classes).
        '''
        pass

    def error(self, ytrue, ypred, metric='acc'):
        '''
            It calculates the error of a prediction matrix given a target matrix.
            The error can be measured in different ways, depending on the input
            argument 'metric'.

            :param ytrue: data matrix of target classes of size (n_test_examples, n_classes).
            :param ypred: data matrix of predicted classes of size (n_test_examples, n_classes).
            :param metric: metric to measure error. Default accuracy (classification).
                metric='acc': returns classification accuracy.
                metric='mse': returns Mean Squared Error.
        '''
        # Accuracy
        if metric == 'acc':
            n_test = len(ytrue)
            hit_rate = 0
            for i in range(n_test):
                if np.array_equal(ytrue[i], ypred[i]):
                    hit_rate += 1
            hit_rate /= n_test
            # miss rate is the complement of hit rate
            return 1-hit_rate
        # Mean Squared Error
        if metric == 'mse': # TODO: review
            n_test = len(ytrue)
            n_outputs = len(ytrue[0])
            S = [0]*n_outputs
            for j in range(n_outputs):
                for i in range(n_test):
                    S[j] += (ytrue[i][j] - ypred[i][j])**2
            S = np.asarray(S)
            return (1/n_test)*np.sum(S)
