'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: Neuron.py
    Date: Feb. 20, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of class Neuron, the logic
        units of a neural network.

'''


from enum import Enum
from neuro_clfs.Connection import Connection


class Neuron:
    '''
        Implementation of class Neuron, the logic units of a neural network.
    '''

    class Type(Enum):
        '''
            Enumeration to describe Neuron type.
        '''
        Direct = 0
        McCulloch = 1
        Bias = 2
        BipolarSigmoid = 3
        CustomSigmoid = 4
        Perceptron = 5

    def __init__(self, type, threshold=0.5, active_output=None, inactive_output=None):
        '''
            Constructor of a new object 'Neuron'.

            :return: None
        '''
        self.type = type
        self.threshold = threshold
        self.active_output = active_output
        self.inactive_output = inactive_output
        self.connections = []
        self.f_x = 0
        self.value = 0

    def initialise(self, value):
        '''
            It initialises the Neuron value.

            :param value: Float. Initialised value
            :return: None
        '''
        self.value = value

    def any_weight_update(self):
        '''
            Checks whether any weight of any output connection of the neuron has been update.

            :return: Boolean. True if any connection has been updated, False otherwise
        '''
        for connection in self.connections:
            if connection.any_weight_update():
                return True
        return False

    def connect(self, neuron, weight):
        '''
            Creates a connection from the Neuron object to the neuron indicated by the 'neuron' param with weight 'weight'.

            :param neuron: Neuron. Neuron to be connected to the Neuron object
            :param weight: Float. Weight of that connection
            :return: returns None
        '''
        self.connections.append(Connection(weight, neuron))

    def trigger(self):
        '''
            Trigger the output value of the neuron (f_x) calculated using the value and the type of the neuron.
            It also updates the value of the output connections from this neuron to reflect the change.

            :return: returns None
        '''
        if self.type is Neuron.Type.Direct:
            self.f_x = self.value
        elif self.type is Neuron.Type.Bias:
            self.f_x = 1.0
        elif self.type is Neuron.Type.BipolarSigmoid:
            self.f_x = 1 if self.value >= 0 else -1
        elif self.type is Neuron.Type.McCulloch:
            self.f_x = self.active_output if self.value >= self.threshold else self.inactive_output
        elif self.type is Neuron.Type.Perceptron:
            if self.value > self.threshold:
                self.f_x = self.active_output
            elif self.value < -self.threshold:
                self.f_x = self.inactive_output
            else:
                self.f_x = 0

        if self.type is not Neuron.Type.Bias: self.value = 0
        for connection in self.connections:
            connection.received_value = self.f_x

    def propagate(self):
        '''
            Triggers the propagation of all the output connections of the neuron

            :return: returns None
        '''
        for connection in self.connections:
            connection.propagate()

    def print_neuron(self):
        '''
            Prints the Neuron object, identified by its value, its F_x and its output connections.

            :return: returns None
        '''
        print("\t\t\tValue:", self.value)
        print("\t\t\tF_x:", self.f_x)
        for (i,conn) in enumerate(self.connections):
            print("\t\t\tConnection", i)
            conn.print_connection()
