--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p1ej1.vhf
-- /___/   /\     Timestamp : 10/13/2016 10:43:18
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/1/p1ej1/p1ej1.vhf -w C:/Users/eps/Desktop/1/p1ej1/p1ej1.sch
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
   signal XLXN_4  : std_logic;
   signal XLXN_25 : std_logic;
   signal XLXN_26 : std_logic;
   signal XLXN_27 : std_logic;
   signal XLXN_28 : std_logic;
   signal XLXN_29 : std_logic;
   signal XLXN_30 : std_logic;
   signal XLXN_31 : std_logic;
   signal XLXN_51 : std_logic;
   component AND4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND4 : component is "BLACK_BOX";
   
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component OR4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR4 : component is "BLACK_BOX";
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
begin
   XLXI_1 : AND4
      port map (I0=>D,
                I1=>XLXN_27,
                I2=>XLXN_26,
                I3=>XLXN_25,
                O=>XLXN_1);
   
   XLXI_2 : AND3
      port map (I0=>XLXN_29,
                I1=>C,
                I2=>XLXN_28,
                O=>XLXN_2);
   
   XLXI_3 : AND3
      port map (I0=>XLXN_30,
                I1=>B,
                I2=>A,
                O=>XLXN_3);
   
   XLXI_4 : AND3
      port map (I0=>XLXN_51,
                I1=>XLXN_31,
                I2=>A,
                O=>XLXN_4);
   
   XLXI_5 : OR4
      port map (I0=>XLXN_4,
                I1=>XLXN_3,
                I2=>XLXN_2,
                I3=>XLXN_1,
                O=>Z);
   
   XLXI_10 : INV
      port map (I=>A,
                O=>XLXN_25);
   
   XLXI_11 : INV
      port map (I=>B,
                O=>XLXN_26);
   
   XLXI_12 : INV
      port map (I=>C,
                O=>XLXN_27);
   
   XLXI_13 : INV
      port map (I=>A,
                O=>XLXN_28);
   
   XLXI_14 : INV
      port map (I=>D,
                O=>XLXN_29);
   
   XLXI_15 : INV
      port map (I=>D,
                O=>XLXN_30);
   
   XLXI_16 : INV
      port map (I=>C,
                O=>XLXN_31);
   
   XLXI_17 : INV
      port map (I=>D,
                O=>XLXN_51);
   
end BEHAVIORAL;


