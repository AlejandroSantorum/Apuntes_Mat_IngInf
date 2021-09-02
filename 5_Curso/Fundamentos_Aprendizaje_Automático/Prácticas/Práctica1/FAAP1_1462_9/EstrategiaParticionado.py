################################################################################
#   Authors:
#       · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
#       · Jose Manuel Chacon Aguilera - josem.chacon@estudiante.uam.es
#   File: EstrategiaParticionado.py
#   Date: Oct. 24, 2020
#   Project: Assignment 1 Fundamentals of Machine Learning
#   File Description: Implementation of class 'Particion' and
#       'EstrategiaParticionado'. The rest of partition strategies
#       inherit that class and implements its own partition methods.
#
################################################################################

from abc import ABCMeta,abstractmethod
import numpy as np
import random


class Particion():

    # Esta clase mantiene la lista de �ndices de Train y Test para cada partici�n del conjunto de particiones
    def __init__(self):
        self.indicesTrain=[]
        self.indicesTest=[]

#####################################################################################################

class EstrategiaParticionado(object):
    # Clase abstracta
    __metaclass__ = ABCMeta

    # Atributos: deben rellenarse adecuadamente para cada estrategia concreta. Se pasan en el constructor

    @abstractmethod
    # TODO: esta funcion deben ser implementadas en cada estrategia concreta
    def creaParticiones(self,datos,seed=None):
        pass


#####################################################################################################

class ValidacionSimple(EstrategiaParticionado):
    def __init__(self, percentage, nreps=1):
        self.particiones = [Particion() for i in range(nreps)]
        self.nreps = nreps
        self.percentage = percentage
    # Crea particiones segun el metodo tradicional de division de los datos segun el porcentaje deseado y el n�mero de ejecuciones deseado
    # Devuelve una lista de particiones (clase Particion)
    # TODO: implementar
    def creaParticiones(self,datos,seed=None):
        random.seed(seed)
        [ndata, _] = datos.shape
        ntrain = int(ndata*self.percentage)
        for i in range(self.nreps):
            self.particiones[i].indicesTrain = random.sample(range(ndata), ntrain)
            all = np.arange(ndata)
            self.particiones[i].indicesTest = [idx for idx in all if idx not in self.particiones[i].indicesTrain]



#####################################################################################################
class ValidacionCruzada(EstrategiaParticionado):

    def __init__(self, k_fold):
        self.particiones = [Particion() for i in range(k_fold)]
        self.k_fold = k_fold

    # Crea particiones segun el metodo de validacion cruzada.
    # El conjunto de entrenamiento se crea con las nfolds-1 particiones y el de test con la particion restante
    # Esta funcion devuelve una lista de particiones (clase Particion)
    # TODO: implementar
    def creaParticiones(self,datos,seed=None):
        random.seed(seed)
        [ndata, _] = datos.shape
        # Size of each fold
        size = int(ndata/self.k_fold)
        # Filling the partition array
        for i in range(self.k_fold):
            self.particiones[i].indicesTest = np.arange(i*size, (i+1)*size)
            self.particiones[i].indicesTrain = np.concatenate((np.arange(0, i*size), np.arange((i+1)*size, ndata)), axis=None)
