----------------------------------------------------------------------
-- Fichero: p2ej3_tb.vhd
-- Descripción: Testbench para Práctica 2 Ejercicio 3
-- Fecha última modificación: 18/10/2015

-- Autores: José Colás
-- Asignatura: Fundamentos de Computadores
-- Práctica: 2
-- Ejercicio: 3
----------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
LIBRARY UNISIM;
USE UNISIM.Vcomponents.ALL;

ENTITY p2ej3_tb IS
END p2ej3_tb;

ARCHITECTURE behavioral OF p2ej3_tb IS 

   COMPONENT p2ej3
   PORT( X0	:	IN	STD_LOGIC; 
          X1	:	IN	STD_LOGIC; 
          X2	:	IN	STD_LOGIC; 
          X3	:	IN	STD_LOGIC; 
          X4	:	IN	STD_LOGIC; 
          BOLA	:	OUT	STD_LOGIC);
   END COMPONENT;

   SIGNAL Aux_X0	:	STD_LOGIC;
   SIGNAL Aux_X1	:	STD_LOGIC;
   SIGNAL Aux_X2	:	STD_LOGIC;
   SIGNAL Aux_X3	:	STD_LOGIC;
   SIGNAL Aux_X4	:	STD_LOGIC;
   SIGNAL Aux_BOLA	:	STD_LOGIC;
	signal Aux_input :  std_logic_vector (4 downto 0);

 -- Se define la constante tiempo. Su valor es indiferente, mientras sea mayor que 0. 
   constant tiempo : time := 10 ns;

BEGIN

   UUT: p2ej3 PORT MAP(
		X0 => Aux_X0, 
		X1 => Aux_X1, 
		X2 => Aux_X2, 
		X3 => Aux_X3, 
		X4 => Aux_X4, 
		BOLA => Aux_BOLA
   );

-- Entrada
	Aux_X4<=Aux_input(4);
	Aux_X3<=Aux_input(3);
	Aux_X2<=Aux_input(2);
	Aux_X1<=Aux_input(1);
	Aux_X0<=Aux_input(0);
	
	

	-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la proto board) y se comprobará su salida (equivalente a ver si los 
	-- leds de la proto board se encienden o no).

	tb : PROCESS
	
	BEGIN
		for i in 0 to 31 loop
			Aux_input <= std_logic_vector(to_unsigned(i,5));
			wait for tiempo;
		end loop;
		report "Fin de simulación, verifique errores" severity note;
				
		-- dejamos todas las entradas a 0
		Aux_input <= "00000";

		WAIT; 

	END PROCESS;


END;