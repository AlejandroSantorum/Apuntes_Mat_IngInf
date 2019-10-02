LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
LIBRARY UNISIM;
USE UNISIM.Vcomponents.ALL;

ENTITY p3ej3_tb IS
END p3ej3_tb;

ARCHITECTURE behavioral OF p3ej3_tb IS 

-- Define las entradas y salidas del circuito que se quiere simular (Unit Under Test, UUT)
   COMPONENT p3ej3
   PORT(  SIG_DIV	:	OUT	STD_LOGIC; 
          INIT	:	IN	STD_LOGIC;
			 CLK	:	IN	STD_LOGIC); 
   END COMPONENT;

-- Define las se�ales auxiliares para la simulaci�n a las que se les asiganr� valores o est�mulos   
   SIGNAL sig_div	:	STD_LOGIC;
   SIGNAL init :  STD_LOGIC;
	SIGNAL clk	:	STD_LOGIC;
   	
-- Define e inicializa otras se�ales o constantes auxiliares necesarias en la simulaci�n	
	SIGNAL finSimu : boolean := true;
	CONSTANT CLK_PERIOD : time := 10 ns; 
	
-- Comienzo del proceso de simulaci�n 
BEGIN

-- Asocia las se�ales de la UUT con las se�ales auxiliares para la simulaci�n(Instanciaci�n)
   UUT: p3ej3 PORT MAP(
		SIG_DIV => sig_div, 
		INIT => init,
		CLK => clk 
		);

-- Se define un proceso que simula la se�al del reloj, se ejecuta mientras dure la simulaci�n (105 periodos)
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

-- Se define un proceso de inicializaci�n del contador que se ejecuta solo una vez
-- Inicializa todos los FF a cero de forma as�ncrona
init_proc: process
	begin
		init <= '1';
		wait for CLK_PERIOD;
		init <= '0';
		wait for CLK_PERIOD*105;
		finSimu <= false ;
		wait;
	end process;

END;
