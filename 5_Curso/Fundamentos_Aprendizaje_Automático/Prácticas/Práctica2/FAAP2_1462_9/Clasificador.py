################################################################################
#   Authors:
#       · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
#       · Jose Manuel Chacon Aguilera - josem.chacon@estudiante.uam.es
#   File: Clasificador.py
#   Date: Nov. 24, 2020
#   Project: Assignment 2 Fundamentals of Machine Learning
#   File Description: Implementation of class 'Clasificador'. The rest of
#       classifiers inherit that class and implements its own training
#       and validation methods.
#
################################################################################

from abc import ABCMeta,abstractmethod
import numpy as np
import random
import scipy
from scipy.stats import norm
import math
from collections import Counter

from sklearn.naive_bayes import MultinomialNB
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression, SGDClassifier



class Clasificador:

    # Clase abstracta
    __metaclass__ = ABCMeta

    # Metodos abstractos que se implementan en casa clasificador concreto
    @abstractmethod
    # TODO: esta funcion debe ser implementada en cada clasificador concreto
    # datosTrain: matriz numpy con los datos de entrenamiento
    # atributosDiscretos: array bool con la indicatriz de los atributos nominales
    # diccionario: array de diccionarios de la estructura Datos utilizados para la codificacion de variables discretas
    def entrenamiento(self,datosTrain,atributosDiscretos,diccionario):
        pass


    @abstractmethod
    # TODO: esta funcion debe ser implementada en cada clasificador concreto
    # devuelve un numpy array con las predicciones
    def clasifica(self,datosTest,atributosDiscretos,diccionario):
        pass


    # Obtiene el numero de aciertos y errores para calcular la tasa de fallo
    # datos is numpy array
    # pred is numpy array
    def error(self, datos, pred):
        # Aqui se compara la prediccion (pred) con las clases reales y se calcula el error
        hit_rate = sum(datos == pred)/len(pred)
        return 1-hit_rate # miss rate is the complement of hit rate


    # Realiza una clasificacion utilizando una estrategia de particionado determinada
    # TODO: implementar esta funcion
    def validacion(self, particionado, dataset, clasificador, seed=None):
        # Creamos las particiones siguiendo la estrategia llamando a particionado.creaParticiones
        # - Para validacion cruzada: en el bucle hasta nv entrenamos el clasificador con la particion de train i
        # y obtenemos el error en la particion de test i
        # - Para validacion simple (hold-out): entrenamos el clasificador con la particion de train
        # y obtenemos el error en la particion test. Otra opci�n es repetir la validaci�n simple un n�mero especificado de veces, obteniendo en cada una un error. Finalmente se calcular�a la media.
        random.seed(seed)
        np.random.shuffle(dataset.datos)

        particionado.creaParticiones(dataset.datos, seed)

        errores = []

        for particion in particionado.particiones:
            # Partitioning
            datostrain = dataset.datos[particion.indicesTrain, :]
            datostest = dataset.datos[particion.indicesTest, :]
            # Training
            clasificador.entrenamiento(datostrain, dataset.nominalAtributos, dataset.diccionario)
            # Predicting
            pred = clasificador.clasifica(datostest, dataset.nominalAtributos, dataset.diccionario)
            # Testing error
            ydatos = datostest[:,-1]
            err = clasificador.error(ydatos, pred)

            errores.append(err)
        # We return the array of errores. We can calculate later its mean and std
        return errores



##############################################################################
##############################################################################

