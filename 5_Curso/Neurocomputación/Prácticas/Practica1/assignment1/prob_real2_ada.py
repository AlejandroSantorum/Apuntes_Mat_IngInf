'''
    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: prob_real2_ada.py
    Date: Mar. 12, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the script for real problem 2 adaline exercise

'''


import sys
import numpy as np
from neuro_clfs.Adaline import Adaline
import matplotlib.pyplot as plt
from read_data_utils import parse_read_mode, read1, read3
from tabulate import tabulate



TRAIN_PATH = "test_files/problema_real2.txt"
PREDICT_PATH = "test_files/problema_real2_no_etiquetados.txt"

DEFAULT_ALPHA = 0.01
DEFAULT_TOL = 0.001
DEFAULT_NREPS = 10
DEFAULT_PERCENTAGE = 0.75

# prob_real2_ada.py [-hyper] [-a alpha] [-tol tolerance] [-nreps num_reps]
def read_input_params():
    '''
        Reads input arguments accordingly to the specified exercise.

        :return:
            alpha: learning rate for perceptron algorithm.
            tol: tolerance for adaline algorithm.
            num_reps: number of simulations to calculate mean MSE and/or accuracy.
    '''
    alpha = DEFAULT_ALPHA
    tol = DEFAULT_TOL
    num_reps = DEFAULT_NREPS

    # reading input params alpha and/or tolerance (if specified)
    for (idx, parameter) in enumerate(sys.argv[1:]):
        if parameter == '-a':
            alpha = float(sys.argv[idx+2])
            if alpha <= 0 or alpha > 1:
                print("Error: alpha must be in (0, 1]")
                exit()
        if parameter == '-tol':
            tol = float(sys.argv[idx+2])
            if tol <= 0:
                print("Error: tolerance must be positive")
                exit()

    return alpha, tol, num_reps



# default GridSearch hyperparameters
ALPHAS = [0.005, 0.01, 0.05, 0.1]
TOLS = [0.001, 0.005, 0.01, 0.05]

def val_hyperparams(alphas=ALPHAS, tols=TOLS):
    '''
        Executes GridSearch hyperparameter tuning accordingly to specified hyperparameters vectors.

        :param alphas: array of different alphas
        :param tols: array of different tolerances.
    '''
    headers = ["Tols \ Alphas"]
    for alpha in ALPHAS:
        headers.append(str(alpha))

    L_RES = []
    for tol in TOLS:
        L = [str(tol)]
        for alpha in ALPHAS:
            mse, std, _, _ = exec_real2(alpha, tol, DEFAULT_NREPS)
            L.append(str(mse)+' +- '+str(std))
            print("Alpha:", alpha, "Tolerance:", tol, "---> mse:", mse)
        L_RES.append(L)

    print(tabulate(L_RES, headers=headers, tablefmt="grid"))



def exec_real2(alpha, tol, num_reps):
    '''
        Trains Adaline algorithms and trains it several times in order to get
        mean MSE and mean accuracy.

        :param alpha: Learning parameter alpha
        :param tol: Tolerance.
        :param num_reps: Number of simulations to calculate average values.
        :return: mean mse, std mse, mean accuracy, std accuracy
    '''
    mse_list = []
    acc_list = []
    for i in range(num_reps):
        # reading training and test sets
        sets = read1(TRAIN_PATH, DEFAULT_PERCENTAGE)
        xtrain, ytrain, xtest, ytest = sets

        n_inputs = len(xtrain[0])
        n_outputs = len(ytrain[0])

        ada_nn = Adaline(n_inputs, n_outputs, alpha=alpha, tol=tol)

        ada_nn.train(xtrain, ytrain)
        ypred = ada_nn.predict(xtest)
        mse = ada_nn.error(ytest, ypred, metric='mse')
        acc = 1-ada_nn.error(ytest, ypred, metric='acc')
        mse_list.append(mse)
        acc_list.append(acc)

    mse_list = np.asarray(mse_list)
    acc_list = np.asarray(acc_list)
    return round(mse_list.mean(),5), round(mse_list.std(),3), round(acc_list.mean(),3), round(acc_list.std(),2)



SAVE_PATH = "predicciones/prediccion_adaline.txt"

def predict_file(alpha, tol):
    '''
        It generates the predictions of 'Problema Real 2' given a certain hyperparameters for Adaline algorithm.
        The predicted outputs are stored in predicciones/prediccion_adaline.txt
        
        :param alpha: Learning parameter alpha
        :param tol: Tolerance.
    '''
    sets = read3(TRAIN_PATH, PREDICT_PATH)
    xtrain, ytrain, xtest, ytest = sets # ytest is useless is read mode 3
    n_inputs = len(xtrain[0])
    n_outputs = len(ytrain[0])

    # Estimating generalization error, dividing train file in train+test sets
    accs = []
    for i in range(DEFAULT_NREPS):
        error_sets = read1(TRAIN_PATH, DEFAULT_PERCENTAGE)
        error_xtrain, error_ytrain, error_xtest, error_ytest = error_sets
        error_ada_nn = Adaline(n_inputs, n_outputs, alpha=alpha, tol=tol)
        error_ada_nn.train(error_xtrain, error_ytrain)
        error_ypred = error_ada_nn.predict(error_xtest)
        accs.append(1-error_ada_nn.error(error_ytest, error_ypred, metric='acc'))
    accs = np.asarray(accs)
    print("Estimated accuracy:", round(accs.mean(), 3), '+-', round(accs.std(), 2))

    # Predicting non-labeled examples
    ada_nn = Adaline(n_inputs, n_outputs, alpha=alpha, tol=tol)
    ada_nn.train(xtrain, ytrain)
    ypred = ada_nn.predict(xtest)

    with open(SAVE_PATH, 'w') as f:
        for predict in ypred:
            f.write(str(predict[0])+' '+str(predict[1])+'\n')

    print('The predictions have been stored in:', SAVE_PATH)



if __name__ == '__main__':
    # hyperparameter validation
    if '-hyper' in sys.argv:
        val_hyperparams()
    # executing with specified parameters
    else:
        alpha, tol, num_reps = read_input_params()
        print("Executing Adaline algorithm with parameters:")
        print("\tAlpha =", alpha)
        print("\tTolerance =", tol)
        print("\tNumber of repetitions =", num_reps)
        predict_file(alpha, tol)
