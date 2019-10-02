--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : circuito.vhf
-- /___/   /\     Timestamp : 09/21/2016 12:24:32
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl "C:/Users/eps/Desktop/Practicas 0a/Tutorial/circuito.vhf" -w "C:/Users/eps/Desktop/Practicas 0a/Tutorial/circuito.sch"
--Design Name: circuito
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

entity circuito is
   port ( A : in    std_logic; 
          B : in    std_logic; 
          C : in    std_logic; 
          D : in    std_logic; 
          Z : out   std_logic);
end circuito;

architecture BEHAVIORAL of circuito is
   attribute BOX_TYPE   : string ;
   signal XLXN_5  : std_logic;
   signal XLXN_7  : std_logic;
   signal XLXN_8  : std_logic;
   signal XLXN_9  : std_logic;
   signal XLXN_10 : std_logic;
   signal XLXN_24 : std_logic;
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component AND4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND4 : component is "BLACK_BOX";
   
   component OR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR3 : component is "BLACK_BOX";
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   XLXI_1 : AND3
      port map (I0=>A,
                I1=>C,
                I2=>XLXN_24,
                O=>XLXN_8);
   
   XLXI_2 : AND2
      port map (I0=>XLXN_24,
                I1=>XLXN_5,
                O=>XLXN_9);
   
   XLXI_3 : AND4
      port map (I0=>XLXN_10,
                I1=>B,
                I2=>C,
                I3=>D,
                O=>XLXN_7);
   
   XLXI_4 : OR3
      port map (I0=>XLXN_7,
                I1=>XLXN_8,
                I2=>XLXN_9,
                O=>Z);
   
   XLXI_5 : INV
      port map (I=>B,
                O=>XLXN_5);
   
   XLXI_6 : INV
      port map (I=>D,
                O=>XLXN_24);
   
   XLXI_7 : INV
      port map (I=>A,
                O=>XLXN_10);
   
end BEHAVIORAL;


