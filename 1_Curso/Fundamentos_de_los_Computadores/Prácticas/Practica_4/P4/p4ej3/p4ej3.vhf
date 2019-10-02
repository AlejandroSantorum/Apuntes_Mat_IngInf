--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p4ej3.vhf
-- /___/   /\     Timestamp : 12/07/2016 12:19:27
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/P4/p4ej3/p4ej3.vhf -w C:/Users/eps/Desktop/P4/p4ej3/p4ej3.sch
--Design Name: p4ej3
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

entity Memoria_MUSER_p4ej3 is
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
end Memoria_MUSER_p4ej3;

architecture BEHAVIORAL of Memoria_MUSER_p4ej3 is
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



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity p4ej3 is
   port ( CLK      : in    std_logic; 
          MARCHA   : in    std_logic; 
          RESET    : in    std_logic; 
          CAFE     : out   std_logic; 
          CALENTAR : out   std_logic; 
          READY    : out   std_logic);
end p4ej3;

architecture BEHAVIORAL of p4ej3 is
   attribute BOX_TYPE   : string ;
   signal XLXN_6   : std_logic;
   signal XLXN_7   : std_logic;
   signal XLXN_9   : std_logic;
   signal XLXN_10  : std_logic;
   signal XLXN_12  : std_logic;
   signal XLXN_13  : std_logic;
   signal XLXN_14  : std_logic;
   signal XLXN_15  : std_logic;
   component Memoria_MUSER_p4ej3
      port ( CAFE     : out   std_logic; 
             CALENTAR : out   std_logic; 
             D0       : out   std_logic; 
             D1       : out   std_logic; 
             D2       : out   std_logic; 
             D3       : out   std_logic; 
             MARCHA   : in    std_logic; 
             Q0       : in    std_logic; 
             Q1       : in    std_logic; 
             Q2       : in    std_logic; 
             Q3       : in    std_logic; 
             READY    : out   std_logic);
   end component;
   
   component FDC
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute BOX_TYPE of FDC : component is "BLACK_BOX";
   
begin
   XLXI_1 : Memoria_MUSER_p4ej3
      port map (MARCHA=>MARCHA,
                Q0=>XLXN_6,
                Q1=>XLXN_7,
                Q2=>XLXN_9,
                Q3=>XLXN_10,
                CAFE=>CAFE,
                CALENTAR=>CALENTAR,
                D0=>XLXN_12,
                D1=>XLXN_13,
                D2=>XLXN_14,
                D3=>XLXN_15,
                READY=>READY);
   
   XLXI_2 : FDC
      port map (C=>CLK,
                CLR=>RESET,
                D=>XLXN_12,
                Q=>XLXN_6);
   
   XLXI_3 : FDC
      port map (C=>CLK,
                CLR=>RESET,
                D=>XLXN_13,
                Q=>XLXN_7);
   
   XLXI_4 : FDC
      port map (C=>CLK,
                CLR=>RESET,
                D=>XLXN_14,
                Q=>XLXN_9);
   
   XLXI_5 : FDC
      port map (C=>CLK,
                CLR=>RESET,
                D=>XLXN_15,
                Q=>XLXN_10);
   
end BEHAVIORAL;


