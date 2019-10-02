----------------------------------------------------------------------
-- Fichero: CircuitoTb.vhd
-- Descripción: Testbench para el tutorial de Xilinx con esquemáticos
-- Fecha última modificación: 2012-10-03

-- Autores: Alberto Sánchez (2012)
-- Asignatura: F.C. 1º grado. Ingeniería Informática.
-- Práctica: Tutorial Xilinx
-- Ejercicio: 1
----------------------------------------------------------------------


-- Declaración de bibliotecas. --
library ieee;
use ieee.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.Vcomponents.all;


-- Declaración de la entidad del testbench.
entity CircuitoTb is
end CircuitoTb;


-- Declaración de la arquitectura del testbench.
architecture behavioral of CircuitoTb is

	-- Declaración del componente que se va a probar. 
	component Circuito
	port( 
		A : in std_logic;
		B : in std_logic;
		C : in std_logic;
		D : in std_logic;
		Z : out std_logic
	);
	end component;

	-- Declaración de señales auxiliares.
	signal aAux, bAux, cAux, dAux, zAux : std_logic;
	-- signal entradas : std_logic_vector(3 downto 0);
	-- signal salidaEsperada : std_logic;
	
	-- Se define la constante INSTANTE. Su valor es indiferente, mientras sea mayor que 0. 
	-- Sirve para "dejar tiempo" a que el componente a probar (el esquemático realizado) establezca su salida.
	constant INSTANTE : time := 10 ns;
begin
	
	-- Instancia el componente a probar. Uniendo sus entradas/salidas con las señales auxiliares de este testbench
   uut: Circuito 
	port map(
		A => aAux,
		B => bAux,
		C => cAux,
		D => dAux,
		Z => zAux		
   );

	-- En este proceso se van a generar entradas (el equivalente a mover los interruptores en la proto board) y se comprobará su salida (equivalente a ver si los 
	-- leds de la proto board se encienden o no).
   metodoFacil : process
   begin
	
		-- Prueba del caso 0000
		aAux <= '0'; bAux <= '0'; cAux <= '0'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '1' report "Error en caso 0000" severity warning;
		
		-- Prueba del caso 0001
		aAux <= '0'; bAux <= '0'; cAux <= '0'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 0001" severity warning;
		
		-- Prueba del caso 0010
		aAux <= '0'; bAux <= '0'; cAux <= '1'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '1' report "Error en caso 0010" severity warning;
		
		-- Prueba del caso 0011
		aAux <= '0'; bAux <= '0'; cAux <= '1'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 0011" severity warning;
		
		-- Prueba del caso 0100
		aAux <= '0'; bAux <= '1'; cAux <= '0'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 0100" severity warning;
		
		-- Prueba del caso 0101
		aAux <= '0'; bAux <= '1'; cAux <= '0'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 0101" severity warning;
		
		-- Prueba del caso 0110
		aAux <= '0'; bAux <= '1'; cAux <= '1'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 0110" severity warning;
		
		-- Prueba del caso 0111
		aAux <= '0'; bAux <= '1'; cAux <= '1'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '1' report "Error en caso 0111" severity warning;
		
		-- Prueba del caso 1000
		aAux <= '1'; bAux <= '0'; cAux <= '0'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '1' report "Error en caso 1000" severity warning;
		
		-- Prueba del caso 1001
		aAux <= '1'; bAux <= '0'; cAux <= '0'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 1001" severity warning;
		
		-- Prueba del caso 1010
		aAux <= '1'; bAux <= '0'; cAux <= '1'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '1' report "Error en caso 1010" severity warning;
		
		-- Prueba del caso 1011
		aAux <= '1'; bAux <= '0'; cAux <= '1'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 1011" severity warning;
		
		-- Prueba del caso 1100
		aAux <= '1'; bAux <= '1'; cAux <= '0'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 1100" severity warning;
		
		-- Prueba del caso 1101
		aAux <= '1'; bAux <= '1'; cAux <= '0'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 1101" severity warning;
		
		-- Prueba del caso 1110
		aAux <= '1'; bAux <= '1'; cAux <= '1'; dAux <= '0';
		wait for INSTANTE;
		assert zAux = '1' report "Error en caso 1110" severity warning;
		
		-- Prueba del caso 1111
		aAux <= '1'; bAux <= '1'; cAux <= '1'; dAux <= '1';
		wait for INSTANTE;
		assert zAux = '0' report "Error en caso 1111" severity warning;
			
      wait; -- Evita que se repita la simulación continuamente
   end process metodoFacil;
	
	
	-- Este proceso realiza la misma función que el proceso anterior pero en menos líneas de codigo y lo hace escalable (es decir, si en vez de 4 entradas, el circuito a probar tuviera 20 entradas, con pequeñas modificaciones se podria probar el nuevo circuito)
	-- Para probar esta forma simplificada (el resultado tiene que ser el mismo), se debe descomentar las siguiente líneas de código, y comentar el anterior proceso
	
--		otroMetodo : process
--		begin
--			for i in 0 to 15
--			loop
--				entradas <= conv_std_logic_vector(i,4);
--				wait for INSTANTE;
--				assert zAux = salidaEsperada
--				report "Error en caso " & integer'image(i) severity warning;
--			end loop;
--			wait; -- Evita que se repita la simulación continuamente
--		end process otroMetodo;
--		
--		 aAux <= entradas(3);
--		 bAux <= entradas(2);
--		 cAux <= entradas(1);
--		 dAux <= entradas(0);
--
--     -- La siguiente línea define la función lógica que debería hacer el circuito
--		 salidaEsperada <= ( (not bAux) and (not dAux) ) or ( (not aAux) and bAux and cAux and dAux) or ( aAux and cAux and (not dAux) );
	 

	
end;
