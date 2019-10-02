----------------------------------------------------------------------
-- Fichero: P1EJ4b_tb.vhd
-- Descripción: Testbench para el ejercicio 4b de la práctica 1 2016
-- Práctica: 1  Ejercicio: 4b
-----------------------------------------------------------------

-- Declaración de bibliotecas. --
library ieee;
use ieee.std_logic_1164.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.Vcomponents.all;


-- Declaración de la entidad del testbench (nombre del archivo de simulación).
entity P1EJ4b_tb is
end P1EJ4b_tb;


architecture behavioral of P1EJ4b_tb is

	component p1ej4b 		-- Nombre del archivo a simular. 
	port( 
		Cin :  in std_logic;		-- Todas las señales del componente son todas de un bit
		A0 :   in std_logic;
		A1 :   in std_logic;
		A2 :   in std_logic;
		A3 :   in std_logic;
		B0 :   in std_logic;
		B1 :   in std_logic;
		B2 :   in std_logic;
		B3 :   in std_logic;
		S0 :   out std_logic;
		S1 :   out std_logic;
		S2 :   out std_logic;
		S3 :   out std_logic;
		Cout : out std_logic
	);
	end component;

-- Definición de las señales auxiliares en las que se van a generan los valores de la simulación. 	
   signal Aux_Cin:   std_logic;							-- Señal auxiliar de 1 bit
	signal Aux_A :   std_logic_vector(3 downto 0);  -- Señal auxiliar de 4 bits
	signal Aux_B :   std_logic_vector(3 downto 0);	-- Señal auxiliar de 4 bits
	signal Aux_S :   std_logic_vector(4 downto 0);	-- Señal auxiliar de 5 bits
	
-- Se define la constante INSTANTE. Su valor es indiferente, mientras sea mayor que 0. 
-- Sirve para "dejar tiempo" a que el componente a probar (el esquemático realizado) establezca su salida.
	constant DELAY : time := 10 ns;

	begin
-- Instancia el componente a probar. Se trata de asociar las señales auxiliares con las señales del archivo a simular (Unit Under Test, uut).
   	uut: p1Ej4b 
	port map(
		Cin => Aux_Cin,
		A0 => Aux_A(0),
		A1 => Aux_A(1),
		A2 => Aux_A(2),
		A3 => Aux_A(3),
		B0 => Aux_B(0),
		B1 => Aux_B(1),
		B2 => Aux_B(2),
		B3 => Aux_B(3),
		S0 => Aux_S(0),
		S1 => Aux_S(1),
		S2 => Aux_S(2),
		S3 => Aux_S(3),
      Cout => Aux_S(4)
	);

	-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la proto board) 
	prueba : process
	begin
	-- inicializamos todas las entradas a 0
		Aux_Cin <= '0';
		Aux_A <= "0000";
		Aux_B <= "0000";
		wait for DELAY;

			FOR j IN 0 TO 15 LOOP 			-- Genera todas la sumas posibles entre dos números naturales de 4 bits.
				Aux_B <= "0000";
				Aux_A <= std_logic_vector(to_unsigned(j,4));
				FOR k IN 0 TO 15 LOOP
					Aux_B <= std_logic_vector(to_unsigned(k,4));
					wait for DELAY;		
				END LOOP;
			END LOOP;

		-- dejamos todas las entradas a 0
		Aux_A <= "0000";
		Aux_B <= "0000";
		wait; 									-- Evita que se repita la simulación continuamente
	  
   end process prueba;
end;
