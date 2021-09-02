################################################################################
#   Authors:
#       · Alejandro Santorum Varela - alejandro.santorum@gmail.com
#       · Jose Manuel Chacon Aguilera - josem.chacon@estudiante.uam.es
#       · David Cabornero Pascual - david.cabornero@estudiante.uam.es
#       · Mario García Pascual - mario.garciapascual@estudiante.uam.es
#   File: utils.py
#   Date: Feb. 1, 2021
#   Project: Gas Sensors Home Activity Monitoring
################################################################################

import math
import time
import pickle
import pandas as pd
import numpy as np
from collections import Counter
from sklearn.metrics import accuracy_score, f1_score, confusion_matrix, plot_confusion_matrix

from preprocessing import split_series_byID


DEFAULT_FEAT = ['R1', 'R2', 'R3', 'R4', 'R5', 'R6', 'R7', 'R8', 'Temp.', 'Humidity']

def split_train_test(dataframe, train_perc, features=DEFAULT_FEAT):
    '''
        INPUT:
            dataframe: pandas dataframe
            train_perc: float between 0 and 1. Train set percentage.
        
        OUTPUT:
            xtrain: pandas dataframe. X train set
            ytrain: pandas dataframe. Y train set
            xtest: pandas dataframe. X test set
            ytest: pandas dataframe. Y test set

        DESCRIPTION:
            It separates given pandas dataframe in 4 sub-dataframes:
            X train set, Y train set, X test set, Y test set.
    '''
    df_train, df_test = split_series_byID(train_perc, dataframe)
    xtrain, ytrain = df_train[features].values, df_train['class'].values
    xtest, ytest = df_test[features].values, df_test['class'].values
    return xtrain, ytrain, xtest, ytest




def metric_report(y_true, y_pred, plot_conf_mtx=False, clf=None, X=None):
    '''
        INPUT:
            y_true: target true values
            y_pred: predicted classes for test data
            plot_conf_mtx: Boolean. If set to True, clf and X params are required and it prints
                           confusion matrix. Default: False
            clf: estimator used to predict y_pred values. It's required to plot conf matrix
            X: test input values used to predict y_pred using clf. It's required to plot conf matrix

        OUTPUT:
            None

        DESCRIPTION:
            It prints a whole metric/score report, focusing on accuracy, each class recall and f1-score.

    '''
    occurrences_dict = Counter(y_true)
    bg_perc = occurrences_dict['background']/len(y_true)
    bg_banana = occurrences_dict['banana']/len(y_true)
    bg_wine = occurrences_dict['wine']/len(y_true)

    conf_m = confusion_matrix(y_true, y_pred, labels=['background', 'banana', 'wine'])

    recall_bg = conf_m[0][0]/sum(conf_m[0,:])   # predicted_bg / total_real_bg
    recall_ban = conf_m[1][1]/sum(conf_m[1,:])   # predicted_banana / total_real_banana
    recall_wine = conf_m[2][2]/sum(conf_m[2,:]) # predicted_wine / total_real_wine

    print('==============================================')
    print('TEST SET PROPORTIONS:')
    print('\tReal background percentage:', bg_perc)
    print('\tReal banana percentage:', bg_banana)
    print('\tReal wine percentage:', bg_wine)
    print('------------------------------------------')
    print('Accuracy:', accuracy_score(y_true, y_pred))
    print('Recall on background:', recall_bg)
    print('Recall on banana:', recall_ban)
    print('Recall on wine:', recall_wine)
    print('F1-score:', f1_score(y_true, y_pred, average='weighted'))
    if plot_conf_mtx:
        if clf is None or X is None:
            raise ValueError('To plot confusion matrix is required estimator and input X')
        else:
            plot_confusion_matrix(clf, X, y_true)
    print('==============================================')




def get_df_from_ID_list(main_df, id_list):
    # Selecting indixes
    bool_list = []
    for id in main_df.id:
        if id in id_list:
            bool_list.append(True)
        else:
            bool_list.append(False)
    
    return main_df[bool_list]



def get_df_excluding_ID_list(main_df, id_list):
    df = main_df[main_df['id']!=id_list[0]]

    if len(id_list) > 1:
        for id in id_list[1:]:
            df = df[df['id'] != id]

    return df




    


