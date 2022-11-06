'''
    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: ex_perceptron.py
    Date: Feb. 28, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the script for perceptron exercise

'''


import sys
import matplotlib.pyplot as plt
from neuro_clfs.Perceptron import Perceptron
from read_data_utils import parse_read_mode
from tabulate import tabulate


DEFAULT_ALPHA = 1.0
DEFAULT_TH = 0.2
DEFAULT_EPOCH = 20
# ex_perceptron.py read_mode file1 [file2/percentage] [-a alpha] [-th threshold] [-mep max_epoch]
def read_input_params():
    '''
        Reads input arguments accordingly to the specified exercise.

        :return:
            read_mode: specified read mode to open data files. It can be 1, 2 or 3.
            sets: 4-tuple containing train and tests sets read from specified datafile using given read mode.
            alpha: learning rate for perceptron algorithm.
            threshold: threshold for perceptron algorithm.
            max_epoch: maximum number of epochs for perceptron algorithm.
    '''
    alpha = DEFAULT_ALPHA
    threshold = DEFAULT_TH
    max_epoch = DEFAULT_EPOCH

    # Reading train/test sets depending on given read mode
    read_mode, sets = parse_read_mode()

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

    return read_mode, sets, alpha, threshold, max_epoch




def main(sets, alpha, threshold, max_epoch):
    '''
        Executes main functionality of the script, i.e., trains Perceptron with given parameters and given data,
        and prints it with the predictions. It also prints final overall MSE and saves a graph representing
        the evolution per epoch of the MSE.

        :param sets: 4-tuple containing train and tests sets read from specified datafile using given read mode.
        :param alpha: learning rate
        :param threshold: threshold
        :param max_epoch: maximum number of epochs.
        :return: None
    '''
    xtrain, ytrain, xtest, ytest = sets

    n_inputs = len(xtrain[0])
    n_outputs = len(ytrain[0])

    perc_nn = Perceptron(n_inputs, n_outputs, threshold, alpha, False, max_epoch)

    perc_nn.train(xtrain, ytrain)
    ypred = perc_nn.predict(xtest)

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

    print("MSE Loss:", perc_nn.error(ytest, ypred, metric='mse'))

    weight_list = []
    input_layer = perc_nn.nn.layers[0]
    for neuron in input_layer.neurons:
        for conn in neuron.connections:
            weight_list.append(conn.weight)

    b = weight_list[0]
    weight_list = weight_list[1:]
    print("Decision boundary: ", end='')
    for (i, w) in enumerate(weight_list):
        print(str(round(w, 2)) + "·X"+str(i+1) + " + ", end='')
    print(str(round(b, 2)) + " = 0")

    plt.title('[Perceptron] Evolution of MSE per epoch')
    plt.ylabel('MSE')
    plt.xlabel('Epoch')
    plt.plot(range(len(perc_nn.epoch_errors)), perc_nn.epoch_errors)
    plt.savefig('imgs/ex_perc_mse.png')




if __name__ == '__main__':
    read_mode, sets, alpha, threshold, max_epoch = read_input_params()
    print("Executing Perceptron algorithm with parameters:")
    print("\tAlpha =", alpha)
    print("\tThreshold =", threshold)
    print("\tNumber of maximum epochs =", max_epoch)
    print("--------------------------------------")
    main(sets, alpha, threshold, max_epoch)
