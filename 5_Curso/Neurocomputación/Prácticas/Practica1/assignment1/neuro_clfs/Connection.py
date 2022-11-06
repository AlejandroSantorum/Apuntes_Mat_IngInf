'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: Connection.py
    Date: Feb. 20, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of class Connection, whose
        goal is to transfer information (weights, activations, etc.) through
        different types of neural networks.

'''


class Connection:
    '''
        Implementation of class Connection, whose goal is to transfer
        information (weights, activations, etc.) through different types
        of neural networks.
    '''

    def __init__(self, weight, neuron):
        '''
            Constructor of a new object 'Connection'.

            :param weight: The weight of the connection
            :param neuron: Neuron object. The built connection ends at this neuron.
            :return: None
        '''
        self.former_weight = None
        self.weight = weight
        self.neuron = neuron
        self.received_value = None

    def update_weight(self, term):
        '''
            It updates the current connection weight.

            :param term: Float. New weight is calculated as:
                new_weight = old_weight + term
            :return: None
        '''
        #print("[Antes] Former: ", self.former_weight, "Weight:" , self.weight)
        self.former_weight = self.weight
        self.weight = self.weight + term
        #print("[Despues] Former: ", self.former_weight, "Weight:" , self.weight)

    def any_weight_update(self):
        '''
            Checks whether the weight of the connection has been modified or not.

            :return: Boolean. False if there has been no update, True otherwise
        '''
        if self.former_weight == self.weight:
            return False
        return True

    def propagate(self):
        '''
            Propagates the received value of the previous neuron to the neuron that the connection is associated with.

            :return: None
        '''
        self.neuron.value += self.weight * self.received_value

    def print_connection(self):
        '''
            Prints the Connection object, identified by its former weight and its actual weight.

            :return: None
        '''
        print("\t\t\t\tFormer_weight:", self.former_weight)
        print("\t\t\t\tWeight:", self.weight)
