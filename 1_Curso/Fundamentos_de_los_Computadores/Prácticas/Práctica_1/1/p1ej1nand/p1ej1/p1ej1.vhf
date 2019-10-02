--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p1ej1.vhf
-- /___/   /\     Timestamp : 10/14/2016 10:54:43
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl "C:/Users/eps/Desktop/1/Nueva carpeta/p1ej1/p1ej1.vhf" -w "C:/Users/eps/Desktop/1/Nueva carpeta/p1ej1/p1ej1.sch"
--Design Name: p1ej1
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

entity p1ej1 is
   port ( A : in    std_logic; 
          B : in    std_logic; 
          C : in    std_logic; 
          D : in    std_logic; 
          Z : out   std_logic);
end p1ej1;

architecture BEHAVIORAL of p1ej1 is
   attribute BOX_TYPE   : string ;
   signal XLXN_1  : std_logic;
   signal XLXN_2  : std_logic;
   signal XLXN_3  : std_logic;
   signal XLXN_6  : std_logic;
   signal XLXN_23 : std_logic;
   signal XLXN_24 : std_logic;
   signal XLXN_25 : std_logic;
   signal XLXN_26 : std_logic;
   component NAND4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NAND4 : component is "BLACK_BOX";
   
   component NAND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NAND3 : component is "BLACK_BOX";
   
   component NAND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NAND2 : component is "BLACK_BOX";
   
begin
   XLXI_1 : NAND4
      port map (I0=>XLXN_26,
                I1=>XLXN_25,
                I2=>XLXN_24,
                I3=>XLXN_23,
                O=>Z);
   
   XLXI_2 : NAND4
      port map (I0=>D,
                I1=>XLXN_3,
                I2=>XLXN_2,
                I3=>XLXN_1,
                O=>XLXN_23);
   
   XLXI_3 : NAND3
      port map (I0=>XLXN_6,
                I1=>C,
                I2=>XLXN_1,
                O=>XLXN_24);
   
   XLXI_4 : NAND3
      port map (I0=>XLXN_6,
                I1=>B,
                I2=>A,
                O=>XLXN_25);
   
   XLXI_5 : NAND3
      port map (I0=>XLXN_6,
                I1=>XLXN_3,
                I2=>A,
                O=>XLXN_26);
   
   XLXI_6 : NAND2
      port map (I0=>A,
                I1=>A,
                O=>XLXN_1);
   
   XLXI_7 : NAND2
      port map (I0=>B,
                I1=>B,
                O=>XLXN_2);
   
   XLXI_8 : NAND2
      port map (I0=>C,
                I1=>C,
                O=>XLXN_3);
   
   XLXI_10 : NAND2
      port map (I0=>D,
                I1=>D,
                O=>XLXN_6);
   
end BEHAVIORAL;


