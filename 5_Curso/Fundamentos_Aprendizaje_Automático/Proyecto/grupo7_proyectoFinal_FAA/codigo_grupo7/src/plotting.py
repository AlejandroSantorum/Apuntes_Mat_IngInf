################################################################################
#   Authors:
#       · Alejandro Santorum Varela - alejandro.santorum@gmail.com
#       · Jose Manuel Chacon Aguilera - josem.chacon@estudiante.uam.es
#       · David Cabornero Pascual - david.cabornero@estudiante.uam.es
#       · Mario García Pascual - mario.garciapascual@estudiante.uam.es
#   File: plotting.py
#   Date: Feb. 1, 2021
#   Project: Gas Sensors Home Activity Monitoring
################################################################################

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt



def _plot_series(features_names, id, dataframe, axes, ox, oy, stim_start, stim_end, wrong_bool=None):
    '''
        INPUT:
            features_names: names of features to include in OY axis
            id: serie identifier
            dataframe: pandas dataframe
            axes: matplotlib.pyplot subplot axis
            ox: X axis identifier
            oy: Y axis identifier
            stim_start: moment when stimulus starts
            stim_end: moment when stimulus ends
            wrong_bool: Optional. Array of booleans where the i-th entry represents if the i-th
                        sample of specified serie has been misclassified. The length of array
                        'wrong_bool' must match the number of samples of specified serie.
        
        OUTPUT:
            None
        
        DESCRIPTION:
            It plots data of the given serie (ID required). In the X axis it's included time and in
            Y axis is represented the data of the specified features. It can also plot misclassified examples.
            This function mainly works as an auxiliary function.
    '''
    # Calculating minimum value
    min_val = dataframe[features_names[0]][dataframe.id==id].values[0]
    for feat_name in features_names:
        min_val_aux = min(dataframe[feat_name][dataframe.id==id])
        min_val = min(min_val, min_val_aux)

    # Calculating maximum value
    max_val = dataframe[features_names[0]][dataframe.id==id].values[0]
    for feat_name in features_names:
        max_val_aux = max(dataframe[feat_name][dataframe.id==id])
        max_val = max(max_val, max_val_aux)

    # Plotting features
    for feat_name in features_names:
        axes[ox,oy].plot(dataframe.time[dataframe.id==id], dataframe[feat_name][dataframe.id==id], linewidth = '2.0', label=feat_name)
    
    # Plotting start and end of stimulus
    axes[ox,oy].plot([stim_start, stim_start], [min_val, max_val])
    axes[ox,oy].plot([stim_end, stim_end], [min_val, max_val])

    # Plotting misclassified examples
    if wrong_bool is not None:
        for feat_name in features_names:
            axes[ox,oy].scatter(dataframe.time[dataframe.id==id][wrong_bool], dataframe[feat_name][dataframe.id==id][wrong_bool], label=feat_name+' mis')

    # Axis labels and legend
    ylabel_str = features_names[0]
    for i in range(1, len(features_names)):
        ylabel_str += ' and '+features_names[i]
    
    xlabel_str = 'Time (h.)'
    axes[ox,oy].set_title(ylabel_str + ' VS ' + xlabel_str)
    axes[ox,oy].set_xlabel(xlabel_str)
    axes[ox,oy].set_ylabel(ylabel_str)
    axes[ox,oy].legend()




