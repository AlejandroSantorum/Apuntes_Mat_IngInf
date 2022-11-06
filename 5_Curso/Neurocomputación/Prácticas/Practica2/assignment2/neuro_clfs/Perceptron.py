'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: Perceptron.py
    Date: Mar. 10, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of class Perceptron, whose
        goal is to execute perceptron learning algorithm. It inherits NNClassifier class.

'''

from neuro_clfs.NNClassifier import NNClassifier
from neuro_clfs.NeuralNetwork import NeuralNetwork
from neuro_clfs.Layer import Layer
from neuro_clfs.Neuron import Neuron

class Perceptron(NNClassifier):
    '''
        Implementation of class Perceptron, whose goal is to execute perceptron
        learning algorithm. It inherits NNClassifier class.
    '''

    def __init__(self, n_inputs, n_outputs, threshold=0.1, alpha=1.0, verbose=False, max_epoch=20):
        '''
            Constructor of a new object 'Perceptron'.

            :param n_inputs: Number of inputs of the neural network
            :param n_outputs: Number of outputs of the neural network
            :param alpha: (Optional) Learning parameter alpha. Default=0.1
            :param threshold: (Optional) Threshold. The algorithm activation function depends on this threshold. Default=0.1
            :param verbose: (Optional) If set to True, feedback of each epoch is printed.
            :param max_epoch: (Optional) Maximum number of epochs. Default=20
            :return: None
        '''
        self.threshold = threshold
        self.alpha = alpha
        self.verbose = verbose
        self.max_epoch = max_epoch
        self.epoch_errors = []

        # building neural network with given data
        self.nn = NeuralNetwork()
        input_layer = Layer()
        output_layer = Layer()

        # creating neurons of input layer
        input_layer.add(Neuron(Neuron.Type.Bias))
        for i in range(n_inputs):
            input_layer.add(Neuron(Neuron.Type.Direct))

        for i in range(n_outputs):
            output_layer.add(Neuron(Neuron.Type.Perceptron, threshold=threshold, active_output=1, inactive_output=-1))
        # WeightMode PerceptronWeight = WeightMode ZeroWeight
        input_layer.connectLayer(output_layer, Layer.WeightMode.ZeroWeight)

        self.nn.add(input_layer)
        self.nn.add(output_layer)


    def train(self, xtrain, ytrain):
        '''
            Input parameters and return explained in parent class.

            It trains the Perceptron object accordingly to perceptron algorithm.
        '''
        n_train = len(xtrain)

        # getting input and output layers
        input_layer = self.nn.layers[0]
        output_layer = self.nn.layers[1]

        # training loop: update_flag is True if any nn weight is updated
        update_flag = True
        n_epoch = 0
        while update_flag and n_epoch < self.max_epoch:
            # setting flag to False before every epoch
            update_flag = False
            n_epoch += 1
            if self.verbose:
                print("Epoch", n_epoch)

            # an epoch trains over all examples
            for i in range(n_train):
                # nit input layer values
                for (j, neuron) in enumerate(input_layer.neurons[1:]):
                    neuron.initialise(xtrain[i][j])

                # calculate output neuron response
                self.nn.trigger()
                self.nn.propagate()
                self.nn.trigger()
                # update weights (if needed)
                for (j, neuron_out) in enumerate(output_layer.neurons):
                    if neuron_out.f_x != ytrain[i][j]:
                        # updating w_i
                        for (k, neuron_in) in enumerate(input_layer.neurons[1:]):
                            neuron_in.connections[j].update_weight(self.alpha*ytrain[i][j]*xtrain[i][k])
                        # updating b
                        input_layer.neurons[0].connections[j].update_weight(self.alpha*ytrain[i][j])

                    else:
                        for neuron_in in input_layer.neurons:
                            neuron_in.connections[j].update_weight(0) # term = 0

                if self.nn.any_weight_update():
                    update_flag = True
            self.epoch_errors.append(self.error(ytrain, self.predict(xtrain), metric='mse'))


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
            self.nn.trigger()
            self.nn.propagate()
            self.nn.trigger()

            ytest.append(self.nn.get_output())

        return ytest
