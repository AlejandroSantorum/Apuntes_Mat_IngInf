'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: Multiperceptron.py
    Date: Apr. 10, 2021
    Project: Assignment 2 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of class Multiperceptron, whose
        goal is to execute forward propagation and backward propagation in order to
        learn the best weights. It inherits NNClassifier class.

'''

from neuro_clfs.NNClassifier import NNClassifier
from neuro_clfs.NeuralNetwork import NeuralNetwork
from neuro_clfs.Layer import Layer
from neuro_clfs.Neuron import Neuron

import numpy as np
import time


def bipolar_sigmoid(x):
    '''
        Bipolar sigmoid activation function.

        :param x: real number to evaluate the function.
        :return: real number, the function at x.
    '''
    return 2/(1+np.exp(-x)) - 1

def bipolar_sigmoid_derivative(x):
    '''
        Derivative of bipolar sigmoid activation function.

        :param x: real number to evaluate the derivative.
        :return: real number, the derivative at x.
    '''
    return 0.5 * (1 + bipolar_sigmoid(x)) * (1 - bipolar_sigmoid(x))

def sigmoid(z):
    '''
        Binary sigmoid activation function.

        :param z: real number to evaluate the function.
        :return: real number, the function at z.
    '''
    return 1/(1 + np.exp(-z))

def sigmoid_derivative(z):
    '''
        Derivative of binary sigmoid activation function.

        :param x: real number to evaluate the derivative.
        :return: real number, the derivative at z.
    '''
    return sigmoid(z)*(1 - sigmoid(z))



class Multiperceptron(NNClassifier):
    '''
        Implementation of class Multiperceptron, whose goal is to execute multilayer perceptron
        learning algorithm. It inherits NNClassifier class.
    '''

    def __init__(self, n_inputs, n_outputs, hidden_layer_sizes=None, alpha=1.0,\
                 activation='bipolar', n_epochs=100, batch_size=None, verbose=False):
        '''
            Constructor of a new object 'Multiperceptron'.

            :param n_inputs: Number of inputs of the neural network
            :param n_outputs: Number of outputs of the neural network
            :param hidden_layer_sizes: Tuple indicating the neurons of the hidden layers.
                The length of this tuple is the number of hidden layers.
                The i-th element represents the number of neurons in the i-th hidden layer,
                    NOT COUNTING THE BIAS NEURON.
            :param alpha: (Optional) Learning parameter alpha. Default=1.0
            :param activation: (Optional) Activation function of the neurons.
                activation='bipolar': it uses bipolar sigmoid function.
                activation='sigmoid': it uses binary sigmoid function.
            :param n_epochs: (Optional) Number of epochs. Default=100
            :param batch_size: (Optional) Size of minibatches for stochastic training.
            :param verbose: (Optional) If set to True, feedback of each epoch is printed.
            :return: None
        '''
        self.hidden_layer_sizes = hidden_layer_sizes
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
        self.batch_size = batch_size
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

        prev_layer = input_layer
        # creating hidden layers and its neurons
        hidden_layers = []
        for i in range(len(self.hidden_layer_sizes)):
            layer = Layer()
            layer.add(Neuron(Neuron.Type.Bias))
            for j in range(self.hidden_layer_sizes[i]):
                layer.add(Neuron(self.neuron_types))
            # weight mode AdalineWeight := random initialization between a small interval
            prev_layer.connectLayer(layer, Layer.WeightMode.AdalineWeight)
            #prev_layer.connectLayer(layer, Layer.WeightMode.DebugWeight)
            hidden_layers.append(layer)
            prev_layer = layer

        # creating output layer and its neurons
        output_layer = Layer()
        for i in range(n_outputs):
            output_layer.add(Neuron(self.neuron_types))
        prev_layer.connectLayer(output_layer, Layer.WeightMode.AdalineWeight)
        #prev_layer.connectLayer(output_layer, Layer.WeightMode.DebugWeight)

        # adding layers to neural network
        self.nn.add(input_layer)
        for hid_layer in hidden_layers:
            self.nn.add(hid_layer)
        self.nn.add(output_layer)


    def _forward_propagation(self, id):
        '''
            Perfroms the forward propagation part of MLP weight update.

            :param id: Debugging id
            :return: None
        '''
        self.former_values = []
        self.former_activations = []
        # input layer trigger
        self.nn.trigger()
        temp_former_activations = []
        for neuron in self.nn.layers[0].neurons:
            temp_former_activations.append(neuron.f_x)
        self.former_activations.append(temp_former_activations)

        # rest of the network propagation
        for layer in self.nn.layers[1:]:
            self.nn.propagate()
            temp_former_values = []
            for neuron in layer.neurons:
                temp_former_values.append(neuron.value)

            self.nn.trigger()
            temp_former_activations = []
            for neuron in layer.neurons:
                temp_former_activations.append(neuron.f_x)

            self.former_values.append(temp_former_values)
            self.former_activations.append(temp_former_activations)



    def _backward_propagation(self, ytrain_array, id):
        '''
            Perfroms the backward propagation part of MLP weight update.

            :param ytrain_array: Targets of the training set
            :param id: Debugging id
            :return: None
        '''
        self.Deltas = []
        # getting last array of predictions (each output neuron activation)
        predictions = self.former_activations[-1]
        prev_layer = self.former_activations[-2]

        # getting last array of values (each output neuron value)
        pred_values = self.former_values[-1]
        deltas_prev_layer = []
        Delta_layer = []

        for k in range(len(self.nn.layers[-1].neurons)): # k lopping through neurons of output layer
            delta_k = (ytrain_array[k]-predictions[k]) * self.activation_func_deriv(pred_values[k])
            deltas_prev_layer.append(delta_k)
            for act in prev_layer:
                Delta_layer.append(self.alpha * delta_k * act)
        self.Deltas.append(Delta_layer)  # Delta_layer has size (n_outputs) x (size last hidden layer) <- including bias

        last_hidden_layer_flag = True

        for (i,layer) in enumerate(reversed(self.nn.layers[1:-1])):
            # Values of the current hidden layer (z_in)
            pred_values = self.former_values[::-1][i+1]
            # Activations of previous hidden layer (input_layer activations included) <- bias included
            prev_layer = self.former_activations[::-1][i+2]

            deltas_prev_layer_new = []
            Delta_layer = []
            for (j,neuron) in enumerate(layer.neurons[1:]):
                delta_in_j = 0
                if last_hidden_layer_flag:
                    for (k, connection) in enumerate(neuron.connections):
                        delta_in_j += connection.weight * deltas_prev_layer[k]
                else:
                    for (k, connection) in enumerate(neuron.connections[1:]):
                        delta_in_j += connection.weight * deltas_prev_layer[k]
                delta_j = delta_in_j * self.activation_func_deriv(pred_values[j+1])
                deltas_prev_layer_new.append(delta_j)
                for act in prev_layer:
                    Delta_layer.append(self.alpha * delta_j * act)
            last_hidden_layer_flag = False
            deltas_prev_layer = deltas_prev_layer_new
            self.Deltas.append(Delta_layer)


    def _update_nn_weights(self):
        '''
            Perfroms the weight modification part of MLP weight update.

            :return: None
        '''

        current_layer = self.nn.layers[-2]
        next_layer = self.nn.layers[-1]

        output_layer_flag = True

        for j,Delta in enumerate(self.Deltas):

            for k,neuron in enumerate(current_layer.neurons):
                l = len(current_layer.neurons) # counting bias
                if output_layer_flag:
                    for i in range(len(next_layer.neurons)):
                        aux = Delta[k + i*l]
                        neuron.connections[i].update_weight(aux)
                else:
                    for i in range(len(next_layer.neurons)-1):
                        aux = Delta[k + i*l]
                        neuron.connections[i+1].update_weight(aux)
            output_layer_flag = False

            if j == len(self.Deltas) - 1:
                break
            next_layer = current_layer
            current_layer = self.nn.layers[-3-j]


    def train(self, xtrain, ytrain):
        '''
            Input parameters and return explained in parent class.

            It trains the Multiperceptron object accordingly to perceptron algorithm.
        '''
        if self.batch_size is not None:
            n_train = self.batch_size
        else:
            n_train = len(xtrain)

        # getting input and output layers
        input_layer = self.nn.layers[0]
        output_layer = self.nn.layers[1]

        # training loop
        for k in range(self.n_epochs):
            # setting flag to False before every epoch
            update_flag = False
            if self.verbose:
                print("Epoch", k)

            # an epoch trains over all examples or batch
            if self.batch_size is not None:
                joint = list(zip(xtrain, ytrain))
                np.random.shuffle(joint)
                xtrain, ytrain = zip(*joint)

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

            ypred_epoch = self.predict(xtrain[:n_train])
            self.epoch_errors.append(self.error(ytrain[:n_train], ypred_epoch, metric='mse'))
            self.epoch_accs.append(1-self.error(ytrain[:n_train], ypred_epoch, metric='acc'))


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
