--------------------------------------------------------------------------------
-- Unidad de control principal del micro. Arq0 2018
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

entity control_unit is
   port (
      -- Entrada = codigo de operacion en la instruccion:
      OpCode  : in  std_logic_vector (5 downto 0);
      -- Seniales para el PC
      Branch : out  std_logic; -- 1=Ejecutandose instruccion branch
	  Jump : out std_logic; -- 1=Ejecutandose instruccion jump
      -- Seniales relativas a la memoria
      MemToReg : out  std_logic; -- 1=Escribir en registro la salida de la mem.
      MemWrite : out  std_logic; -- Escribir la memoria
      MemRead  : out  std_logic; -- Leer la memoria
      -- Seniales para la ALU
      ALUSrc : out  std_logic;                     -- 0=oper.B es registro, 1=es valor inm.
      ALUOp  : out  std_logic_vector (2 downto 0); -- Tipo operacion para control de la ALU
      -- Seniales para el GPR
      RegWrite : out  std_logic; -- 1=Escribir registro
      RegDst   : out  std_logic  -- 0=Reg. destino es rt, 1=rd
   );
end control_unit;

architecture rtl of control_unit is

   -- Tipo para los codigos de operacion:
   subtype t_opCode is std_logic_vector (5 downto 0);

   -- Codigos de operacion para las diferentes instrucciones:
   constant OP_RTYPE  : t_opCode := "000000";
   constant OP_BEQ    : t_opCode := "000100";
   constant OP_SW     : t_opCode := "101011";
   constant OP_LW     : t_opCode := "100011";
   constant OP_LUI    : t_opCode := "001111";
   constant OP_SLTI	  : t_opCode := "001010";
   constant OP_ADDI	  : t_opCode := "001000";
   constant OP_JUMP	  : t_opCode := "000010";

begin

	process(OpCode)
		begin
			case OpCode is
				when OP_ADDI => --addi
					Branch <= '0';
					Jump <= '0';
					MemToReg <= '0';
					MemWrite <= '0';
					MemRead <= '0';
					ALUSrc <= '1';
					RegWrite <= '1';
					RegDst <= '0';
					ALUOp <= "000";
					
				when OP_SLTI => --slti
					Branch <= '0';
					Jump <= '0';
					MemToReg <= '0';
					MemWrite <= '0';
					MemRead <= '0';
					ALUSrc <= '1';
					RegWrite <= '1';
					RegDst <= '0';
					ALUOp <= "100";
					
				when OP_BEQ => --beq
					Branch <= '1';
					Jump <= '0';
					MemToReg <= '-';
					MemWrite <= '0';
					MemRead <= '0';
					ALUSrc <= '0';
					RegWrite <= '0';
					RegDst <= '-';
					ALUOp <= "001";
				
				when OP_JUMP => -- j
					Branch <= '-';
					Jump <= '1';
					MemToReg <= '-';
					MemWrite <= '0';
					MemRead <= '0';
					ALUSrc <= '-';
					RegWrite <= '0';
					RegDst <= '-';
					ALUOp <= "---";
				
				when OP_LW => --lw
					Branch <= '0';
					Jump <= '0';
					MemToReg <= '1';
					MemWrite <= '0';
					MemRead <= '1';
					ALUSrc <= '1';
					RegWrite <= '1';
					RegDst <= '0';
					ALUOp <= "000";
					
				when OP_SW => --sw
					Branch <= '0';
					Jump <= '0';
					MemToReg <= '-';
					MemWrite <= '1';
					MemRead <= '0';
					ALUSrc <= '1';
					RegWrite <= '0';
					RegDst <= '-';
					ALUOp <= "000";
				
				when OP_LUI => --lui
					Branch <= '0';
					Jump <= '0';
					MemToReg <= '0';
					MemWrite <= '0';
					MemRead <= '0';
					ALUSrc <= '1';
					RegWrite <= '1';
					RegDst <= '0';
					ALUOp <= "011";
					
				when OP_RTYPE => --Tipo R 
					Branch <= '0';
					Jump <= '0';
					MemToReg <= '0';
					MemWrite <= '0';
					MemRead <= '0';
					ALUSrc <= '0';
					RegWrite <= '1';
					RegDst <= '1';
					ALUOp <= "010";
				
				when others =>
					Branch <= '0';
					Jump <= '0';
					MemToReg <= '-';
					MemWrite <= '0';
					MemRead <= '0';
					ALUSrc <= '-';
					RegWrite <= '0';
					RegDst <= '-';
					ALUOp <= "---";
			end case;
		end process;
end architecture;