class ClasificadorNaiveBayes(Clasificador):

    def __init__(self, laplace=True):
        self.prior_probs = []
        self.likelihoods = []
        self.laplace = laplace


    def _multinomialNB(self, xdata, ydata, feat_idx, diccionario):
        n_xi = len(diccionario[feat_idx])
        n_classes = len(diccionario[-1])
        theta_mtx = np.zeros((n_xi, n_classes))

        for value in diccionario[feat_idx]:
            feat_val_idx = diccionario[feat_idx][value]
            for class_name in diccionario[-1]:
                class_idx = diccionario[-1][class_name]
                # Calculating likelihood probability
                theta_mtx[feat_val_idx][class_idx] = sum((xdata[:,feat_idx] == feat_val_idx)&(ydata == class_idx))/sum(ydata == class_idx)

        # applying laplace correction
        if self.laplace and 0 in theta_mtx:
            theta_mtx += np.ones((n_xi, n_classes))

        return theta_mtx


    def _gaussianNB(self, xdata, ydata, feat_idx, diccionario):
        n_classes = len(diccionario[-1])

        theta_mtx = np.zeros((n_classes, 2)) # 2 columns: mean and variance for each class

        for class_name in diccionario[-1]:
            class_idx = diccionario[-1][class_name]
            # We calculate the mean coditioned to each possible class
            mean_sum = sum(elem for (idx, elem) in enumerate(xdata[:,feat_idx]) if ydata[idx]==class_idx)
            mean_class = mean_sum/sum(ydata == class_idx)
            # We calculate the variance conditioned to each possible class
            var_sum = sum((elem-mean_class)**2 for (idx, elem) in enumerate(xdata[:,feat_idx]) if ydata[idx]==class_idx)
            var_class = var_sum/sum(ydata == class_idx)

            theta_mtx[class_idx][0] = mean_class
            theta_mtx[class_idx][1] = var_class

        return theta_mtx


    def entrenamiento(self,datostrain,atributosDiscretos,diccionario):
        xdata = datostrain[:,:-1] # all rows, all columns but last one
        ydata = datostrain[:,-1]  # all rows, just last column

        m, n = xdata.shape     # number of examples, number of features
        n_classes = len(diccionario[-1])  # number of different classes

        # Calculating prior probabilities
        self.prior_probs = np.zeros(n_classes) # initializing array of prior probs with zeros
        for class_name in diccionario[-1]:
            class_idx = diccionario[-1][class_name]
            self.prior_probs[class_idx] = sum((class_idx == ydata))/m # P(y=i) = count(ydata==i)/len(ydata)

        likelihoods_list = []
        # Calculating likelihoods
        for feat_idx in range(n):
            if atributosDiscretos[feat_idx]:
                # calculating frequentist probs for discrete features
                theta_mtx = self._multinomialNB(xdata, ydata, feat_idx, diccionario)
            else:
                # calculating means and variances for continuous features
                theta_mtx = self._gaussianNB(xdata, ydata, feat_idx, diccionario)

            likelihoods_list.append(theta_mtx)

        self.likelihoods = np.asarray(likelihoods_list, dtype="object")


    # TODO: implementar
    def clasifica(self,datostest,atributosDiscretos,diccionario):
        xdata = datostest[:,:-1] # all rows, all columns but last one
        ydata = datostest[:,-1]  # all rows, just last column

        ndata, n_feat = xdata.shape     # number of examples, number of features
        n_classes = len(diccionario[-1])  # number of different classes

        pred = []
        for i in range(ndata):
            classes_probs = []
            for k in range(n_classes):
                class_p = self.prior_probs[k]
                for feat_idx in range(n_feat):
                    if atributosDiscretos[feat_idx]:
                        # calculating posterior probability
                        class_p *= self.likelihoods[feat_idx][int(xdata[i][feat_idx])][k]
                    else:
                        mean = self.likelihoods[feat_idx][k][0]
                        var = self.likelihoods[feat_idx][k][1]
                        # calculating posterior probability
                        class_p *= norm.pdf(xdata[i][feat_idx], loc=mean, scale=math.sqrt(var))
                classes_probs.append(class_p)
            pred.append(classes_probs.index(max(classes_probs)))

        return np.asarray(pred, dtype="object")



# scikit-learn NaiveBayes classifier encapsulated in our own general class
class ClasificadorNaiveBayesSK(Clasificador):

    def __init__(self, laplace=True, gaussian_feat=True):
        if gaussian_feat:
            self.clf = GaussianNB()
        else:
            self.clf = MultinomialNB(alpha=int(laplace))


    def entrenamiento(self,datostrain,atributosDiscretos,diccionario):
        xdata = datostrain[:,:-1] # all rows, all columns but last one
        ydata = datostrain[:,-1]  # all rows, just last column

        self.clf.fit(xdata,ydata)


    # TODO: implementar
    def clasifica(self,datostest,atributosDiscretos,diccionario):
        xdata = datostest[:,:-1] # all rows, all columns but last one

        return self.clf.predict(xdata)



##############################################################################
##############################################################################

class ClasificadorVecinosProximos(Clasificador):

    def __init__(self, K=5, dist='euclidean'):
        self.K = K
        self.dist = dist
        self.Sigma = None
        self.invSigma = None
        self.xtrain = None
        self.ytrain = None


    def entrenamiento(self,datosTrain,atributosDiscretos,diccionario):
        # We suppose data is already normalized
        self.xtrain = datosTrain[:,:-1] # all rows, all columns but last one
        self.ytrain = datosTrain[:,-1]  # all rows, just last column
        if self.dist == 'mahalanobis':
            # we use only train set to estimate covariance matrix
            self.Sigma = np.cov(self.xtrain, rowvar=False)
            self.invSigma = np.linalg.inv(self.Sigma)


    def clasifica(self,datosTest,atributosDiscretos,diccionario):
        xtest = datosTest[:,:-1] # all rows, all columns but last one
        ytest = datosTest[:,-1]  # all rows, just last column

        ntest, n_feat = xtest.shape  # number of examples, number of features
        ntrain = self.xtrain.shape[0]

        pred = []
        for idx_test in range(ntest):
            distances = []
            for idx_train in range(ntrain):
                if self.dist == 'euclidean':
                    # calculating euclidean distance between a test set example and a train set example
                    distances.append(math.sqrt(np.sum((xtest[idx_test,:]-self.xtrain[idx_train,:])**2)))
                elif self.dist == 'manhattan':
                    # calculating manhattan distance between a test set example and a train set example
                    distances.append(np.sum(np.absolute(xtest[idx_test,:]-self.xtrain[idx_train,:])))
                elif self.dist == 'mahalanobis':
                    # calculating mahalanobis distance between a test set example and a train set example
                    distances.append(scipy.spatial.distance.mahalanobis(xtest[idx_test,:],\
                                                                        self.xtrain[idx_train,:], self.invSigma))
                else:
                    raise Exception('The introduced distance is not available')
            # Sorting distances list
            sorted_dist = sorted(distances)
            pred_aux = []
            for d in sorted_dist[:self.K]: # Getting K-nearest neighbors
                idx = distances.index(d)
                pred_aux.append(self.ytrain[idx])
            # Getting most common class
            [(p_class, times_class)] = Counter(pred_aux).most_common(1)
            pred.append(p_class)

        return np.asarray(pred, dtype="object")



