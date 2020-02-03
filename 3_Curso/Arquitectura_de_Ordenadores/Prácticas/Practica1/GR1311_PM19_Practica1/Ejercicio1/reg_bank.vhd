--------------------------------------------------------------------------------
-- Universidad Autonoma de Madrid
-- Escuela Politecnica Superior
-- Laboratorio de Arq0 2018
--
-- Banco completo de registros del microprocesador MIPS
----------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity reg_bank is
   port (
      Clk   : in std_logic; -- Reloj activo en flanco de subida
      Reset : in std_logic; -- Reset asíncrono a nivel alto
      A1    : in std_logic_vector(4 downto 0);   -- Dirección para el puerto Rd1
      Rd1   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd1
      A2    : in std_logic_vector(4 downto 0);   -- Dirección para el puerto Rd2
      Rd2   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd2
      A3    : in std_logic_vector(4 downto 0);   -- Dirección para el puerto Wd3
      Wd3   : in std_logic_vector(31 downto 0);  -- Dato de entrada Wd3
      We3   : in std_logic -- Habilitación de la escritura de Wd3
   ); 
end reg_bank;

architecture rtl of reg_bank is

   -- Tipo y senial para almacenar los registros
   type regs_t is array (0 to 31) of std_logic_vector(31 downto 0);

   signal regs : regs_t;

begin

   ------------------------------------------------------
   -- Escritura de registro
   ------------------------------------------------------

   process(Clk, Reset)
   begin
      if Reset = '1' then
         for i in 0 to 31 loop
            regs(i) <= (others => '0');
         end loop;
      elsif rising_edge(Clk) then
         if We3 = '1' then
            if A3 /= "00000" then -- El R0 siempre es cero
               regs(conv_integer(A3)) <= Wd3;
            end if;
         end if;
      end if;
   end process;

   ------------------------------------------------------
   -- Lectura de registros
   ------------------------------------------------------
   Rd1 <= regs(conv_integer(A1));
   Rd2 <= regs(conv_integer(A2));

end architecture;

