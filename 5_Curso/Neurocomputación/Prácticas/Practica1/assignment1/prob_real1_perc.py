'''
    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: prob_real1_perc.py
    Date: Mar. 12, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the script for real problem 1 perceptron exercise

'''


import sys
import numpy as np
import matplotlib.pyplot as plt
from neuro_clfs.Perceptron import Perceptron
from read_data_utils import parse_read_mode, read1
from tabulate import tabulate



FILE_PATH = "test_files/problema_real1.txt"

DEFAULT_ALPHA = 0.5
DEFAULT_TH = 0.0
DEFAULT_NREPS = 10
DEFAULT_PERCENTAGE = 0.75
DEFAULT_EPOCH = 20

# prob_real1_perc.py [-hyper] [-a alpha] [-th threshold] [-nreps num_reps] [-mep max_epoch]
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
        if parameter == '-nreps':
            num_reps = int(sys.argv[idx+2])
            if num_reps <= 0:
                print("Error: num_reps must be at least one")
                exit()
        if parameter == '-mep':
            max_epoch = int(sys.argv[idx+2])
            if max_epoch <= 0:
                print("Error: max_epoch must be at least one")
                exit()

    return alpha, threshold, num_reps, max_epoch



# default GridSearch hyperparameters
ALPHAS = [0.01, 0.05, 0.1, 0.5, 1]
THS = [0, 0.25, 0.5, 1]

def val_hyperparams(alphas=ALPHAS, ths=THS):
    '''
        Executes GridSearch hyperparameter tuning accordingly to specified hyperparameters vectors.

        :param alphas: array of different alphas
        :param ths: array of different thresholds.
    '''
    L_RES = []
    L_RES_ACC = []

    # If alpha is fixed
    if len(alphas) == 1:
        mse_list = []
        acc_list = []
        L1 = [str(alphas[0])]
        L2 = [str(alphas[0])]
        headers = ['Alpha \ Thresholds']
        for th in ths:
            headers.append(str(th))
        for th in ths:
            mse, std, acc, std2 = exec_real1(alphas[0], th, DEFAULT_NREPS, DEFAULT_EPOCH)
            mse_list.append(mse)
            acc_list.append(acc)
            L1.append(str(mse)+' +- '+str(std))
            L2.append(str(acc)+' +- '+str(std2))
            print("Alpha:", alphas[0], "Threshold:", th, "---> mse:", mse, ", acc:", acc)
        L_RES.append(L1)
        L_RES_ACC.append(L2)
        # Plotting
        fig, axes = plt.subplots(nrows=1, ncols=2)
        fig.set_figheight(5)
        fig.set_figwidth(13)
        fig.subplots_adjust(hspace=.5)
        axes[0].set_title('Evolution of MSE varying threshold (alpha='+str(alphas[0])+')')
        axes[1].set_title('Evolution of Accuracy varying threshold (alpha='+str(alphas[0])+')')
        axes[0].set_ylabel('MSE')
        axes[1].set_ylabel('Accuracy')
        axes[0].set_xlabel('Threshold')
        axes[1].set_xlabel('Threshold')
        axes[0].plot(ths, mse_list)
        axes[1].plot(ths, acc_list)
        plt.savefig('imgs/MSE+Acc_perc_varThs.png')

    # If threshold is fixed
    elif len(ths) == 1:
        mse_list = []
        acc_list = []
        L1 = [str(ths[0])]
        L2 = [str(ths[0])]
        headers = ['Threshold \ Alphas']
        for alpha in alphas:
            headers.append(str(alpha))
        for a in alphas:
            mse, std, acc, std2 = exec_real1(a, ths[0], DEFAULT_NREPS, DEFAULT_EPOCH)
            mse_list.append(mse)
            acc_list.append(acc)
            L1.append(str(mse)+' +- '+str(std))
            L2.append(str(acc)+' +- '+str(std2))
            print("Alpha:", a, "Threshold:", ths[0], "---> mse:", mse, ", acc:", acc)
        L_RES.append(L1)
        L_RES_ACC.append(L2)
        # Plotting
        fig, axes = plt.subplots(nrows=1, ncols=2)
        fig.set_figheight(5)
        fig.set_figwidth(13)
        fig.subplots_adjust(hspace=.5)
        axes[0].set_title('Evolution of MSE varying alpha (thresh='+str(ths[0])+')')
        axes[1].set_title('Evolution of Accuracy varying alpha (thresh='+str(ths[0])+')')
        axes[0].set_ylabel('MSE')
        axes[1].set_ylabel('Accuracy')
        axes[0].set_xlabel('Alpha')
        axes[1].set_xlabel('Alpha')
        axes[0].plot(alphas, mse_list)
        axes[1].plot(alphas, acc_list)
        plt.savefig('imgs/MSE+Acc_perc_varAlpha.png')

    # None is fixed
    else:
        headers = ["Thresholds \ Alphas"]
        for alpha in alphas:
            headers.append(str(alpha))
        for th in ths:
            L1 = [str(th)]
            L2 = [str(th)]
            for alpha in alphas:
                mse, std, acc, std2 = exec_real1(alpha, th, DEFAULT_NREPS, DEFAULT_EPOCH)
                L1.append(str(mse)+' +- '+str(std))
                L2.append(str(acc)+' +- '+str(std2))
                print("Alpha:", alpha, "Threshold:", th, "---> mse:", mse, ", acc:", acc)
            L_RES.append(L1)
            L_RES_ACC.append(L2)

    print(tabulate(L_RES, headers=headers, tablefmt="grid"))
    print(tabulate(L_RES_ACC, headers=headers, tablefmt="grid"))



