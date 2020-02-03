/***************************************************************************
File: practica2.h
Project: Assignment 2 Communication Networks I
Authors:
	- Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
	- David Cabornero Pascual - david.cabornero@estudiante.uam.es
Date: 10-11-2018
***************************************************************************/
#ifndef PRACTICA2_H
#define PRACTICA2_H

/**
*	Handler of SIGINT signal
*/
void signal_handler(int nsignal);

/** 
*	Function that prints an error message warning
*	the user to introduce correctly the input parameters
*/
void invalid_input_message();

/**
*	Function that checks that the input parameters are correct
*/
void input_parameter_checking(int argc, char **argv);

/**
*	Package treatment function: it gets the specified fields of link level,
*	network level and transport level. It also applies the introduced filters
*/
void package_treat(u_char *user, const struct pcap_pkthdr *header, const uint8_t *pack);

#endif /* PRACTICA2_H */