--------------------------------------------------------------------------------
-- Unidad de adelantamiento para el control de riesgo de datos del MIPS.
-- Curso Arquitectura 2018-19
--
-- Autores:
--		Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
--		David Cabornero Pascual - david.cabornero@estudiante.uam.es
-- Grupo: 1311
-- Practica 2
-- Pareja: PM19
-- Fecha: 13/10/2018
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;


entity forwarding_unit is
	port (
		Rs_fu:	in std_logic_vector(4 downto 0);
		Rt_fu: 	in std_logic_vector(4 downto 0);
		Rd_ExMem_fu:  in std_logic_vector(4 downto 0);
		Rd_MemWb_fu:  in std_logic_vector(4 downto 0);
		RegWrite_ExMem_fu:	in std_logic;
		RegWrite_MemWb_fu:	in std_logic;
		MuxALUOp1_fu:	out std_logic_vector(1 downto 0);
		MuxALUOp2_fu:	out std_logic_vector(1 downto 0)
	); 
end forwarding_unit;


architecture comportamental of forwarding_unit is

begin
	MuxALUOp1_fu <= "10" when (RegWrite_ExMem_fu='1' and (Rd_ExMem_fu /= "00000") and (Rd_ExMem_fu = Rs_fu)) else
					"01" when (RegWrite_MemWb_fu='1' and (Rd_MemWb_fu /= "00000") and (Rd_MemWb_fu = Rs_fu)) else
					"00";
					
	MuxALUOp2_fu <= "10" when (RegWrite_ExMem_fu='1' and (Rd_ExMem_fu /= "00000") and (Rd_ExMem_fu = Rt_fu)) else
					"01" when (RegWrite_MemWb_fu='1' and (Rd_MemWb_fu /= "00000") and (Rd_MemWb_fu = Rt_fu)) else
					"00";

end architecture;