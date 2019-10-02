--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p4ej1.vhf
-- /___/   /\     Timestamp : 11/30/2016 12:29:47
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/P4/p4ej1/p4ej1.vhf -w C:/Users/eps/Desktop/P4/p4ej1/p4ej1.sch
--Design Name: p4ej1
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

entity p4ej1 is
   port ( CLK      : in    std_logic; 
          MARCHA   : in    std_logic; 
          RESET    : in    std_logic; 
          CAFE     : out   std_logic; 
          CALENTAR : out   std_logic; 
          READY    : out   std_logic);
end p4ej1;

architecture BEHAVIORAL of p4ej1 is
   attribute BOX_TYPE   : string ;
   signal XLXN_10  : std_logic;
   signal XLXN_12  : std_logic;
   signal XLXN_13  : std_logic;
   signal XLXN_17  : std_logic;
   signal XLXN_26  : std_logic;
   signal XLXN_29  : std_logic;
   signal XLXN_31  : std_logic;
   signal XLXN_32  : std_logic;
   signal XLXN_35  : std_logic;
   signal XLXN_46  : std_logic;
   signal XLXN_47  : std_logic;
   signal XLXN_54  : std_logic;
   component FDC
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute BOX_TYPE of FDC : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component AND3B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B2 : component is "BLACK_BOX";
   
   component AND2B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B2 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component AND2B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B1 : component is "BLACK_BOX";
   
begin
   XLXI_4 : FDC
      port map (C=>CLK,
                CLR=>RESET,
                D=>XLXN_10,
                Q=>XLXN_17);
   
   XLXI_5 : FDC
      port map (C=>CLK,
                CLR=>RESET,
                D=>XLXN_26,
                Q=>XLXN_31);
   
   XLXI_6 : FDC
      port map (C=>CLK,
                CLR=>RESET,
                D=>XLXN_32,
                Q=>XLXN_35);
   
   XLXI_8 : AND2
      port map (I0=>XLXN_17,
                I1=>XLXN_31,
                O=>XLXN_46);
   
   XLXI_10 : AND3B2
      port map (I0=>XLXN_35,
                I1=>XLXN_31,
                I2=>XLXN_17,
                O=>XLXN_29);
   
   XLXI_11 : AND2B2
      port map (I0=>XLXN_35,
                I1=>XLXN_17,
                O=>XLXN_13);
   
   XLXI_12 : OR2
      port map (I0=>XLXN_13,
                I1=>XLXN_12,
                O=>XLXN_10);
   
   XLXI_13 : OR2
      port map (I0=>XLXN_29,
                I1=>XLXN_47,
                O=>XLXN_26);
   
   XLXI_14 : OR2
      port map (I0=>XLXN_46,
                I1=>XLXN_35,
                O=>XLXN_32);
   
   XLXI_15 : AND2
      port map (I0=>MARCHA,
                I1=>XLXN_35,
                O=>XLXN_12);
   
   XLXI_16 : OR2
      port map (I0=>XLXN_54,
                I1=>XLXN_31,
                O=>CALENTAR);
   
   XLXI_17 : AND2
      port map (I0=>XLXN_17,
                I1=>XLXN_35,
                O=>CAFE);
   
   XLXI_18 : AND2B1
      port map (I0=>XLXN_17,
                I1=>XLXN_35,
                O=>READY);
   
   XLXI_19 : AND2B1
      port map (I0=>XLXN_35,
                I1=>XLXN_17,
                O=>XLXN_54);
   
   XLXI_20 : AND2B1
      port map (I0=>XLXN_17,
                I1=>XLXN_31,
                O=>XLXN_47);
   
end BEHAVIORAL;