def plot_allSeries_byID(id, dataframe, wrong_bool=None, probs_mtx=None):
    '''
        INPUT:
            id: serie ID
            dataframe: pandas dataframe
            wrong_bool: Optional. Array of booleans where the i-th entry represents if the i-th
                        sample of specified serie has been misclassified. The length of array
                        'wrong_bool' must match the number of samples of specified serie.
        
        OUTPUT:
            None
        
        DESCRIPTION: It plots all series (all sensors, humidity and temp.) with given ID.
    '''
    # nrows values is set according to the project
    if probs_mtx is not None:
        nrows = 4
    else:
        nrows = 3

    fig, axes = plt.subplots(nrows=nrows, ncols=2)
    fig.set_figheight(10)
    fig.set_figwidth(17)
    fig.subplots_adjust(hspace=.5)

    stim_start = dataframe.t0[dataframe.id==id].values[0]
    stim_end = dataframe.t0[dataframe.id==id].values[0] + dataframe.dt[dataframe.id==id].values[0]
    if 't0_delay' in dataframe and 'dt_delay' in dataframe:
        stim_start += dataframe['t0_delay'][dataframe.id==id].values[0]
        stim_end += dataframe['dt_delay'][dataframe.id==id].values[0]
    
    _plot_series(['Humidity'], id, dataframe, axes, 0, 0, stim_start, stim_end, wrong_bool)
    _plot_series(['Temp.'], id, dataframe, axes, 0, 1, stim_start, stim_end, wrong_bool)
    _plot_series(['R1', 'R2'], id, dataframe, axes, 1, 0, stim_start, stim_end, wrong_bool)
    _plot_series(['R3', 'R4'], id, dataframe, axes, 1, 1, stim_start, stim_end, wrong_bool)
    _plot_series(['R5', 'R6'], id, dataframe, axes, 2, 0, stim_start, stim_end, wrong_bool)
    _plot_series(['R7', 'R8'], id, dataframe, axes, 2, 1, stim_start, stim_end, wrong_bool)

    if probs_mtx is not None:
        axes[3,0].plot(dataframe.time[dataframe.id==id], probs_mtx[:,0], linewidth = '2.0', label='bg prob')
        axes[3,0].plot(dataframe.time[dataframe.id==id], probs_mtx[:,1], linewidth = '2.0', label='banana prob')
        axes[3,0].plot(dataframe.time[dataframe.id==id], probs_mtx[:,2], linewidth = '2.0', label='wine prob')
        axes[3,1].plot(dataframe.time[dataframe.id==id], probs_mtx[:,0], linewidth = '2.0', label='bg prob')
        axes[3,1].plot(dataframe.time[dataframe.id==id], probs_mtx[:,1], linewidth = '2.0', label='banana prob')
        axes[3,1].plot(dataframe.time[dataframe.id==id], probs_mtx[:,2], linewidth = '2.0', label='wine prob')
        axes[3,0].set_title('Predicted classes probabilities')
        axes[3,0].set_xlabel('Time (h.)')
        axes[3,0].set_ylabel('Probability')
        axes[3,0].legend(loc='upper left')
        axes[3,1].set_title('Predicted classes probabilities')
        axes[3,1].set_xlabel('Time (h.)')
        axes[3,1].set_ylabel('Probability')
        axes[3,1].legend(loc='upper left')

    stims = sorted(list(set(dataframe['class'][dataframe['id'] == id])))
    stim = stims[-1]
    plt.suptitle('Sensor Reading on Day '+str(id)+' ('+stim+')')





def _validate_id_test(df_test, id):
    unique_ids = list(set(df_test.id))

    # Checking introduced ID is in test set
    if id not in unique_ids:
        raise ValueError('series ID not in test set. Check introduced ID')


def get_nsamples_before_id(df_test, id):
    i = 0
    while df_test['id'].iloc[i] != id:
        i += 1
    return i


def _truncate_probs_mtx_by_ID(df_test, id, probs_mtx, nsamples=None):
    if nsamples is None:
        nsamples = get_nsamples_before_id(df_test, id)

    df_aux = df_test[df_test['id']==id]

    return probs_mtx[nsamples:nsamples+len(df_aux)]




def plot_misclassified_byID(df_test, id, y_true, y_pred, probs_mtx=None):
    '''
        INPUT:
            df_test: pandas dataframe. It is considered to be test dataframe,
                     but it can be the whole dataframe too, due to the fact
                     that series are selected by ID.
            id: serie identifier
            y_true: real class values
            y_pred: predicted class values
            probs_mtx (optional): numpy matrix. Outputed probability matrix for each class.

        OUTPUT:
            None
        
        DESCRIPTION:
            Given a serie ID on test set, it calculates the samples misclassified
            and plots the whole series, remarking misclassified examples.
    '''
    # checking ID is in test set
    _validate_id_test(df_test, id)

    # Selecting samples by ID
    df_aux = df_test[df_test.id==id]

    # Selecting misclassified samples (by hand, we have no ID info at y_pred & y_true)
    nsamples = get_nsamples_before_id(df_test, id)

    wrong_bool = (y_pred != y_true)
    wrong_bool = wrong_bool[nsamples:nsamples+len(df_aux)]

    if probs_mtx is not None:
        probs_mtx = _truncate_probs_mtx_by_ID(df_test, id, probs_mtx, nsamples=nsamples)

    plot_allSeries_byID(id, df_test, wrong_bool=wrong_bool, probs_mtx=probs_mtx)




def plot_probs_byID(df_test, id, probs_mtx):
    '''
        INPUT:
            df_test: pandas dataframe. It is considered to be test dataframe,
                     but it can be the whole dataframe too, due to the fact
                     that series are selected by ID.
            id: serie identifier
            y_true: real class values
            y_pred: predicted class values
            probs_mtx: numpy matrix. Outputed probability matrix for each class.

        OUTPUT:
            None
        
        DESCRIPTION:
            Given a serie ID on test set, it plots the whole series, including
            outputed probability for each class by the used model.
    '''
    # checking ID is in test set
    _validate_id_test(df_test, id)

    probs_mtx = _truncate_probs_mtx_by_ID(df_test, id, probs_mtx)

    plot_allSeries_byID(id, df_test, probs_mtx=probs_mtx)
