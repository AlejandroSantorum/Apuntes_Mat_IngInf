'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: Layer.py
    Date: Feb. 20, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of class Layer, whose goal
        is to group several neurons allocated at the same depth of a neural
        network.

'''

from enum import Enum
import random

class Layer:
    '''
        Implementation of class Layer, whose goal is to group several neurons
        allocated at the same depth of a neural network.
    '''

    class WeightMode(Enum):
        '''
            Enumeration to describe layers weigth mode.
        '''
        ZeroWeight = 0
        AdalineWeight = 1

    def __init__(self):
        '''
            Constructor of a new object 'Layer'.

            :return: None
        '''
        self.neurons = []

    def initialise():
        '''
            It initialises the values of the neurons of the current Layer.

            :return: None
        '''
        for neuron in self.neurons:
            neuron.initialise()

    def any_weight_update(self):
        '''
            Checks whether any weight of any output connection of the neuron has been update.

            :return: Boolean. True if any connection has been updated, False otherwise
        '''
        for neuron in self.neurons:
            if neuron.any_weight_update():
                return True
        return False

    def add(self, neuron):
        '''
            Add a neuron to the layer.

            :param neuron: neuron object to insert in this layer.
            :return: None.
        '''
        self.neurons.append(neuron)

    def connectLayer(self, layer, weight_mode):
        '''
            Connects a given layer to the current layer.

            :param layer: layer object to connect with this layer.
            :param weight_mode: weight mode to initialise weights.
            :return: None.
        '''
        for neuron in layer.neurons:
            self.connectNeuron(neuron, weight_mode)

    def connectNeuron(self, neuron, weight_mode):
        '''
            Connects a given neuron to the current layer.

            :param neuron: neuron object to connect with this layer.
            :param weight_mode: weight mode to initialise weights.
            :return: None.
        '''
        if weight_mode is Layer.WeightMode.ZeroWeight:
            for orig_neuron in self.neurons:
                orig_neuron.connect(neuron, 0)

        elif weight_mode is Layer.WeightMode.AdalineWeight:
            for orig_neuron in self.neurons:
                orig_neuron.connect(neuron, random.uniform(-0.5, 0.5))

    def trigger(self):
        '''
            Triggers the current layer neurons

            :return: None
        '''
        for neuron in self.neurons:
            neuron.trigger()

    def propagate(self):
        '''
            Propagates the values of the current layer neurons

            :return: None
        '''
        for neuron in self.neurons:
            neuron.propagate()

    def print_layer(self):
        for (i, neuron) in enumerate(self.neurons):
            print("\t\tNeuron", i)
            neuron.print_neuron()
