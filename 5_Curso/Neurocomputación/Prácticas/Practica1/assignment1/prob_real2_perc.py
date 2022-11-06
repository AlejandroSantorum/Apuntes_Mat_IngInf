'''
    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: prob_real2_perc.py
    Date: Mar. 12, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the script for real problem 2 perceptron exercise

'''


import sys
import numpy as np
from neuro_clfs.Perceptron import Perceptron
from read_data_utils import parse_read_mode, read1, read3
from tabulate import tabulate



TRAIN_PATH = "test_files/problema_real2.txt"
PREDICT_PATH = "test_files/problema_real2_no_etiquetados.txt"

DEFAULT_ALPHA = 0.5
DEFAULT_TH = 0.0
DEFAULT_NREPS = 10
DEFAULT_PERCENTAGE = 0.75
DEFAULT_EPOCH = 20

# prob_real2_perc.py [-hyper] [-a alpha] [-th tolerance] [-nreps num_reps] [-mep max_epoch]
def read_input_params():
    '''
        Reads input arguments accordingly to the specified exercise.

        :return:
            alpha: learning rate for perceptron algorithm.
            threshold: threshold for perceptron algorithm.
            num_reps: number of simulations to calculate mean MSE and/or accuracy.
            max_epoch: maximum number of epochs for perceptron algorithm.
    '''
    alpha = DEFAULT_ALPHA
    threshold = DEFAULT_TH
    num_reps = DEFAULT_NREPS
    max_epoch = DEFAULT_EPOCH

    # reading input params alpha and/or threshold (if specified)
    for (idx, parameter) in enumerate(sys.argv[1:]):
        if parameter == '-a':
            alpha = float(sys.argv[idx+2])
            if alpha <= 0 or alpha > 1:
                print("Error: alpha must be in (0, 1]")
                exit()
        if parameter == '-th':
            threshold = float(sys.argv[idx+2])
            if threshold < 0:
                print("Error: threshold must be non-negative")
                exit()
        if parameter == '-mep':
            max_epoch = int(sys.argv[idx+2])
            if max_epoch <= 0:
                print("Error: max_epoch must be at least one")
                exit()

    return alpha, threshold, num_reps, max_epoch



# default GridSearch hyperparameters
ALPHAS = [0.01, 0.05, 0.1, 0.5, 1]
THS = [0, 0.1, 0.3, 0.5, 1]

def val_hyperparams(alphas=ALPHAS, ths=THS):
    '''
        Executes GridSearch hyperparameter tuning accordingly to specified hyperparameters vectors.

        :param alphas: array of different alphas
        :param ths: array of different thresholds.
    '''
    headers = ["Thresholds \ Alphas"]
    for alpha in alphas:
        headers.append(str(alpha))

    L_RES = []
    L_RES_ACC = []
    for th in ths:
        L1 = [str(th)]
        L2 = [str(th)]
        for alpha in alphas:
            mse, std, acc, std2 = exec_real2(alpha, th, DEFAULT_NREPS, DEFAULT_EPOCH)
            L1.append(str(mse)+' +- '+str(std))
            L2.append(str(acc)+' +- '+str(std2))
            print("Alpha:", alpha, "Threshold:", th, "---> mse:", mse, ", acc:", acc)
        L_RES.append(L1)
        L_RES_ACC.append(L2)

    print(tabulate(L_RES, headers=headers, tablefmt="grid"))
    print(tabulate(L_RES_ACC, headers=headers, tablefmt="grid"))



def exec_real2(alpha, th, num_reps, max_epoch):
    '''
        Trains Perceptron algorithms and trains it several times in order to get
        mean MSE and mean accuracy.

        :param alpha: Learning parameter alpha
        :param th: Threshold. The algorithm activation function depends on this threshold
        :param num_reps: Number of simulations to calculate average values.
        :param max_epoch: Maximum number of epochs.
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

        perc_nn = Perceptron(n_inputs, n_outputs, alpha=alpha, threshold=th, max_epoch=max_epoch)

        perc_nn.train(xtrain, ytrain)
        ypred = perc_nn.predict(xtest)
        mse = perc_nn.error(ytest, ypred, metric='mse')
        acc = 1-perc_nn.error(ytest, ypred, metric='acc')
        mse_list.append(mse)
        acc_list.append(acc)

    mse_list = np.asarray(mse_list)
    acc_list = np.asarray(acc_list)
    return round(mse_list.mean(),5), round(mse_list.std(),3), round(acc_list.mean(),3), round(acc_list.std(),2)



SAVE_PATH = "predicciones/prediccion_perceptron.txt"

def predict_file(alpha, th, max_epoch):
    '''
        It generates the predictions of 'Problema Real 2' given a certain hyperparameters for Perceptron algorithm.
        The predicted outputs are stored in predicciones/prediccion_perceptron.txt

        :param alpha: Learning parameter alpha
        :param tol: Tolerance.
        :param max_epoch: Maximum number of epochs.
        :return: None
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
        error_perc_nn = Perceptron(n_inputs, n_outputs, alpha=alpha, threshold=th, max_epoch=max_epoch)
        error_perc_nn.train(error_xtrain, error_ytrain)
        error_ypred = error_perc_nn.predict(error_xtest)
        accs.append(1-error_perc_nn.error(error_ytest, error_ypred, metric='acc'))
    accs = np.asarray(accs)
    print("Estimated accuracy:", round(accs.mean(), 3), '+-', round(accs.std(), 2))

    # Predicting non-labeled examples
    perc_nn = Perceptron(n_inputs, n_outputs, alpha=alpha, threshold=th, max_epoch=max_epoch)
    perc_nn.train(xtrain, ytrain)
    ypred = perc_nn.predict(xtest)

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
        alpha, th, num_reps, max_epoch = read_input_params()
        print("Executing Perceptron algorithm with parameters:")
        print("\tAlpha =", alpha)
        print("\tThreshold =", th)
        print("\tNumber of repetitions =", num_reps)
        print("\tNumber of maximum epochs =", max_epoch)
        predict_file(alpha, th, max_epoch)
