--------------------------------------------------------------------------------
-- Universidad Autonoma de Madrid
-- Escuela Politecnica Superior
-- Laboratorio de ARQ 2018
--
-- ALU simple.
-- - Soporta las operaciones: +, -, and, or, xor, not, slt, opb<<16
-- - Soporta el flag Zero
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity alu is
   port (
      OpA     : in  std_logic_vector (31 downto 0); -- Operando A
      OpB     : in  std_logic_vector (31 downto 0); -- Operando B
      Control : in  std_logic_vector ( 3 downto 0); -- Codigo de control=op. a ejecutar
      Result  : out std_logic_vector (31 downto 0); -- Resultado
      ZFlag   : out std_logic                       -- Flag Z
   );
end alu;

architecture rtl of alu is

   -- Tipo para los codigos de control de la ALU:
   subtype t_aluControl is std_logic_vector (3 downto 0);

   -- Codigos de control:
   constant ALU_OR   : t_aluControl := "0111";   
   constant ALU_NOT  : t_aluControl := "0101";
   constant ALU_XOR  : t_aluControl := "0110";
   constant ALU_AND  : t_aluControl := "0100";
   constant ALU_SUB  : t_aluControl := "0001";
   constant ALU_ADD  : t_aluControl := "0000";
   constant ALU_SLT  : t_aluControl := "1010";
   constant ALU_S16  : t_aluControl := "1101";

   -- Seniales intermedias:
   signal subExt    : std_logic_vector (32 downto 0); -- resta extendida a 33 bits
   signal sigResult : std_logic_vector (31 downto 0); -- alias interno de Result

begin

   subExt <= (OpA(31) & OpA) - (OpB(31) & OpB);

   process (Control, OpA, OpB, subExt)
   begin
      case Control is
         when ALU_OR  => sigResult <= OpA or OpB;
         when ALU_NOT => sigResult <= not OpA;
         when ALU_XOR => sigResult <= OpA xor OpB;
         when ALU_AND => sigResult <= OpA and OpB;
         when ALU_SUB => sigResult <= subExt (31 downto 0);
         when ALU_ADD => sigResult <= OpA + OpB;
         when ALU_SLT => sigResult <= x"0000000" & "000" & subExt(32);
         when ALU_S16 => sigResult <= OpB (15 downto 0) & x"0000";
         when others => sigResult <= (others => '0');
      end case;
   end process;

   Result <= sigResult;
   ZFlag  <= '1' when sigResult = x"00000000" else '0';

end architecture;
