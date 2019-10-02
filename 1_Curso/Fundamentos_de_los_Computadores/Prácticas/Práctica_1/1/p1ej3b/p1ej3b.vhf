--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p1ej3b.vhf
-- /___/   /\     Timestamp : 10/14/2016 12:29:53
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/1/p1ej3b/p1ej3b.vhf -w C:/Users/eps/Desktop/1/p1ej3b/p1ej3b.sch
--Design Name: p1ej3b
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

entity p1ej3b is
   port ( A : in    std_logic; 
          B : in    std_logic; 
          C : in    std_logic; 
          D : in    std_logic; 
          Z : out   std_logic);
end p1ej3b;

architecture BEHAVIORAL of p1ej3b is
   attribute BOX_TYPE   : string ;
   signal XLXN_11 : std_logic;
   signal XLXN_12 : std_logic;
   signal XLXN_15 : std_logic;
   signal XLXN_16 : std_logic;
   component NOR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NOR3 : component is "BLACK_BOX";
   
   component NOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NOR2 : component is "BLACK_BOX";
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   XLXI_1 : NOR3
      port map (I0=>XLXN_11,
                I1=>C,
                I2=>B,
                O=>XLXN_15);
   
   XLXI_2 : NOR3
      port map (I0=>XLXN_11,
                I1=>C,
                I2=>XLXN_12,
                O=>XLXN_16);
   
   XLXI_3 : NOR2
      port map (I0=>XLXN_16,
                I1=>XLXN_15,
                O=>Z);
   
   XLXI_4 : INV
      port map (I=>A,
                O=>XLXN_12);
   
   XLXI_5 : INV
      port map (I=>D,
                O=>XLXN_11);
   
end BEHAVIORAL;


