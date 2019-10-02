--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p1ej4a.vhf
-- /___/   /\     Timestamp : 10/13/2016 11:51:23
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/1/p1ej4a/p1ej4a.vhf -w C:/Users/eps/Desktop/1/p1ej4a/p1ej4a.sch
--Design Name: p1ej4a
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

entity p1ej4a is
   port ( A    : in    std_logic; 
          B    : in    std_logic; 
          Cin  : in    std_logic; 
          Cout : out   std_logic; 
          S    : out   std_logic);
end p1ej4a;

architecture BEHAVIORAL of p1ej4a is
   attribute BOX_TYPE   : string ;
   signal XLXN_1 : std_logic;
   signal XLXN_2 : std_logic;
   signal XLXN_3 : std_logic;
   component XOR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR3 : component is "BLACK_BOX";
   
   component OR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR3 : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
begin
   XLXI_1 : XOR3
      port map (I0=>B,
                I1=>A,
                I2=>Cin,
                O=>S);
   
   XLXI_2 : OR3
      port map (I0=>XLXN_3,
                I1=>XLXN_2,
                I2=>XLXN_1,
                O=>Cout);
   
   XLXI_3 : AND2
      port map (I0=>A,
                I1=>Cin,
                O=>XLXN_1);
   
   XLXI_4 : AND2
      port map (I0=>B,
                I1=>Cin,
                O=>XLXN_2);
   
   XLXI_5 : AND2
      port map (I0=>B,
                I1=>A,
                O=>XLXN_3);
   
end BEHAVIORAL;


