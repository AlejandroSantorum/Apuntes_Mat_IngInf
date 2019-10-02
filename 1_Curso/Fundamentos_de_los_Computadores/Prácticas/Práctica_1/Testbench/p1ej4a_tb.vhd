----------------------------------------------------------------------
-- Fichero: P1EJ4a_tb.vhd
-- Descripción: Testbench para el ejercicio 4a de la práctica 1 2016
-- Práctica: 1  Ejercicio: 4a
----------------------------------------------------------------------

-- Declaración de bibliotecas. --
library ieee;
use ieee.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.Vcomponents.all;

-- Declaración de la entidad del testbench (nombre del archivo de simulación).
entity P1EJ4a_tb is
end P1EJ4a_tb;

architecture behavioral of P1EJ4a_tb is

	component P1EJ4a 				-- Nombre del archivo a simular.  
	PORT( 
		A : in std_logic; 
		B : in std_logic; 
		Cin : in std_logic; 
		S : out std_logic; 
		Cout : out std_logic
	);
   end component;
-- Definición de las señales auxiliares en las que se van a generan los valores de la simulación
   signal Aux_a : std_logic;
   signal Aux_b : std_logic;
   signal Aux_Cin : std_logic;
   signal Aux_s : std_logic;
   signal Aux_Cout : std_logic;
   signal Aux_Entrada : std_logic_vector(2 downto 0);
	
	
-- Se define la constante INSTANTE. Su valor es indiferente, mientras sea mayor que 0. 
-- Sirve para "dejar tiempo" a que el componente a probar (el esquemático realizado) establezca su salida.
	constant INSTANTE : time := 10 ns;

begin
-- Instancia el componente a probar. Se trata de asociar las señales auxiliares con las señales del archivo a simular (Unit Under Test, uut).
   
	UUT: P1EJ4a PORT MAP(
		A => Aux_a, 
		B => Aux_b, 
		Cin => Aux_Cin, 
		S => Aux_s, 
		Cout => Aux_Cout
   );
	
-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la proto board) y se comprobará su salida (equivalente a ver si los 
-- leds de la proto board se encienden o no).
	prueba : process
	begin
		for i in 0 to 7	-- genera las 8 combinaciones posibles para los 3 bits de entrada.
		loop
			Aux_Entrada <= conv_std_logic_vector(i,3);
			wait for INSTANTE;
		end loop;
		wait; -- Evita que se repita la simulación continuamente
	end process prueba;
	
	Aux_Cin <= Aux_Entrada(2);
	Aux_b <= Aux_Entrada(1);
	Aux_a <= Aux_Entrada(0);

end;
