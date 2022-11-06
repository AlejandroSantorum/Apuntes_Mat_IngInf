ayuda:
	@echo "Ejecute junto con make uno de los siguientes argumentos:"
	@echo "make ayuda_mc"
	@echo "make compila_mc"
	@echo "make ejecuta_mc"
	@echo "make compila"
	@echo "make ayuda_per"
	@echo "make ejecuta_per"
	@echo "make ayuda_ada"
	@echo "make ejecuta_ada"
	@echo "make requirements"
	@echo "make install_requirements"


# Commands for McCulloch-Pitts exercise
ayuda_mc:
	@echo "======> AYUDA PARA EL PROGRAMA: RED DE MCCULLOCH-PITTS <======"
	@echo "\t ·Nombre del programa ejecutable de Python3: ex_mcculloch_pitts.py"
	@echo "\t ·Posibles parámetros de entrada:"
	@echo "\t\t - (obligatorio) ruta fichero de lectura donde se especifican las entradas del ejercicio"
	@echo "\t ·EJEMPLO DE USO: python3 ex_mcculloch_pitts.py test_files/mccPitts_ex.txt"
	@echo "=============================================================================="

compila_mc:
	@echo "Python es un lenguaje interpretado"
	@echo "De todas formas, asegúrese de satisfacer los prerrequisitos:"
	@make requirements

ejecuta_mc:
	@python3 ex_mcculloch_pitts.py test_files/mccPitts_ex.txt


# Commands for Perceptron exercise
compila:
	@echo "Los scripts necesarios para analizar el problema real 1 no requieren de compilación"

ayuda_per:
	@echo "======> AYUDA PARA EL PROGRAMA: PERCEPTRON PROBLEMA REAL 1 <======"
	@echo "-> Se han programado dos scripts que permiten ejecutar el problema real 1:"
	@echo "\t ·Nombre script 1: ex_perceptron.py"
	@echo "\t ·Posibles parámetros de entrada:"
	@echo "\t\t - (obligatorio) modo de lectura de fichero: 1, 2 o 3"
	@echo "\t\t - (obligatorio) ruta primer fichero de lectura donde se especifican las entradas del ejercicio"
	@echo "\t\t - (opcional) ruta segundo fichero 2 de lectura (solo modo de lectura 3)"
	@echo "\t\t - [-a alpha] (opcional) donde alpha, la const. de aprendizaje, es un número real"
	@echo "\t\t - [-th threshold] (opcional) donde threshold, el umbral, es un número real"
	@echo "\t\t - [-mep max_epoch] (opcional) donde max_epoch, el no. máximo de épocas, es un entero"
	@echo "\t\t ·EJEMPLO DE USO 1: python3 ex_perceptron.py 2 test_files/problema_real1.txt -a 0.5 -th 0.0"
	@echo "\t\t ·EJEMPLO DE USO 2: python3 ex_perceptron.py 2 test_files/and.txt"
	@echo "\t\t ·DESCRIPCIÓN: Script que permite leer un fichero de datos y ejecutar el algoritmo perceptron con los parametros introducidos/por defecto."
	@echo "\t\t\t\t La salida incluye el ECM final y una tabla con los valores de entrada, salidas objetivos y salidas predichas"
	@echo "\t\t ---------------------------"
	@echo "\t ·Nombre script 2: prob_real1_perc.py"
	@echo "\t ·Posibles parámetros de entrada:"
	@echo "\t\t - [-hyper] (opcional) indica que se quiere hacer GridSearch."
	@echo "\t\t - [-a alpha] (opcional) donde alpha, la const. de aprendizaje, es un número real"
	@echo "\t\t - [-th threshold] (opcional) donde threshold, el umbral, es un número real"
	@echo "\t\t - [-nreps num_reps] (opcional) donde num_reps, número de repeticiones de simulación, es un número entero"
	@echo "\t\t - [-mep max_epoch] (opcional) donde max_epoch, el no. máximo de épocas, es un entero"
	@echo "\t\t ·EJEMPLO DE USO 1: python3 prob_real1_perc.py -hyper"
	@echo "\t\t ·EJEMPLO DE USO 2: python3 prob_real1_perc.py -a 0.5 -th 0.0"
	@echo "\t\t ·DESCRIPCIÓN: Script que permite leer un fichero de datos en modo 1 y ejecutar el algoritmo perceptron con los parametros introducidos/por defecto."
	@echo "\t\t\t\t Si se introduce el argumento -hyper se realiza un GridSearch sobre los hiperparámetros NO especificados."
	@echo "\t\t\t\t La salida incluye un resumen de los argumentos introducidos y el ECM final y la precisión media final."
	@echo "\t\t ---------------------------"
	@echo "=============================================================================="

