'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: 1L_Multiperceptron.py
    Date: Mar. 20, 2021
    Project: Assignment 2 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of class 1L_Multiperceptron, whose
        goal is to execute forward propagation and backward propagation in order to
        learn the best weights. It inherits NNClassifier class.

'''

from neuro_clfs.NNClassifier import NNClassifier
from neuro_clfs.NeuralNetwork import NeuralNetwork
from neuro_clfs.Layer import Layer
from neuro_clfs.Neuron import Neuron

import numpy as np


def bipolar_sigmoid(x):
    return 2/(1+np.exp(-x)) - 1

def bipolar_sigmoid_derivative(x):
    return 0.5 * (1 + bipolar_sigmoid(x)) * (1 - bipolar_sigmoid(x))

def sigmoid(z):
    return 1/(1 + np.exp(-z))

def sigmoid_derivative(z):
    return sigmoid(z)*(1 - sigmoid(z))



class L1_Multiperceptron(NNClassifier):
    '''
        Implementation of class Multiperceptron, whose goal is to execute multilayer perceptron
        learning algorithm. It inherits NNClassifier class.
    '''

    def __init__(self, n_inputs, n_hidden, n_outputs, alpha=1.0, activation='bipolar', n_epochs=100, verbose=False):
        '''
            Constructor of a new object '1L_Multiperceptron'.

            :param n_inputs: Number of inputs of the neural network
            :param n_outputs: Number of outputs of the neural network
            :param alpha: (Optional) Learning parameter alpha. Default=1.0
            :param activation: (Optional) Activation function of the neurons.
                activation='bipolar': it uses bipolar sigmoid function.
                activation='sigmoid': it uses binary sigmoid function.
            :param verbose: (Optional) If set to True, feedback of each epoch is printed.
            :param n_epochs: (Optional) Number of epochs. Default=100
            :return: None
        '''
        self.n_inputs = n_inputs
        self.n_hidden = n_hidden
        self.n_outputs = n_outputs
        self.alpha = alpha
        self.activation = activation
        if activation == 'bipolar':
            self.neuron_types = Neuron.Type.BipolarSigmoid
            self.activation_func = bipolar_sigmoid
            self.activation_func_deriv = bipolar_sigmoid_derivative
        elif activation == 'sigmoid':
            self.neuron_types = Neuron.Type.Sigmoid
            self.activation_func = sigmoid
            self.activation_func_deriv = sigmoid_derivative
        self.n_epochs = n_epochs
        self.verbose = verbose
        self.epoch_errors = []
        self.epoch_accs = []
        # building neural network with given data
        self.nn = NeuralNetwork()

        # creating input layer and its neurons
        input_layer = Layer()
        input_layer.add(Neuron(Neuron.Type.Bias))
        for i in range(n_inputs):
            input_layer.add(Neuron(Neuron.Type.Direct))

        hidden_layer = Layer()
        hidden_layer.add(Neuron(Neuron.Type.Bias))
        for i in range(n_hidden):
            hidden_layer.add(Neuron(self.neuron_types))

        input_layer.connectLayer(hidden_layer, Layer.WeightMode.AdalineWeight)
        #input_layer.connectLayer(hidden_layer, Layer.WeightMode.DebugWeight)

        # creating output layer and its neurons
        output_layer = Layer()
        for i in range(n_outputs):
            output_layer.add(Neuron(self.neuron_types))

        hidden_layer.connectLayer(output_layer, Layer.WeightMode.AdalineWeight)
        #hidden_layer.connectLayer(output_layer, Layer.WeightMode.DebugWeight)

        # adding layers to neural network
        self.nn.add(input_layer)
        self.nn.add(hidden_layer)
        self.nn.add(output_layer)



    def _forward_propagation(self, id):
        self.X = []
        self.Z_in = []
        self.Z = []
        self.Y_in = []
        self.Y = []

        # Paso 3
        self.nn.trigger()
        for neuron in self.nn.layers[0].neurons: # INCLUDING BIAS
            self.X.append(neuron.f_x)

        # Paso 4
        self.nn.propagate()
        for neuron in self.nn.layers[1].neurons[1:]:
            self.Z_in.append(neuron.value)
        self.nn.trigger()
        for neuron in self.nn.layers[1].neurons[1:]:
            self.Z.append(neuron.f_x)

        # Paso 5
        self.nn.propagate()
        for neuron in self.nn.layers[2].neurons:
            self.Y_in.append(neuron.value)
        self.nn.trigger()
        for neuron in self.nn.layers[2].neurons:
            self.Y.append(neuron.f_x)


    def _backward_propagation(self, ytrain_array, id):
        self.Delta_W = np.zeros((len(self.nn.layers[1].neurons), len(self.nn.layers[2].neurons)))
        # Paso 6
        deltas_k = []
        for k in range(len(self.Y)):
            del_k = (ytrain_array[k] - self.Y[k]) * self.activation_func_deriv(self.Y_in[k])
            deltas_k.append(del_k)
            for j in range(len(self.Z)):
                self.Delta_W[j+1][k] = self.alpha * del_k * self.Z[j]
            self.Delta_W[0][k] = self.alpha * del_k

        self.Delta_V = np.zeros((len(self.nn.layers[0].neurons), len(self.nn.layers[1].neurons)-1))
        # Paso 7
        for j,neuron in enumerate(self.nn.layers[1].neurons[1:]):
            delta_in_j = 0
            for k in range(len(self.nn.layers[2].neurons)):
                delta_in_j += deltas_k[k] * neuron.connections[k].weight
            del_j = delta_in_j * self.activation_func_deriv(self.Z_in[j])
            for i in range(len(self.X)):
                self.Delta_V[i][j] = self.alpha * del_j * self.X[i]


    def _update_nn_weights(self):
        # Paso 8
        for i,neuron in enumerate(self.nn.layers[0].neurons):
            for j,conn in enumerate(neuron.connections[1:]):
                conn.update_weight(self.Delta_V[i][j])

        for j,neuron in enumerate(self.nn.layers[1].neurons):
            for k,conn in enumerate(neuron.connections):
                conn.update_weight(self.Delta_W[j][k])



    def train(self, xtrain, ytrain):
        '''
            Input parameters and return explained in parent class.

            It trains the Multiperceptron object accordingly to perceptron algorithm.
        '''
        n_train = len(xtrain)

        # getting input and output layers
        input_layer = self.nn.layers[0]

        # training loop
        for k in range(self.n_epochs):
            if self.verbose:
                print("Epoch", k)

            # an epoch trains over all examples
            for i in range(n_train):
                # init input layer values
                for (j, neuron) in enumerate(input_layer.neurons[1:]):
                    neuron.initialise(xtrain[i][j])

                # calculate neurons values
                self._forward_propagation(i)

                # backpropagate gradient
                self._backward_propagation(ytrain[i], i)

                # update weights
                self._update_nn_weights()

            ypred_epoch = self.predict(xtrain)
            self.epoch_errors.append(self.error(ytrain, ypred_epoch, metric='mse'))
            self.epoch_accs.append(1-self.error(ytrain, ypred_epoch, metric='acc'))


    def predict(self, xtest):
        '''
            Input parameters and return explained in parent class.

            It predicts the network output accordingly its hyperparameters and fitting parameters.
        '''
        n_test = len(xtest)
        input_layer = self.nn.layers[0]

        ytest = []

        for i in range(n_test):
            # init input layer values
            for (j, neuron) in enumerate(input_layer.neurons[1:]):
                neuron.initialise(xtest[i][j])

            # calculate output neuron response

            #self._forward_propagation()
            self.nn.trigger()
            for layer in self.nn.layers[1:]:
                self.nn.propagate()
                self.nn.trigger()

            outputs = self.nn.get_output()

            if len(outputs) == 1:
                if outputs[0] > 0:
                    ytest.append([1])
                else:
                    ytest.append([-1])
            else:
                ret = [-1]*len(outputs)
                max_idx = outputs.index(max(outputs))
                ret[max_idx] = 1
                ytest.append(ret)

        return ytest
