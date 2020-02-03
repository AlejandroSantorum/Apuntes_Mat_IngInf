--------------------------------------------------------------------------------
-- Bloque de control para la ALU. Arq0 2018.
--
-- Autores:
--		Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
--		David Cabornero Pascual - david.cabornero@estudiante.uam.es
-- Grupo: 1311
-- Pareja: PM19
-- Fecha: 06/10/2018
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity alu_control is
   port (
      -- Entradas:
      ALUOp  : in std_logic_vector (2 downto 0); -- Codigo control desde la unidad de control
      Funct  : in std_logic_vector (5 downto 0); -- Campo "funct" de la instruccion
      -- Salida de control para la ALU:
      ALUControl : out std_logic_vector (3 downto 0) -- Define operacion a ejecutar por ALU
   );
end alu_control;

architecture rtl of alu_control is
   
begin
	process(ALUOp, Funct)
		begin
			case ALUOp is
				when "000" => --Suma (sw,lw,addi)
					ALUControl <= "0000";
					
				when "001" => --Resta (beq)
					ALUControl <= "0001";
					
				when "010" => --Tipo R
					case Funct is
						when "100000" => --add
							ALUControl <= "0000";
						when "100100" => --and
							ALUControl <= "0100";
						when "100101" => --or
							ALUControl <= "0111";
						when "100010" => --sub
							ALUControl <= "0001";
						when "100110" => --xor
							ALUControl <= "0110";
						when "101010" => --slt
							ALUControl <= "1010";
						when "000000" => --NOP
							ALUControl <= "0000";
						when others => 
							ALUControl <= "----";
					end case;
				when "011" => --lui
					ALUControl <= "1101";
				when "100" => --slti
					ALUControl <= "1010";
				when others =>
					ALUControl <= "----";
			end case;
	end process;
end architecture;
