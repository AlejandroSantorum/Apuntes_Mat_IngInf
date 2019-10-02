--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : Memoria.vhf
-- /___/   /\     Timestamp : 12/07/2016 12:19:27
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/P4/p4ej3/Memoria.vhf -w C:/Users/eps/Desktop/P4/p4ej3/Memoria.sch
--Design Name: Memoria
--Device: spartan3
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity Memoria is
   port ( MARCHA   : in    std_logic; 
          Q0       : in    std_logic; 
          Q1       : in    std_logic; 
          Q2       : in    std_logic; 
          Q3       : in    std_logic; 
          CAFE     : out   std_logic; 
          CALENTAR : out   std_logic; 
          D0       : out   std_logic; 
          D1       : out   std_logic; 
          D2       : out   std_logic; 
          D3       : out   std_logic; 
          READY    : out   std_logic);
end Memoria;

architecture BEHAVIORAL of Memoria is
   attribute INIT       : string ;
   attribute BOX_TYPE   : string ;
   component ROM32X1
      -- synopsys translate_off
      generic( INIT : bit_vector :=  x"00000000");
      -- synopsys translate_on
      port ( A0 : in    std_logic; 
             A1 : in    std_logic; 
             A2 : in    std_logic; 
             A3 : in    std_logic; 
             A4 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute INIT of ROM32X1 : component is "00000000";
   attribute BOX_TYPE of ROM32X1 : component is "BLACK_BOX";
   
   attribute INIT of XLXI_1 : label is "00FFC000";
   attribute INIT of XLXI_2 : label is "000000FC";
   attribute INIT of XLXI_3 : label is "00000300";
   attribute INIT of XLXI_4 : label is "03FFFC00";
   attribute INIT of XLXI_5 : label is "00333233";
   attribute INIT of XLXI_6 : label is "003C3C3C";
   attribute INIT of XLXI_7 : label is "03C03FC0";
begin
   XLXI_1 : ROM32X1
   -- synopsys translate_off
   generic map( INIT => x"00FFC000")
   -- synopsys translate_on
      port map (A0=>MARCHA,
                A1=>Q0,
                A2=>Q1,
                A3=>Q2,
                A4=>Q3,
                O=>D3);
   
   XLXI_2 : ROM32X1
   -- synopsys translate_off
   generic map( INIT => x"000000FC")
   -- synopsys translate_on
      port map (A0=>MARCHA,
                A1=>Q0,
                A2=>Q1,
                A3=>Q2,
                A4=>Q3,
                O=>CALENTAR);
   
   XLXI_3 : ROM32X1
   -- synopsys translate_off
   generic map( INIT => x"00000300")
   -- synopsys translate_on
      port map (A0=>MARCHA,
                A1=>Q0,
                A2=>Q1,
                A3=>Q2,
                A4=>Q3,
                O=>READY);
   
   XLXI_4 : ROM32X1
   -- synopsys translate_off
   generic map( INIT => x"03FFFC00")
   -- synopsys translate_on
      port map (A0=>MARCHA,
                A1=>Q0,
                A2=>Q1,
                A3=>Q2,
                A4=>Q3,
                O=>CAFE);
   
   XLXI_5 : ROM32X1
   -- synopsys translate_off
   generic map( INIT => x"00333233")
   -- synopsys translate_on
      port map (A0=>MARCHA,
                A1=>Q0,
                A2=>Q1,
                A3=>Q2,
                A4=>Q3,
                O=>D0);
   
   XLXI_6 : ROM32X1
   -- synopsys translate_off
   generic map( INIT => x"003C3C3C")
   -- synopsys translate_on
      port map (A0=>MARCHA,
                A1=>Q0,
                A2=>Q1,
                A3=>Q2,
                A4=>Q3,
                O=>D1);
   
   XLXI_7 : ROM32X1
   -- synopsys translate_off
   generic map( INIT => x"03C03FC0")
   -- synopsys translate_on
      port map (A0=>MARCHA,
                A1=>Q0,
                A2=>Q1,
                A3=>Q2,
                A4=>Q3,
                O=>D2);
   
end BEHAVIORAL;


