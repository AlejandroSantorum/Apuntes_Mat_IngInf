'''

    Authors:
        · Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
        · Sergio Galán Martín - sergio.galanm@estudiante.uam.es

    File: read_data_utils.py
    Date: Feb. 20, 2021
    Project: Assignment 1 - Neurocomputation [EPS-UAM]

    Description: This file contains the implementation of several reading functions.
        Its goal is to read the dataset/s and return the specified parameters.

'''


import sys, math, random


def _print_help():
    print("READ MODES AVAILABLE:")
    print("· IF READ MODE 1:")
    print("\t exec_file.py 1 <datafile_name> <train_percentage>")
    print("· IF READ MODE 2:")
    print("\t exec_file.py 2 <datafile_name>")
    print("· IF READ MODE 3:")
    print("\t exec_file.py 3 <train_datafile_name> <test_datafile_name>")



def parse_read_mode():
    '''
        Reads input arguments
    '''

    nparams = len(sys.argv)

    if nparams < 2:
        print("Error: Not enough input parameters")
        _print_help()
        exit()

    read_mode = int(sys.argv[1])

    if read_mode == 2:
        ret = read2(sys.argv[2])
        return read_mode, ret
    else:
        if nparams < 3:
            print("Error: Not enough files provided")
            _print_help()
            exit()
        else:
            if read_mode == 1:
                ret = read1(sys.argv[2], float(sys.argv[3]))
                return read_mode, ret
            elif read_mode == 3:
                ret = read3(sys.argv[2], sys.argv[3])
                return read_mode, ret
            else:
                print("Error: Wrong read mode [1,2,3]")
                _print_help()
                exit()



def read1(data_file, perc):
    '''
        Read Mode 1

        :param data_file: file to read the data.
        :param perc: percentage of data destined to train set. 1-perc is put into test set.
        :Observation: Data is shuffled before splitting.

        :return:
            s_train: train data matrix
            t_train: train target matrix
            s_test: test data matrix
            t_test: test target matrix
    '''

    with open(data_file, 'r') as f:
        # reading number of features (M) and number of classes (N)
        mn = f.readline().split()
        M = int(mn[0])
        N = int(mn[1])

        # reading file lines and calculating number of training examples
        file_lines = f.readlines()
        total_lines = len(file_lines)
        ntrain_examples = math.floor(perc*total_lines)
        # shuffling data matrix
        random.shuffle(file_lines)

        # building train set
        s_train = []
        t_train = []
        for i in range(ntrain_examples):
            data_line = file_lines[i][:-1].split()
            s_aux = []
            t_aux = []
            for i in range(M):
                s_aux.append(float(data_line[i]))
            for i in range(M,len(data_line)):
                t_aux.append(float(data_line[i]))
            s_train.append(s_aux)
            t_train.append(t_aux)

        # building test set
        s_test = []
        t_test = []
        for j in range(ntrain_examples, total_lines):
            data_line = file_lines[j][:-1].split()
            s_aux = []
            t_aux = []
            for i in range(M):
                s_aux.append(float(data_line[i]))
            for i in range(M,len(data_line)):
                t_aux.append(float(data_line[i]))
            s_test.append(s_aux)
            t_test.append(t_aux)

    return s_train, t_train, s_test, t_test




def read2(data_file):
    '''
        Read Mode 2

        :param data_file: file to read the data.
        :Observation: Train and test sets are the same.

        :return:
            s_train: train data matrix
            t_train: train target matrix
            s_test: test data matrix
            t_test: test target matrix
    '''

    with open(data_file, 'r') as f:
        # reading number of features (M) and number of classes (N)
        mn = f.readline().split()
        M = int(mn[0])
        N = int(mn[1])

        # reading file lines and calculating number of training examples
        file_lines = f.readlines()

        # building train/test set
        s = []
        t = []
        for line in file_lines:
            data_line = line[:-1].split()
            s_aux = []
            t_aux = []
            for i in range(M):
                s_aux.append(float(data_line[i]))
            for i in range(M,len(data_line)):
                t_aux.append(float(data_line[i]))
            s.append(s_aux)
            t.append(t_aux)

    return s, t, s, t



def read3(train_file, test_file):
    '''
        Read Mode 3

        :param train_file: file to read the train data.
        :param test_file: file to read the test data.

        :return:
            s_train: train data matrix
            t_train: train target matrix
            s_test: test data matrix
            t_test: test target matrix
    '''

    with open(train_file, 'r') as f:
        # reading number of features (M) and number of classes (N)
        mn = f.readline().split()
        M = int(mn[0])
        N = int(mn[1])

        # reading file lines and calculating number of training examples
        file_lines = f.readlines()

        # building train set
        s_train = []
        t_train = []
        for line in file_lines:
            data_line = line[:-1].split()
            s_aux = []
            t_aux = []
            for i in range(M):
                s_aux.append(float(data_line[i]))
            for i in range(M,len(data_line)):
                t_aux.append(float(data_line[i]))
            s_train.append(s_aux)
            t_train.append(t_aux)

    with open(test_file, 'r') as f:
        # reading number of features (M) and number of classes (N)
        mn = f.readline().split()
        M = int(mn[0])
        N = int(mn[1])

        # reading file lines and calculating number of test examples
        file_lines = f.readlines()

        # building test set
        s_test = []
        t_test = []
        for line in file_lines:
            data_line = line[:-1].split()
            s_aux = []
            t_aux = []
            for i in range(M):
                s_aux.append(float(data_line[i]))
            for i in range(M,len(data_line)):
                t_aux.append(float(data_line[i]))
            s_test.append(s_aux)
            t_test.append(t_aux)

    return s_train, t_train, s_test, t_test
