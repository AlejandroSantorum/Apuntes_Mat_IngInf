'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: ex_multiperceptron.py
    Date: Apr. 10, 2021
    Project: Assignment 2 - Neurocomputation [EPS-UAM]

    Description: This file contains the script for multiperceptron exercises

'''

import sys
import matplotlib.pyplot as plt
from neuro_clfs.Multiperceptron import Multiperceptron
from read_data_utils import parse_read_mode, bipolar_encode, normalize
from tabulate import tabulate
import numpy as np
from scipy import stats


# If set to True, test set is divided into validation and test set (50%-50%).
VALIDATION = False


DEFAULT_ALPHA = 0.1
DEFAULT_NEPOCHS = 100
DEFAULT_NORM = False
DEFAULT_BATCH = None
DEFAULT_HIDDEN = []
# ex_multiperceptron.py read_mode file1 [file2/percentage] [-hyper] [-a alpha] [-nep n_epochs] [-h] [16 8 4] [-b batch_size] [-norm]
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
    n_epochs = DEFAULT_NEPOCHS
    norm = DEFAULT_NORM
    batch_size = DEFAULT_BATCH
    hidden = DEFAULT_HIDDEN

    # Reading train/test sets depending on given read mode
    read_mode, sets = parse_read_mode()

    # reading input params alpha and/or tolerance (if specified)
    for (idx, parameter) in enumerate(sys.argv[1:]):
        if parameter == '-a':
            alpha = float(sys.argv[idx+2])
            if alpha <= 0 or alpha > 1:
                print("Error: alpha must be in (0, 1]")
                exit()
        if parameter == '-nep':
            n_epochs = int(sys.argv[idx+2])
            if n_epochs <= 0:
                print("Error: n_epochs must be positive")
                exit()
        if parameter == '-norm':
            norm = True
        if parameter == '-b':
            batch_size = int(sys.argv[idx+2])
            if batch_size <= 0:
                print("Error: batch_size must be positive")
                exit()
        if parameter == '-h':
            hid_aux = []
            j = idx+2
            item = sys.argv[j]
            while '-' not in item:
                n_neur = int(item)
                if n_neur <= 0:
                    print("Error: number of neurons must be positive")
                    exit()
                hid_aux.append(n_neur)
                j += 1
                if j >= len(sys.argv[1:]):
                    break
                else:
                    item = sys.argv[j]
            hidden = hid_aux

    return read_mode, sets, alpha, n_epochs, norm, hidden, batch_size


# Ignoring numpy Overflow warning when using sigmoid function
np.seterr( over='ignore' )


def exec_train_predict(sets, alpha, n_epochs, hidden, batch_size, hyper=False, verbose=True):
    '''
        Executes main functionality of the script, i.e., trains Adaline with given parameters and given data,
        and prints it with the predictions. It also prints final overall MSE and saves a graph representing
        the evolution per epoch of the MSE.

        :param sets: 4-tuple containing train and tests sets read from specified datafile using given read mode.
        :param alpha: learning rate
        :param n_epochs: number of epochs to train the algorithm.
        :param hidden: Tuple indicating the neurons of the hidden layers.
            The length of this tuple is the number of hidden layers.
            The i-th element represents the number of neurons in the i-th hidden layer,
                NOT COUNTING THE BIAS NEURON.
        :param batch_size: Size of minibatches for stochastic training.
        :param hyper: (Optional) boolean, whether to perform RandomSearch on the hyperparameters
        :return: None
    '''
    xtrain, ytrain, xtest, ytest = sets

    ytrain = bipolar_encode(ytrain)
    ytest = bipolar_encode(ytest)

    n_inputs = len(xtrain[0])
    n_outputs = len(ytrain[0])

    multiperc_nn = Multiperceptron(n_inputs, n_outputs,
                                   hidden_layer_sizes=hidden, alpha=alpha,
                                   activation='bipolar', n_epochs=n_epochs,
                                   batch_size=batch_size, verbose=verbose)

    multiperc_nn.train(xtrain, ytrain)

    ypred = multiperc_nn.predict(xtest)

    mse_loss = multiperc_nn.error(ytest, ypred, metric='mse')
    acc = 1-multiperc_nn.error(ytest, ypred, metric='acc')

    if hyper:
        # returning hyperparameter search results
        return mse_loss, acc

    # Only printing feedback if we are not devoloping a hyperparameter seach
    multiperc_nn.nn.print_nn()

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
            res.append(str(round(xtest[i][j], 4)))
        for j in range(n_outputs):
            res.append(str(ytest[i][j]))
        for j in range(n_outputs):
            res.append(str(ypred[i][j]))
        results.append(res)

    print(tabulate(results, headers=headers, tablefmt="pretty"))

    fig, axes = plt.subplots(nrows=1, ncols=2)
    fig.set_figheight(5)
    fig.set_figwidth(13)
    fig.subplots_adjust(hspace=.5)
    axes[0].set_title('Evolution of MSE')
    axes[1].set_title('Evolution of Accuracy')
    axes[0].set_ylabel('MSE')
    axes[1].set_ylabel('Accuracy')
    axes[0].set_xlabel('Epochs')
    axes[1].set_xlabel('Epochs')
    axes[0].plot(range(len(multiperc_nn.epoch_errors)), multiperc_nn.epoch_errors)
    axes[1].plot(range(len(multiperc_nn.epoch_accs)), multiperc_nn.epoch_accs)
    plt.savefig('imgs/MSE+Acc_multiperc.png')

    if VALIDATION:
        print("===> Final generalization error using test set:")

    print("MSE Loss:", mse_loss)
    print("Accuracy:", acc, "("+str(acc*100)+"%)")



# RandomSearch intervals
ALPHA_RANGE = [0.05, 0.999]
N_HIDDEN = [1,2]
N_NEUR_LAYER = [2, 20]
N_HYPER = 7
N_REPS = 5

def val_hyperparams(sets, n_epochs, batch_size):
    '''
        Executes random hyperparameter search.

        :param sets: tuple containing train and test set. The test set might be
            considered a validation set instead.
        :param n_epochs: number of epochs for training.
        :param batch_size: batch size for training set.
        :return: tuple containing best hyperparameters, i.e.,
            the hyperparamters that the models performs better (best accuracy).
    '''

    best_acc = 0.0

    for i in range(N_HYPER):
        alpha = stats.loguniform.rvs(ALPHA_RANGE[0], ALPHA_RANGE[1])
        n_hidden = np.random.randint(low=N_HIDDEN[0], high=N_HIDDEN[1]+1) # + 1 because of the last is not included
        hidden_list = []
        for j in range(n_hidden):
            hidden_list.append(np.random.randint(low=N_NEUR_LAYER[0], high=N_NEUR_LAYER[1]+1))

        print("===========================================")
        print("Alpha:", alpha)
        print("Number of hidden layers:", n_hidden)
        print("Hidden layers:", hidden_list)
        MSE_LOSS = []
        ACC = []
        for k in range(N_REPS):
            mse_loss, acc = exec_train_predict(sets, alpha, n_epochs, hidden_list, batch_size, hyper=True, verbose=False)
            MSE_LOSS.append(mse_loss)
            ACC.append(acc)

        MSE_LOSS = np.asarray(MSE_LOSS)
        ACC = np.asarray(ACC)
        if ACC.mean() > best_acc:
            best_hyper = (alpha, hidden_list)

        print("=> Mean MSE Loss:", MSE_LOSS.mean(), "+-", MSE_LOSS.std())
        print("=> Mean Accuracy:", ACC.mean(), "+-", ACC.std())
        print("===========================================")

    if VALIDATION:
        print(">>> Best hyperparameters (obtained using train and validation sets) <<<")
        print("Alpha:", best_hyper[0])
        print("Hidden layers:", best_hyper[1])
        print(">>======================================================<<")


    return best_hyper




def _divide_test_set(xtest, ytest):
    '''
        Divides test set into validation set and test set. It takes the 50% of
        the examples and place them into the validation set, and the other
        50% is placed into a new test set.

        :param xtest: input test examples.
        :param ytest: output test examples.
        :return: tuple containing:
            input validation examples, output validation examples,
            input test examples, output test examples.
    '''
    half = len(xtest)//2
    return xtest[:half], ytest[:half], xtest[half:], ytest[half:]


if __name__ == '__main__':
    read_mode, sets, alpha, n_epochs, norm, hidden, batch_size = read_input_params()

    xtrain, ytrain, xtest, ytest = sets
    # Normalizing data if specified by user
    if norm:
        xtrain, xtest = normalize(xtrain, xtest)

    if VALIDATION:
        xval, yval, xtest, ytest = _divide_test_set(xtest, ytest)
        sets_val = (xtrain, ytrain, xval, yval)
        sets_train_pred = (xtrain, ytrain, xtest, ytest)
    else:
        sets_val = sets
        sets_train_pred = sets

    if '-hyper' in sys.argv:
        alpha, hidden = val_hyperparams(sets_val, n_epochs, batch_size)
        if VALIDATION:
            exec_train_predict(sets_train_pred, alpha, n_epochs, hidden, batch_size)
    else:
        exec_train_predict(sets_train_pred, alpha, n_epochs, hidden, batch_size)
