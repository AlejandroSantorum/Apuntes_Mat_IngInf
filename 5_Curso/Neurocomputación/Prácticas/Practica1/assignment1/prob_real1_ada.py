'''
    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: prob_real1_ada.py
    Date: Mar. 12, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the script for real problem 1 adaline exercise

'''


import sys
import numpy as np
from neuro_clfs.Adaline import Adaline
import matplotlib.pyplot as plt
from read_data_utils import parse_read_mode, read1
from tabulate import tabulate



FILE_PATH = "test_files/problema_real1.txt"

DEFAULT_ALPHA = 0.01
DEFAULT_TOL = 0.01
DEFAULT_NREPS = 10
DEFAULT_PERCENTAGE = 0.75

# prob_real1_ada.py [-hyper] [-a alpha] [-tol tolerance] [-nreps num_reps]
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
        if parameter == '-nreps':
            num_reps = int(sys.argv[idx+2])
            if num_reps <= 0:
                print("Error: num_reps must be at least one")
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
    L_RES = []

    # If alpha is fixed
    if len(alphas) == 1:
        mse_list = []
        L = [str(alphas[0])]
        headers = ['Alpha \ Tols']
        for tol in tols:
            headers.append(str(tol))
        for tol in tols:
            mse, std, _, _ = exec_real1(alphas[0], tol, DEFAULT_NREPS)
            mse_list.append(mse)
            L.append(str(mse)+' +- '+str(std))
            print("Alpha:", alphas[0], "Tol:", tol, "---> mse:", mse)
        L_RES.append(L)
        # Plotting
        plt.title('Evolution of MSE varying tolerance (alpha='+str(alphas[0])+')')
        plt.ylabel('MSE')
        plt.xlabel('Tolerance')
        plt.plot(tols, mse_list)
        plt.savefig('imgs/MSE_adal_varTol.png')

    # If tolerance is fixed
    elif len(tols) == 1:
        mse_list = []
        L = [str(tols[0])]
        headers = ["Tols \ Alphas"]
        for a in alphas:
            headers.append(str(a))
        for a in alphas:
            mse, std, _, _ = exec_real1(a, tols[0], DEFAULT_NREPS)
            mse_list.append(mse)
            L.append(str(mse)+' +- '+str(std))
            print("Alpha:", a, "Tol:", tols[0], "---> mse:", mse)
        L_RES.append(L)
        # Plotting
        plt.title('Evolution of MSE varying alpha (tol='+str(tols[0])+')')
        plt.ylabel('MSE')
        plt.xlabel('Alpha')
        plt.plot(alphas, mse_list)
        plt.savefig('imgs/MSE_adal_varAlpha.png')

    # None is fixed
    else:
        headers = ["Tols \ Alphas"]
        for alpha in alphas:
            headers.append(str(alpha))
        for tol in tols:
            L = [str(tol)]
            for alpha in alphas:
                mse, std, _, _ = exec_real1(alpha, tol, DEFAULT_NREPS)
                L.append(str(mse)+' +- '+str(std))
                print("Alpha:", alpha, "Tolerance:", tol, "---> mse:", mse)
            L_RES.append(L)

    print(tabulate(L_RES, headers=headers, tablefmt="grid"))



def exec_real1(alpha, tol, num_reps):
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
        sets = read1(FILE_PATH, DEFAULT_PERCENTAGE)
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



if __name__ == '__main__':
    # hyperparameter validation
    if '-hyper' in sys.argv and '-a' not in sys.argv and '-tol' not in sys.argv:
        val_hyperparams()
    # hyperparameter validation fixing alpha
    elif '-hyper' in sys.argv and '-a' in sys.argv and '-tol' not in sys.argv:
        idx = sys.argv.index('-a')
        alpha = float(sys.argv[idx+1])
        val_hyperparams(alphas=[alpha])
    # hyperparameter validation fixing threshold
    elif '-hyper' in sys.argv and '-a' not in sys.argv and '-tol' in sys.argv:
        idx = sys.argv.index('-tol')
        tol = float(sys.argv[idx+1])
        val_hyperparams(tols=[tol])
    # executing with specified parameters
    else:
        alpha, tol, num_reps = read_input_params()
        print("Executing Adaline algorithm with parameters:")
        print("\tAlpha =", alpha)
        print("\tTolerance =", tol)
        print("\tNumber of repetitions =", num_reps)
        mse, std, acc, std2 = exec_real1(alpha, tol, num_reps)
        print("===> Mean Squared Error:", mse, "+-", std)
        print("===> Mean Accuracy:", acc, "+-", std2)
