-----------------------------------------------------------------------
-- Fichero: P1EJ3a_tb.vhd
-- Descripción: Testbench para el ejercicio 3a de la práctica 1 2016
-- Práctica: 1 -- Ejercicio: 3a
----------------------------------------------------------------------

-- Declaración de bibliotecas. 
library ieee;
use ieee.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.Vcomponents.all;

-- Declaración de la entidad del testbench (nombre del archivo de simulación).
entity P1EJ3a_tb is
end P1EJ3a_tb;


architecture behavioral of P1EJ3a_tb is

	component P1EJ3a  			-- Nombre del archivo a simular.  
	PORT( 
		A : in std_logic; 
		B : in std_logic; 
		C : in std_logic; 
		D : in std_logic; 
		Z : out std_logic
	);
   end component;

-- Definición de las señales auxiliares en las que se van a generan los valores de la simulación							
   signal Aux_a : std_logic;
   signal Aux_b : std_logic;
   signal Aux_c : std_logic;
   signal Aux_d : std_logic;
	signal Aux_z : std_logic;
	signal Aux_Entrada : std_logic_vector(3 downto 0);
	
-- Se define la constante INSTANTE. Su valor es indiferente, mientras sea mayor que 0. 
-- Sirve para "dejar tiempo" a que el componente a probar (el esquemático realizado) establezca su salida.
	constant INSTANTE : time := 10 ns;

begin
-- Instancia el componente a probar. Se trata de asociar las señales auxiliares con las señales del archivo a simular (Unit Under Test, uut).
   uut: P1EJ3a port map(
		A => Aux_a,
		B => Aux_b, 
		C => Aux_c, 
		D => Aux_d, 
		Z => Aux_z 
	);
	
-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la protoboard) y se comprobará su salida (equivalente a ver si los 
-- leds de la protoboard se encienden o no).
	prueba : process
	begin
		for i in 0 to 15			-- genera las 16 combinaciones posibles para los 4 bits de entrada. 
		loop
			Aux_Entrada <= conv_std_logic_vector(i,4);
			wait for INSTANTE;
		end loop;
		wait; -- Evita que se repita la simulación continuamente
	end process prueba;
	
	Aux_a <= Aux_Entrada(3);
	Aux_b <= Aux_Entrada(2);
	Aux_c <= Aux_Entrada(1);
	Aux_d <= Aux_Entrada(0);

end;