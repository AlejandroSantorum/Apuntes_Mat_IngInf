################################################################################
#   Authors:
#       · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
#       · Jose Manuel Chacon Aguilera - josem.chacon@estudiante.uam.es
#   File: Datos.py
#   Date: Dec. 20, 2020
#   Project: Assignment 3 Fundamentals of Machine Learning
#   File Description: Preliminary treatment of datasets using the class provided
#       in this file. It reads the data of the given file and stores all the
#       needed information for further use by machine learning algorithms.
#
################################################################################

# -*- coding: utf-8 -*-

# coding: utf-8
import pandas as pd
import numpy as np
from sklearn.preprocessing import OneHotEncoder


class Datos:

    # TODO: procesar el fichero para asignar correctamente las variables nominalAtributos, datos y diccionarios
    def __init__(self, nombreFichero, normalize=False, col_custom_dtypes=None):
        '''
            CONSTRUCTOR INPUT ARGS:
                nombreFichero: path to file containing the data
                normalize: boolean parameter. If set to True, data is normalized after reading. Default is False.
                col_custom_dtypes: dictionary containing data type for each column.
                                   For example, {'a': np.float64, 'b': np.int32, 'class': str}
                                   for more information: https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.read_csv.html
        '''
        # Attributes
        self.datos = None
        self.nominalAtributos = None
        self.diccionario = None
        self.means = None # attributes mean array. Used in normalization
        self.stds = None # attributes std deviation array. Used in normalization

        # reading csv
        if col_custom_dtypes:
            data_csv = pd.read_csv(nombreFichero, delimiter=',', dtype=col_custom_dtypes)
        else:
            data_csv = pd.read_csv(nombreFichero, delimiter=',')

        # building 'nominalAtributos' variable: list of boolean values with the same legth as the number of features
        # of the dataset (including the class feature). If the feature is a nominal value (string) the variable
        # 'nominalAtributos' will contain True, False if the feature is an integer or a real number.
        self.nominalAtributos = []
        example_row = data_csv.values[1]
 
        for item in example_row: # all atributes (including class)
            if isinstance(item, str): # nominal feature
                self.nominalAtributos.append(True)
            elif isinstance(item, int) or isinstance(item, float): # integer or real feature
                self.nominalAtributos.append(False)
            else: # feature neither nominal nor integer nor real
                raise ValueError('Tipo de dato diferente a nominal, entero o real')

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

        if normalize:
            self.normalizarDatos(self.datos, self.nominalAtributos)



    def calcularMediasDesv(self, datos, nominalAtributos):
        self.means = []
        self.stds = []

        for feat_idx, nominal_val in enumerate(nominalAtributos):
            if nominal_val == False: # continuous attribute
                self.means.append(np.mean(datos[:,feat_idx]))
                self.stds.append(np.std(datos[:,feat_idx]))
            else: # nominal attribute
                self.means.append(None)
                self.stds.append(None)

        return self.means, self.stds



    def normalizarDatos(self, datos, nominalAtributos):
        self.calcularMediasDesv(datos, nominalAtributos)

        for idx, nominal_val in enumerate(nominalAtributos):
            if nominal_val == False: # continuous attribute
                if self.stds[idx] != 0:
                    # centering and scaling data, using mean and standard deviation
                    datos[:,idx] = (datos[:,idx] - self.means[idx])/self.stds[idx]
                else:
                    datos[:,idx] -= self.means[idx]
                    
    def encodeDatos(datos):
        '''
            INPUT
                datos: numpy array
            
            OUTPUT
                numpy array
            
            DESCRIPTION:
                It computes One-Hot encoding of the X matrix, i.e., it computes One-Hot encoding of features.
        '''
        X = datos[:,:-1] # all rows, all columns but last one
        Y = datos[:,-1]  # all rows, just last column (class)

        # One hot encoding for discrete (nominal) features
        enc = OneHotEncoder(sparse=False, categories='auto')
        X_enc = np.array(enc.fit_transform(X), dtype=np.int32) 

        # Concatenating encoded data matrix and classes
        datos_aux = np.array(np.concatenate((X_enc, Y[:,None]), axis=1), dtype=np.int32)
        return datos_aux



    def extraeDatos(self, idx):
        # Se implementara en la practica 1
        pass
