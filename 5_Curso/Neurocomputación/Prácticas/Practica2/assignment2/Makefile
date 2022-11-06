ayuda:
	@echo "Ejecute junto con make uno de los siguientes argumentos:"
	@echo "make ayuda_retro"
	@echo "make compilar"
	@echo "make ejecuta_problema_real2"
	@echo "make ejecuta_problema_real6"
	@echo "make requirements"
	@echo "make install_requirements"

ayuda_retro:
	@echo "======> AYUDA PARA EL PROGRAMA: ex_multiperceptron <======"
	@echo "-> Se ha programado dos scripts que permiten ejecutar el problema real 1:"
	@echo "\t ·Nombre script 1: ex_multiperceptron.py"
	@echo "\t ·Posibles parámetros de entrada:"
	@echo "\t\t - (obligatorio) modo de lectura de fichero: 1, 2 o 3"
	@echo "\t\t - (obligatorio) ruta primer fichero de lectura donde se especifican las entradas del ejercicio"
	@echo "\t\t - (opcional) ruta segundo fichero 2 de lectura (solo modo de lectura 3) o porcentaje del trainset"
	@echo "\t\t - [-a alpha] (opcional, default=0.1) donde alpha, la const. de aprendizaje, es un número real"
	@echo "\t\t - [-h h1 h2 ... h_n] (opcional, default: 0 capas ocultas) donde h1, h2, ..., h_n son numeros enteros describiendo el numero de neuronas por capa oculta (n capas ocultas)"
	@echo "\t\t - [-nep n_epochs] (opcional, default=100) donde n_epochs es el número de épocas de entrenamiento, es un número entero"
	@echo "\t\t - [-b batch_size] (opcional, default=None) donde batch_size es el tamaño del entrenamiento por lotes"
	@echo "\t\t - [-hyper] (opcional), si se indica se ejecuta una búsqueda de hiperparámetros aleatoria"
	@echo "\t\t - [-norm] (opcional), si se indica se normalizan los datos"
	@echo "\t\t ·EJEMPLO DE USO 1: python3 ex_multiperceptron.py 1 test_files/problema_real1.txt 0.7 -a 0.1 -h 8 4 -nep 50 -batch_size 100 -norm"
	@echo "\t\t ·EJEMPLO DE USO 2: python3 ex_multiperceptron.py 1 test_files/problema_real1.txt 0.7 -hyper -norm"
	@echo "\t\t ·DESCRIPCIÓN: Script que permite leer un fichero de datos y ejecutar el algoritmo multiperceptron con los parametros introducidos/por defecto."
	@echo "\t\t\t\t La salida incluye el ECM final y una tabla con los valores de entrada, salidas objetivos y salidas predichas"
	@echo "=============================================================================="


compilar:
	@echo "Los scripts necesarios para ejecutar esta práctica no requieren de compilación"

# Problema real 2
ejecuta_problema_real2:
	@python3 ex_multiperceptron.py 1 test_files/problema_real2.txt 0.7 -a 0.265 -h 5 20 -nep 150


# Problema real 6
ejecuta_problema_real6:
	@python3 ex_multiperceptron.py 1 test_files/problema_real6.txt 0.7 -a 0.1 -h 20 -nep 5000 -norm 


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
