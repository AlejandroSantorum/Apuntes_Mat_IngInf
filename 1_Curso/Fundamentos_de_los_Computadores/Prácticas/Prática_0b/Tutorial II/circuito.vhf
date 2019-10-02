--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : circuito.vhf
-- /___/   /\     Timestamp : 09/28/2016 12:24:50
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/Practicas/Tutorial/circuito.vhf -w C:/Users/eps/Desktop/Practicas/Tutorial/circuito.sch
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
   signal XLXN_10 : std_logic;
   signal XLXN_28 : std_logic;
   signal XLXN_29 : std_logic;
   signal XLXN_30 : std_logic;
   signal XLXN_31 : std_logic;
   signal XLXN_32 : std_logic;
   signal XLXN_33 : std_logic;
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
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
begin
   XLXI_2 : AND2
      port map (I0=>XLXN_32,
                I1=>XLXN_5,
                O=>XLXN_31);
   
   XLXI_3 : AND4
      port map (I0=>XLXN_10,
                I1=>B,
                I2=>C,
                I3=>D,
                O=>XLXN_29);
   
   XLXI_5 : INV
      port map (I=>B,
                O=>XLXN_5);
   
   XLXI_6 : INV
      port map (I=>D,
                O=>XLXN_32);
   
   XLXI_7 : INV
      port map (I=>A,
                O=>XLXN_10);
   
   XLXI_8 : OR2
      port map (I0=>XLXN_30,
                I1=>XLXN_31,
                O=>XLXN_28);
   
   XLXI_9 : OR2
      port map (I0=>XLXN_29,
                I1=>XLXN_28,
                O=>Z);
   
   XLXI_10 : AND2
      port map (I0=>A,
                I1=>C,
                O=>XLXN_33);
   
   XLXI_11 : AND2
      port map (I0=>XLXN_33,
                I1=>XLXN_32,
                O=>XLXN_30);
   
end BEHAVIORAL;


