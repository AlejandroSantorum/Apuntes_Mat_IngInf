----------------------------------------------------------------------
-- Fichero: p2ej1_tb.vhd
-- Descripción: Testbench para Práctica 2 Ejercicio 1
-- Fecha última modificación: 18/10/2015

-- Autores: José Colás
-- Asignatura: Fundamentos de Computadores
-- Práctica: 2
-- Ejercicio: 1
----------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
LIBRARY UNISIM;
USE UNISIM.Vcomponents.ALL;

ENTITY p2ej1_tb IS
END p2ej1_tb;

ARCHITECTURE behavioral OF p2ej1_tb IS 

   COMPONENT p2ej1
   PORT( X0	:	IN	STD_LOGIC; 
          X1	:	IN	STD_LOGIC; 
          X2	:	IN	STD_LOGIC; 
          X3	:	IN	STD_LOGIC; 
			 FIN	:	OUT	STD_LOGIC; 
          PREMIO	:	OUT	STD_LOGIC; 
          BOLA	:	OUT	STD_LOGIC);
			 
	END COMPONENT;

   SIGNAL Aux_X0	:	STD_LOGIC;
   SIGNAL Aux_X1	:	STD_LOGIC;
   SIGNAL Aux_X2	:	STD_LOGIC;
   SIGNAL Aux_X3	:	STD_LOGIC;
	SIGNAL Aux_FIN	:	STD_LOGIC;
   SIGNAL Aux_PREMIO	:	STD_LOGIC;
   SIGNAL Aux_BOLA	:	STD_LOGIC;
	


	signal input :  std_logic_vector (3 downto 0);

-- Se define la constante tiempo. Su valor es indiferente, mientras sea mayor que 0. 
   constant tiempo : time := 10 ns;

BEGIN

   UUT: p2ej1 PORT MAP(
		X0 => Aux_X0, 
		X1 => Aux_X1, 
		X2 => Aux_X2, 
		X3 => Aux_X3, 
		FIN => Aux_FIN, 
		PREMIO => Aux_PREMIO, 
		BOLA => Aux_BOLA
	);


	-- Entrada
	Aux_X3<=input(3);
	Aux_X2<=input(2);
	Aux_X1<=input(1);
	Aux_X0<=input(0);

-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la proto board) y se comprobará su salida (equivalente a ver si los 
-- leds de la proto board se encienden o no).
 
 tb : PROCESS
 BEGIN
	
	for i in 0 to 15 loop
			input <= std_logic_vector(to_unsigned(i,4));
			wait for tiempo;

		end loop;
		report "Fin de simulación, verifique errores" severity note;
				
		-- dejamos todas las entradas a 0
		input <= "0000";

		WAIT; 

	END PROCESS;

END;
