-- Vhdl test bench created from schematic D:\Practicas_ISE\Pr2\p2ej2.sch - Wed Oct 19 18:46:13 2016
--
-- Notes: 
-- 1) This testbench template has been automatically generated using types
-- std_logic and std_logic_vector for the ports of the unit under test.
-- Xilinx recommends that these types always be used for the top-level
-- I/O of a design in order to guarantee that the testbench will bind
-- correctly to the timing (post-route) simulation model.
-- 2) To use this template as your testbench, change the filename to any
-- name of your choice with the extension .vhd, and use the "Source->Add"
-- menu in Project Navigator to import the testbench. Then
-- edit the user defined section below, adding code to generate the 
-- stimulus for your design.
--
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
LIBRARY UNISIM;
USE UNISIM.Vcomponents.ALL;

ENTITY p2ej2_montaje_tb IS
END p2ej2_montaje_tb;

ARCHITECTURE behavioral OF p2ej2_montaje_tb IS 

   COMPONENT p2ej2_montaje
   PORT( X3	:	IN	STD_LOGIC; 
          X2	:	IN	STD_LOGIC; 
          FIN	:	OUT	STD_LOGIC; 
          PREMIO	:	OUT	STD_LOGIC; 
          BOLA	:	OUT	STD_LOGIC; 
          X1	:	IN	STD_LOGIC; 
          X0	:	IN	STD_LOGIC);
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

   UUT: p2ej2_montaje PORT MAP(
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