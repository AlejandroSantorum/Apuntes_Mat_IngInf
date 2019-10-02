-- 
--
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
LIBRARY UNISIM;
USE UNISIM.Vcomponents.ALL;

ENTITY p3ej1a_tb IS
END p3ej1a_tb;

ARCHITECTURE behavioral OF p3ej1a_tb IS 

-- Define las entradas y salidas del circuito que se quiere simular (Unit Under Test, UUT)
   COMPONENT p3ej1a
   PORT(  Q0	:	OUT	STD_LOGIC; 
          Q1	:	OUT	STD_LOGIC; 
          Q2	:	OUT	STD_LOGIC; 
          Q3	:	OUT	STD_LOGIC; 
          CLK	:	IN	STD_LOGIC; 
          CLR	:	IN	STD_LOGIC);
   END COMPONENT;

-- Define las se�ales auxiliares para la simulaci�n a las que se les asiganr� valores o est�mulos   
	SIGNAL q0	:	STD_LOGIC;
   SIGNAL q1	:	STD_LOGIC;
   SIGNAL q2	:	STD_LOGIC;
   SIGNAL q3	:	STD_LOGIC;
   SIGNAL clk	:	STD_LOGIC;
   SIGNAL clr	:	STD_LOGIC;
	
-- Define e inicializa otras se�ales o constantes auxiliares necesarias en la simulaci�n	
   SIGNAL finSimu : boolean := true;
	CONSTANT CLK_PERIOD : time := 10 ns; 
   CONSTANT ESPERA : time := 5 ns;

-- Comienzo del proceso de simulaci�n 
BEGIN

-- Asocia las se�ales de la UUT con las se�ales auxiliares para la simulaci�n(Instanciaci�n)
   UUT: p3ej1a PORT MAP(
		Q0 => q0, 
		Q1 => q1, 
		Q2 => q2, 
		Q3 => q3, 
		CLK => clk, 
		CLR => clr
   );

-- Se define un proceso que simula la se�al del reloj, se ejecuta mientras dure la simulaci�n (16 periodos) y luego para
	CLKPROCESS: process
	begin
		while (finSimu) loop
			clk <= '0';
			wait for CLK_PERIOD/2;
			clk <= '1';
			wait for CLK_PERIOD/2;
		end loop;
		wait;
	end process;

-- Se define un proceso de incializaci�n que se ejecuta solo una vez y luego para
-- Inicializa todos los FF a cero de forma as�ncrona
init_proc: process
	begin
		clr <= '1';
		wait for ESPERA;
		clr <= '0';
		wait for CLK_PERIOD*16;
		finSimu <= false ;
		wait;
	end process;

END;
