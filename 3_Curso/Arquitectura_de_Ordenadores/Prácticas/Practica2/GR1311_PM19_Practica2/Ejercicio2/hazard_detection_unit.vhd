--------------------------------------------------------------------------------
-- Unidad de detección de riesgos. Curso Arquitectura 2018-19
--
-- Autores:
--		Alejandro Santorum Varela - alejandro.santorum@estudiante.uam.es
--		David Cabornero Pascual - david.cabornero@estudiante.uam.es
-- Grupo: 1311
-- Practica 2
-- Pareja: PM19
-- Fecha: 18/10/2018
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;


entity hazard_detection_unit is
	port (
		Rs_Id_hdu:	in std_logic_vector(4 downto 0);
		Rt_Id_hdu: 	in std_logic_vector(4 downto 0);
		Rt_Ex_hdu:  in std_logic_vector(4 downto 0);
		MemRead_IdEx_hdu:	in std_logic;
		PCWrite_hdu:	out std_logic;
		IfId_Write_hdu: out std_logic;
		HazardCode: out std_logic
	); 
end hazard_detection_unit;


architecture comportamental of hazard_detection_unit is

begin

	HazardCode <= '0' when (((Rs_Id_hdu = Rt_Ex_hdu) or (Rt_Id_hdu = Rt_Ex_hdu)) and (MemRead_IdEx_hdu='1')) else
						  '1';
						  
	PCWrite_hdu <= '0' when (((Rs_Id_hdu = Rt_Ex_hdu) or (Rt_Id_hdu = Rt_Ex_hdu)) and (MemRead_IdEx_hdu='1')) else
				   '1';
	
	IfId_Write_hdu <= '0' when (((Rs_Id_hdu = Rt_Ex_hdu) or (Rt_Id_hdu = Rt_Ex_hdu)) and (MemRead_IdEx_hdu='1')) else
				   '1';

end architecture;