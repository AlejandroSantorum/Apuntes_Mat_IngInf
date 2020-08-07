#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import string 

def main():
    '''En el directorio CONVERTIR_SWS hay que poner archivos sws que queremos convertir a ipynb; los notebooks de IPython 
    generados van a parar al directorio IPYNB'''
    os.chdir("CONVERTIR_SWS/")
    '''Estas tres lineas son para arreglar los nombres de los archivos, sustituyendo los espacios y los parentesis
    por caracteres que no producen errores'''
    os.system('rename "s/ /-/g" *')
    os.system('rename "s/\(/-/g" *')
    os.system('rename "s/\)/-/g" *')
    os.chdir('..')
    os.system("ls CONVERTIR_SWS/ > lista.txt")
    os.system("mv %s %s" %('lista.txt','CONVERTIR_SWS/'))
    os.system("cp %s %s" %('sws2sagews.py','CONVERTIR_SWS/'))
    os.system("cp %s %s" %('sagews2ipynb.py','CONVERTIR_SWS/'))
    os.chdir("CONVERTIR_SWS/")
    infile = open("lista.txt","r")
    for line in infile.readlines():
                print line+"\n"
                nombre = string.join(string.split(line[:-1],".")[:-1],sep=".")
		nombre_l = line[:-1]
		nombre_sagews = nombre+'.sagews'
		nombre_ipynb = nombre+'.ipynb'
		try:
                    os.system("python sws2sagews.py %s" %(nombre_l))
                except:
                    print "FALLO de sws2sagews \n"
                try:
                    os.system("python sagews2ipynb.py %s" %(nombre_sagews))
                except:
                    print "FALLO de sagews2ipnb \n"
		os.system("rm -f %s" %(nombre_sagews))
		os.system("mv %s %s" %(nombre_ipynb,'../IPYNB/'))
    os.system("rm %s" %('sws2sagews.py'))
    os.system("rm %s" %('sagews2ipynb.py'))
    infile.close()
    os.system("rm %s" %('lista.txt'))
		
    
if __name__ == "__main__": 
        main()
