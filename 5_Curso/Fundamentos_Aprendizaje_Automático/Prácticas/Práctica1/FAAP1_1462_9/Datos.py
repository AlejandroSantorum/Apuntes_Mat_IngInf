################################################################################
#   Authors:
#       · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
#       · Jose Manuel Chacon Aguilera - josem.chacon@estudiante.uam.es
#   File: Datos.py
#   Date: Sept. 21, 2020
#   Project: Assignment 0 Fundamentals of Machine Learning
#   File Description: Preliminary treatment of datasets using the class provided
#       in this file. It reads the data of the given file and stores all the
#       needed information for further use by machine learning algorithms.
#
################################################################################

# -*- coding: utf-8 -*-

# coding: utf-8
import pandas as pd
import numpy as np


class Datos:

    # TODO: procesar el fichero para asignar correctamente las variables nominalAtributos, datos y diccionarios
    def __init__(self, nombreFichero):
        # Init attributes
        self.datos = None
        self.nominalAtributos = None
        self.diccionario = None

        # reading csv
        data_csv = pd.read_csv(nombreFichero, delimiter=',')

        # building 'nominalAtributos' variable: list of boolean values with the same legth as the number of features
        # of the dataset (including the class feature). If the feature is a nominal value (string) the variable
        # 'nominalAtributos' will contain True, False if the feature is an integer or a real number.
        self.nominalAtributos = []
        example_row = data_csv.values[1]
        for item in example_row[:-1]: # all atributes, but not the class
            if isinstance(item, str): # nominal feature
                self.nominalAtributos.append(True)
            elif isinstance(item, int) or isinstance(item, float): # integer or real feature
                self.nominalAtributos.append(False)
            else: # feature neither nominal nor integer nor real
                raise ValueError('Tipo de dato diferente a nominal, entero o real')
        # the class is always nominal
        self.nominalAtributos.append(True)

        # building 'diccionario' variable: list of dictionaries. For each nominal feature a dictionary is built:
        # each key will correspond with an unique nominal and its value is the numerical representation of that key/nominal.
        self.diccionario = []
        nexamples, ncols = data_csv.values.shape
        for col in range(ncols):
            # If the feature is integer type or real type, its dictionary is empty (it doesn't need translation)
            if self.nominalAtributos[col] == False:
                self.diccionario.append({})
            # If the feature is nominal, then we build its translation dictionary to numerical values
            else:
                col_set = list(set(data_csv.values[:,col]))   # getting unique nominals
                col_set.sort()                      # sorting nominals alphabetically
                feature_dict = {}
                for i in range(len(col_set)):
                    feature_dict[col_set[i]] = i  # {key: nominal, value: i} (counter)
                self.diccionario.append(feature_dict)  # appending new dictionary for that feature
        
        # storing data values in 'datos' class variable
        self.datos = np.zeros((nexamples, ncols))
        for col in range(ncols):
            # taking column data
            vals = data_csv.values[:,col]
            # if it is nominal, we convert its values
            if self.nominalAtributos[col]:
                # converting data into numerical values
                numerical_vals = [self.diccionario[col][val] for val in vals]
            else:
                numerical_vals = vals
            # updating numerical data matrix
            self.datos[:,col] = numerical_vals
            

    def extraeDatos(self, idx):
        # Se implementara en la practica 1
        pass