def exec_real1(alpha, threshold, num_reps, max_epoch):
    '''
        Trains Perceptron algorithms and trains it several times in order to get
        mean MSE and mean accuracy.

        :param alpha: Learning parameter alpha
        :param threshold: Threshold. The algorithm activation function depends on this threshold
        :param num_reps: Number of simulations to calculate average values.
        :param max_epoch: Maximum number of epochs.
        :return: mean mse, std mse, mean accuracy, std accuracy
    '''
    mse_list = []
    acc_list = []
    for i in range(num_reps):
        # reading training and test sets
        sets = read1(FILE_PATH, DEFAULT_PERCENTAGE)
        xtrain, ytrain, xtest, ytest = sets
        # TODO: Coger una sola columna objetivo (target)
        n_inputs = len(xtrain[0])
        n_outputs = len(ytrain[0])

        perc_nn = Perceptron(n_inputs, n_outputs, threshold=threshold, alpha=alpha, verbose=False, max_epoch=max_epoch)

        perc_nn.train(xtrain, ytrain)
        ypred = perc_nn.predict(xtest)
        mse = perc_nn.error(ytest, ypred, metric='mse')
        acc = 1-perc_nn.error(ytest, ypred, metric='acc')
        mse_list.append(mse)
        acc_list.append(acc)

    mse_list = np.asarray(mse_list)
    acc_list = np.asarray(acc_list)
    return round(mse_list.mean(),5), round(mse_list.std(),3), round(acc_list.mean(),3), round(acc_list.std(),2)



if __name__ == '__main__':
    # hyperparameter validation
    if '-hyper' in sys.argv and '-a' not in sys.argv and '-th' not in sys.argv:
        val_hyperparams()
    # hyperparameter validation fixing alpha
    elif '-hyper' in sys.argv and '-a' in sys.argv and '-th' not in sys.argv:
        idx = sys.argv.index('-a')
        alpha = float(sys.argv[idx+1])
        val_hyperparams(alphas=[alpha])
    # hyperparameter validation fixing threshold
    elif '-hyper' in sys.argv and '-a' not in sys.argv and '-th' in sys.argv:
        idx = sys.argv.index('-th')
        th = float(sys.argv[idx+1])
        val_hyperparams(ths=[th])
    # executing with specified parameters
    else:
        alpha, threshold, num_reps, max_epoch = read_input_params()
        print("Executing Perceptron algorithm with parameters:")
        print("\tAlpha =", alpha)
        print("\tThreshold =", threshold)
        print("\tNumber of repetitions =", num_reps)
        print("\tNumber of maximum epochs =", max_epoch)
        mse, std, acc, std2 = exec_real1(alpha, threshold, num_reps, max_epoch)
        print("===> Mean Squared Error:", mse, "+-", std)
        print("===> Mean Accuracy:", acc, "+-", std2)
