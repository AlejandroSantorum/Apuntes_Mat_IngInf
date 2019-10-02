--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p1ej3a.vhf
-- /___/   /\     Timestamp : 10/13/2016 11:28:13
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/1/p1ej3a/p1ej3a.vhf -w C:/Users/eps/Desktop/1/p1ej3a/p1ej3a.sch
--Design Name: p1ej3a
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

entity p1ej3a is
   port ( A : in    std_logic; 
          B : in    std_logic; 
          C : in    std_logic; 
          D : in    std_logic; 
          Z : out   std_logic);
end p1ej3a;

architecture BEHAVIORAL of p1ej3a is
   attribute BOX_TYPE   : string ;
   signal XLXN_9  : std_logic;
   signal XLXN_11 : std_logic;
   signal XLXN_12 : std_logic;
   signal XLXN_15 : std_logic;
   signal XLXN_19 : std_logic;
   signal XLXN_21 : std_logic;
   signal XLXN_22 : std_logic;
   signal XLXN_23 : std_logic;
   signal XLXN_25 : std_logic;
   signal XLXN_26 : std_logic;
   signal XLXN_27 : std_logic;
   signal XLXN_28 : std_logic;
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component OR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR3 : component is "BLACK_BOX";
   
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component AND3B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B1 : component is "BLACK_BOX";
   
   component XOR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR3 : component is "BLACK_BOX";
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   XLXI_1 : AND2
      port map (I0=>XLXN_25,
                I1=>XLXN_19,
                O=>XLXN_26);
   
   XLXI_2 : AND2
      port map (I0=>B,
                I1=>XLXN_15,
                O=>XLXN_23);
   
   XLXI_3 : OR2
      port map (I0=>XLXN_9,
                I1=>B,
                O=>XLXN_25);
   
   XLXI_4 : OR2
      port map (I0=>XLXN_11,
                I1=>XLXN_23,
                O=>XLXN_21);
   
   XLXI_5 : OR2
      port map (I0=>C,
                I1=>XLXN_9,
                O=>XLXN_28);
   
   XLXI_6 : OR3
      port map (I0=>XLXN_28,
                I1=>XLXN_27,
                I2=>XLXN_26,
                O=>Z);
   
   XLXI_7 : AND3
      port map (I0=>XLXN_22,
                I1=>XLXN_21,
                I2=>XLXN_25,
                O=>XLXN_27);
   
   XLXI_8 : AND3B1
      port map (I0=>XLXN_11,
                I1=>XLXN_12,
                I2=>A,
                O=>XLXN_22);
   
   XLXI_9 : XOR3
      port map (I0=>D,
                I1=>C,
                I2=>A,
                O=>XLXN_19);
   
   XLXI_10 : INV
      port map (I=>A,
                O=>XLXN_15);
   
   XLXI_11 : INV
      port map (I=>B,
                O=>XLXN_11);
   
   XLXI_12 : INV
      port map (I=>C,
                O=>XLXN_12);
   
   XLXI_13 : INV
      port map (I=>D,
                O=>XLXN_9);
   
end BEHAVIORAL;


