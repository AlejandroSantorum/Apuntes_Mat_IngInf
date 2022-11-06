'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: ex_adaline.py
    Date: Feb. 28, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the script for adaline exercise

'''

import sys
import matplotlib.pyplot as plt
from neuro_clfs.Adaline import Adaline
from read_data_utils import parse_read_mode
from tabulate import tabulate


DEFAULT_ALPHA = 0.1
DEFAULT_TOL = 0.001
# ex_adaline.py read_mode file1 [file2/percentage] [-a alpha] [-tol tolerance]
def read_input_params():
    '''
        Reads input arguments accordingly to the specified exercise.

        :return:
            read_mode: specified read mode to open data files. It can be 1, 2 or 3.
            sets: 4-tuple containing train and tests sets read from specified datafile using given read mode.
            alpha: learning rate for adaline algorithm.
            tol: tolerance for adaline algorithm.
    '''
    alpha = DEFAULT_ALPHA
    tol = DEFAULT_TOL

    # Reading train/test sets depending on given read mode
    read_mode, sets = parse_read_mode()

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

    return read_mode, sets, alpha, tol


def main(sets, alpha, tol):
    '''
        Executes main functionality of the script, i.e., trains Adaline with given parameters and given data,
        and prints it with the predictions. It also prints final overall MSE and saves a graph representing
        the evolution per epoch of the MSE.

        :param sets: 4-tuple containing train and tests sets read from specified datafile using given read mode.
        :param alpha: learning rate
        :param tol: tolerance
        :return: None
    '''
    xtrain, ytrain, xtest, ytest = sets

    n_inputs = len(xtrain[0])
    n_outputs = len(ytrain[0])

    adal_nn = Adaline(n_inputs, n_outputs, alpha, tol)

    adal_nn.train(xtrain, ytrain)
    ypred = adal_nn.predict(xtest)

    headers = []
    for i in range(n_inputs):
        headers.append("x"+str(i+1))
    for i in range(n_outputs):
        headers.append("t"+str(i+1))
    for i in range(n_outputs):
        headers.append("y"+str(i+1))

    results = []
    for i in range(len(ytest)):
        res = []
        for j in range(n_inputs):
            res.append(str(xtest[i][j]))
        for j in range(n_outputs):
            res.append(str(ytest[i][j]))
        for j in range(n_outputs):
            res.append(str(ypred[i][j]))
        results.append(res)

    print(tabulate(results, headers=headers, tablefmt="pretty"))

    print("MSE Loss:", adal_nn.error(ytest, ypred, metric='mse'))

    weight_list = []
    input_layer = adal_nn.nn.layers[0]
    for neuron in input_layer.neurons:
        for conn in neuron.connections:
            weight_list.append(conn.weight)

    b = weight_list[0]
    weight_list = weight_list[1:]
    print("Decision boundary: ", end='')
    for (i, w) in enumerate(weight_list):
        print(str(round(w, 2)) + "·X"+str(i+1) + " + ", end='')
    print(str(round(b, 2)) + " = 0")

    plt.title('[Adaline] Evolution of MSE per epoch')
    plt.ylabel('MSE')
    plt.xlabel('Epoch')
    plt.plot(range(len(adal_nn.epoch_errors)), adal_nn.epoch_errors)
    plt.savefig('imgs/ex_adal_mse.png')




if __name__ == '__main__':
    read_mode, sets, alpha, tol = read_input_params()
    main(sets, alpha, tol)
