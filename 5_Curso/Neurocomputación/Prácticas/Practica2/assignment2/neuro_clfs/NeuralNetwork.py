'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: NeuralNetwork.py
    Date: Feb. 20, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of class NeuralNetwork, that
        is a set of neurons and connections in order to approximate a general
        function, determined by its weights and input parameters.

'''


class NeuralNetwork:
    '''
        Implementation of class NeuralNetwork, that is a set of neurons and
        connections in order to approximate a general function, determined
        by its weights and input parameters.
    '''

    def __init__(self):
        '''
            Constructor of a new object 'NeuralNetwork'.

            :return: None
        '''
        self.layers = []

    def initialise():
        '''
            It initialises the NeuralNetowrks values.

            :return: None
        '''
        for layer in self.layers:
            layer.initialise()

    def any_weight_update(self):
        '''
            Checks whether any weight of any output connection of the neuron has been update.

            :return: Boolean. True if any connection has been updated, False otherwise
        '''
        for layer in self.layers:
            if layer.any_weight_update():
                return True
        return False

    def add(self, layer):
        '''
            Adds a layer to the network

            :param layer: layer object to be added
            :return: None
        '''
        self.layers.append(layer)

    def trigger(self):
        '''
            Triggers the net's layers

            :return: None
        '''
        for layer in self.layers:
            layer.trigger()

    def propagate(self):
        '''
            Propagates the values of all the net's neurons

            :return: None
        '''
        for layer in self.layers:
            layer.propagate()

    def get_output(self):
        '''
            Return the output values of every neuron in the neural network.

            :return: a list of output values
        '''
        output_vals = []
        for neuron in self.layers[-1].neurons:
            output_vals.append(neuron.f_x)
        return output_vals

    def print_nn(self):
        '''
            Prints the neural network by printing every layer.

            :return: returns None
        '''
        for (i, layer) in enumerate(self.layers):
            print("\tLayer", i)
            layer.print_layer()