class ClasificadorVecinosProximosSK(Clasificador):

    def __init__(self, K=5, dist='euclidean'):
        self.K = K
        self.dist = dist
        self.clf = None # initialized in training method


    def entrenamiento(self,datosTrain,atributosDiscretos,diccionario):
        xdata = datosTrain[:,:-1] # all rows, all columns but last one
        ydata = datosTrain[:,-1]  # all rows, just last column
        
        if self.dist == 'mahalanobis':
            # mahalanobis distance needs an additional param, covariance matrix
            self.clf = KNeighborsClassifier(n_neighbors=self.K, metric=self.dist,\
                                            metric_params={'V': np.cov(xdata, rowvar=False)})
        else:
            self.clf = KNeighborsClassifier(n_neighbors=self.K, metric=self.dist)

        self.clf.fit(xdata,ydata)


    # TODO: implementar
    def clasifica(self,datosTest,atributosDiscretos,diccionario):
        xdata = datosTest[:,:-1] # all rows, all columns but last one

        return self.clf.predict(xdata)



##############################################################################
##############################################################################

def sigmoid(z):
    return 1/(1+math.exp(-z))



class ClasificadorRegresionLogistica(Clasificador):

    def __init__(self, learning_rate=0.1, nepochs=100):
        self.W = None
        self.lr = learning_rate
        self.nepochs = nepochs


    def entrenamiento(self, datosTrain, atributosDiscretos, diccionario):
        n_data = datosTrain.shape[0] # number of train examples
        intercept = np.ones((n_data, 1))
        # all rows, all columns but last one, adding intercept (column of ones)
        xdata = np.hstack((intercept, datosTrain[:,:-1]))
        ydata = datosTrain[:,-1] # all rows, just last column

        n_feat = xdata.shape[1] # number of features

        # Generating random initial weights in [-0.5, 0.5]
        # Remeber n_feat includes intercept column
        self.W = np.random.uniform(-0.5, 0.5, size=n_feat)

        for epoch in range(self.nepochs):
            for j in range(n_data):
                # evaluating sigmoid function in W.T * x_j
                sig = sigmoid(np.dot(xdata[j,:], self.W))
                # updating weights
                self.W = self.W - self.lr*(sig - ydata[j])*xdata[j,:]


    def clasifica(self, datosTest, atributosDiscretos, diccionario):
        n_data = datosTest.shape[0] # number of test examples
        intercept = np.ones((n_data, 1))
        # all rows, all columns but last one, adding intercept (column of ones)
        xdata = np.hstack((intercept, datosTest[:,:-1]))
        ydata = datosTest[:,-1] # all rows, just last column

        n_feat = xdata.shape[1] # number of features

        pred = []
        for j in range(n_data):
            # calculate probability of belonging to class 1
            sig = sigmoid(np.dot(self.W, xdata[j,:]))
            if sig >= 0.5: # predicted class 1
                pred.append(1)
            else: # predicted class 0
                pred.append(0)

        return np.asarray(pred, dtype="object")




class ClasificadorRegresionLogisticaSK(Clasificador):

    def __init__(self, learning_rate=0.1, nepochs=100, sgd=False):
        self.lr = learning_rate
        self.sgd = sgd
        if sgd:
            # loss = 'log' => equivalent to logistic regression
            self.clf = SGDClassifier(loss='log', penalty=None,
                                     learning_rate='constant', eta0=learning_rate,
                                     max_iter=nepochs, tol=1e-4)
        else:
            self.clf = LogisticRegression(solver='lbfgs', max_iter=nepochs)


    def entrenamiento(self,datosTrain,atributosDiscretos,diccionario):
        xdata = datosTrain[:,:-1] # all rows, all columns but last one
        ydata = datosTrain[:,-1]  # all rows, just last column

        self.clf.fit(xdata,ydata)


    def clasifica(self,datosTest,atributosDiscretos,diccionario):
        xdata = datosTest[:,:-1] # all rows, all columns but last one

        return self.clf.predict(xdata)
