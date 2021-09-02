Autores:
	· Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
	· José Manuel Chacón Aguilera - josem.chacon@estudiante.uam.es
Práctica 3 - Fundamentos Aprendizaje Automático
Fecha: 21 diciembre 2020
Grupo: 1462
Pareja: 9


Observación: Si se deseasen ejecutar las instrucciones del notebook se necesitan
Instalar ciertos paquetes de python3 no estándar:
· numpy (cálculos numérico y estructuras de datos)
· Scikit-learn (machine learning)
· Matplotlib (gráficas)
· tabulate (tablas)
· Pickle (persistencia de modelos en ficheros)
Entre otros.

Observación adicional: el clasificador AlgoritmoGenetico tiene tiempos de ejecución muy altos comparados con el resto de clasificadores. La gran mayoría de resultados y modelos entrenados a lo largo de la práctica se incluyen en la carpeta 'models_persistence'. Los ficheros de su interior pueden ser leídos con la librería pickel, tal y como se usan en las celdas del notebook adjunto. Esto nos permite cargar el modelo entrenado en cualquier momento sin tener que reestrenarlo cada vez que arrancamos el notebook. También guardamos el error medio cometido y desviación típica para cada uno.