--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p2ej2_montaje.vhf
-- /___/   /\     Timestamp : 10/31/2016 13:50:39
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/P2/p2ej2_montaje/p2ej2_montaje.vhf -w C:/Users/eps/Desktop/P2/p2ej2_montaje/p2ej2_montaje.sch
--Design Name: p2ej2_montaje
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

entity M2_1E_MXILINX_p2ej2_montaje is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          E  : in    std_logic; 
          S0 : in    std_logic; 
          O  : out   std_logic);
end M2_1E_MXILINX_p2ej2_montaje;

architecture BEHAVIORAL of M2_1E_MXILINX_p2ej2_montaje is
   attribute BOX_TYPE   : string ;
   signal M0 : std_logic;
   signal M1 : std_logic;
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
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
begin
   I_36_30 : AND3
      port map (I0=>D1,
                I1=>E,
                I2=>S0,
                O=>M1);
   
   I_36_31 : AND3B1
      port map (I0=>S0,
                I1=>E,
                I2=>D0,
                O=>M0);
   
   I_36_38 : OR2
      port map (I0=>M1,
                I1=>M0,
                O=>O);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity M4_1E_MXILINX_p2ej2_montaje is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          D2 : in    std_logic; 
          D3 : in    std_logic; 
          E  : in    std_logic; 
          S0 : in    std_logic; 
          S1 : in    std_logic; 
          O  : out   std_logic);
end M4_1E_MXILINX_p2ej2_montaje;

architecture BEHAVIORAL of M4_1E_MXILINX_p2ej2_montaje is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal M01 : std_logic;
   signal M23 : std_logic;
   component M2_1E_MXILINX_p2ej2_montaje
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             E  : in    std_logic; 
             S0 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component MUXF5
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             S  : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of MUXF5 : component is "BLACK_BOX";
   
   attribute HU_SET of I_M01 : label is "I_M01_1";
   attribute HU_SET of I_M23 : label is "I_M23_0";
begin
   I_M01 : M2_1E_MXILINX_p2ej2_montaje
      port map (D0=>D0,
                D1=>D1,
                E=>E,
                S0=>S0,
                O=>M01);
   
   I_M23 : M2_1E_MXILINX_p2ej2_montaje
      port map (D0=>D2,
                D1=>D3,
                E=>E,
                S0=>S0,
                O=>M23);
   
   I_O : MUXF5
      port map (I0=>M01,
                I1=>M23,
                S=>S1,
                O=>O);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity p2ej2_montaje is
   port ( X0     : in    std_logic; 
          X1     : in    std_logic; 
          X2     : in    std_logic; 
          X3     : in    std_logic; 
          BOLA   : out   std_logic; 
          FIN    : out   std_logic; 
          PREMIO : out   std_logic);
end p2ej2_montaje;

architecture BEHAVIORAL of p2ej2_montaje is
   attribute BOX_TYPE   : string ;
   attribute HU_SET     : string ;
   signal XLXN_2       : std_logic;
   signal XLXN_3       : std_logic;
   signal XLXN_7       : std_logic;
   signal XLXN_11      : std_logic;
   signal XLXN_12      : std_logic;
   signal XLXN_13      : std_logic;
   signal XLXN_14      : std_logic;
   signal XLXN_16      : std_logic;
   signal XLXN_18      : std_logic;
   signal XLXN_27      : std_logic;
   signal XLXN_28      : std_logic;
   signal PREMIO_DUMMY : std_logic;
   signal FIN_DUMMY    : std_logic;
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
   
   component M4_1E_MXILINX_p2ej2_montaje
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             D2 : in    std_logic; 
             D3 : in    std_logic; 
             E  : in    std_logic; 
             S0 : in    std_logic; 
             S1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component INV
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of INV : component is "BLACK_BOX";
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_7 : label is "XLXI_7_2";
   attribute HU_SET of XLXI_8 : label is "XLXI_8_3";
begin
   FIN <= FIN_DUMMY;
   PREMIO <= PREMIO_DUMMY;
   XLXI_1 : AND2
      port map (I0=>XLXN_12,
                I1=>X1,
                O=>XLXN_14);
   
   XLXI_2 : AND2
      port map (I0=>X0,
                I1=>XLXN_11,
                O=>XLXN_16);
   
   XLXI_3 : AND2
      port map (I0=>XLXN_11,
                I1=>XLXN_12,
                O=>XLXN_2);
   
   XLXI_4 : AND2
      port map (I0=>X1,
                I1=>X0,
                O=>XLXN_3);
   
   XLXI_5 : OR2
      port map (I0=>XLXN_3,
                I1=>XLXN_2,
                O=>XLXN_18);
   
   XLXI_6 : OR2
      port map (I0=>FIN_DUMMY,
                I1=>PREMIO_DUMMY,
                O=>XLXN_7);
   
   XLXI_7 : M4_1E_MXILINX_p2ej2_montaje
      port map (D0=>XLXN_13,
                D1=>X0,
                D2=>XLXN_14,
                D3=>XLXN_14,
                E=>XLXN_27,
                S0=>X2,
                S1=>X3,
                O=>PREMIO_DUMMY);
   
   XLXI_8 : M4_1E_MXILINX_p2ej2_montaje
      port map (D0=>XLXN_18,
                D1=>XLXN_14,
                D2=>XLXN_16,
                D3=>XLXN_18,
                E=>XLXN_28,
                S0=>X2,
                S1=>X3,
                O=>FIN_DUMMY);
   
   XLXI_9 : INV
      port map (I=>X0,
                O=>XLXN_12);
   
   XLXI_10 : INV
      port map (I=>X1,
                O=>XLXN_11);
   
   XLXI_11 : INV
      port map (I=>XLXN_7,
                O=>BOLA);
   
   XLXI_14 : GND
      port map (G=>XLXN_13);
   
   XLXI_17 : VCC
      port map (P=>XLXN_27);
   
   XLXI_18 : VCC
      port map (P=>XLXN_28);
   
end BEHAVIORAL;