ejecuta_per:
	@python3 prob_real1_perc.py -a 0.5 -th 0.0


# Commands for Adaline exercise
ayuda_ada:
	@echo "======> AYUDA PARA EL PROGRAMA: ADALINE PROBLEMA REAL 1 <======"
	@echo "-> Se han programado dos scripts que permiten ejecutar el problema real 1:"
	@echo "\t ·Nombre script 1: ex_adaline.py"
	@echo "\t ·Posibles parámetros de entrada:"
	@echo "\t\t - (obligatorio) modo de lectura de fichero: 1, 2 o 3"
	@echo "\t\t - (obligatorio) ruta primer fichero de lectura donde se especifican las entradas del ejercicio"
	@echo "\t\t - (opcional) ruta segundo fichero 2 de lectura (solo modo de lectura 3)"
	@echo "\t\t - [-a alpha] (opcional) donde alpha, la const. de aprendizaje, es un número real"
	@echo "\t\t - [-tol tolerance] (opcional) donde tolerance, la tolerancia, es un número real"
	@echo "\t\t ·EJEMPLO DE USO 1: python3 ex_adaline.py 2 test_files/problema_real1.txt -a 0.01 -th 0.01"
	@echo "\t\t ·EJEMPLO DE USO 2: python3 ex_adaline.py 2 test_files/and.txt"
	@echo "\t\t ·DESCRIPCIÓN: Script que permite leer un fichero de datos y ejecutar el algoritmo adaline con los parametros introducidos/por defecto."
	@echo "\t\t\t\t La salida incluye el ECM final y una tabla con los valores de entrada, salidas objetivos y salidas predichas"
	@echo "\t\t ---------------------------"
	@echo "\t ·Nombre script 2: prob_real1_ada.py"
	@echo "\t ·Posibles parámetros de entrada:"
	@echo "\t\t - [-hyper] (opcional) indica que se quiere hacer GridSearch."
	@echo "\t\t - [-a alpha] (opcional) donde alpha, la const. de aprendizaje, es un número real"
	@echo "\t\t - [-tol tolerance] (opcional) donde tolerance, la tolerancia, es un número real"
	@echo "\t\t - [-nreps num_reps] (opcional) donde num_reps, número de repeticiones de simulación, es un número entero"
	@echo "\t\t ·EJEMPLO DE USO 1: python3 prob_real1_ada.py -hyper"
	@echo "\t\t ·EJEMPLO DE USO 2: python3 prob_real1_ada.py -a 0.01 -th 0.01"
	@echo "\t\t ·DESCRIPCIÓN: Script que permite leer un fichero de datos en modo 1 y ejecutar el algoritmo adaline con los parametros introducidos/por defecto."
	@echo "\t\t\t\t Si se introduce el argumento -hyper se realiza un GridSearch sobre los hiperparámetros NO especificados."
	@echo "\t\t\t\t La salida incluye un resumen de los argumentos introducidos y el ECM final y la precisión media final."
	@echo "\t\t ---------------------------"
	@echo "=============================================================================="

ejecuta_ada:
	@python3 prob_real1_ada.py -a 0.01 -th 0.01


# General useful commands
.PHONY: doc
doc:
	mkdir -p doc
	pydoc -w `find . -name '*.py'`
	mv *.html doc

.PHONY: clean
clean:
	rm -f doc/*.html

requirements:
	@echo "===> LIBRERÍAS NO-ESTÁNDAR QUE DEBERÍAN INSTALARSE <==="
	@echo "\t numpy: librería de cálculo matemático eficiente para Python"
	@echo "\t matplotlib: librería para graficar distintas funciones o gráficos"
	@echo "\t tabulate: librería de formateo de tablas para Python"
	@echo "==> Si desea instalar dichas librerías, puede ejecutar \'make install_requirements\'"

install_requirements:
	@pip3 install numpy
	@pip3 install matplotlib
	@pip3 install tabulate
