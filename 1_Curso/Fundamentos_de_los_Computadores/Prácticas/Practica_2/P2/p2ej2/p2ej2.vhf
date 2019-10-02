--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p2ej2.vhf
-- /___/   /\     Timestamp : 10/26/2016 12:13:30
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/P2/p2ej2/p2ej2.vhf -w C:/Users/eps/Desktop/P2/p2ej2/p2ej2.sch
--Design Name: p2ej2
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

entity M2_1E_MXILINX_p2ej2 is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          E  : in    std_logic; 
          S0 : in    std_logic; 
          O  : out   std_logic);
end M2_1E_MXILINX_p2ej2;

architecture BEHAVIORAL of M2_1E_MXILINX_p2ej2 is
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

entity M4_1E_MXILINX_p2ej2 is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          D2 : in    std_logic; 
          D3 : in    std_logic; 
          E  : in    std_logic; 
          S0 : in    std_logic; 
          S1 : in    std_logic; 
          O  : out   std_logic);
end M4_1E_MXILINX_p2ej2;

architecture BEHAVIORAL of M4_1E_MXILINX_p2ej2 is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal M01 : std_logic;
   signal M23 : std_logic;
   component M2_1E_MXILINX_p2ej2
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
   I_M01 : M2_1E_MXILINX_p2ej2
      port map (D0=>D0,
                D1=>D1,
                E=>E,
                S0=>S0,
                O=>M01);
   
   I_M23 : M2_1E_MXILINX_p2ej2
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

entity p2ej2 is
   port ( X0     : in    std_logic; 
          X1     : in    std_logic; 
          X2     : in    std_logic; 
          X3     : in    std_logic; 
          BOLA   : out   std_logic; 
          FIN    : out   std_logic; 
          PREMIO : out   std_logic);
end p2ej2;

architecture BEHAVIORAL of p2ej2 is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal XLXN_1  : std_logic;
   signal XLXN_2  : std_logic;
   signal XLXN_3  : std_logic;
   signal XLXN_44 : std_logic;
   signal XLXN_46 : std_logic;
   signal XLXN_47 : std_logic;
   signal XLXN_51 : std_logic;
   signal XLXN_52 : std_logic;
   signal XLXN_53 : std_logic;
   component M4_1E_MXILINX_p2ej2
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             D2 : in    std_logic; 
             D3 : in    std_logic; 
             E  : in    std_logic; 
             S0 : in    std_logic; 
             S1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   component XNOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XNOR2 : component is "BLACK_BOX";
   
   component AND2B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B1 : component is "BLACK_BOX";
   
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component NOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of NOR2 : component is "BLACK_BOX";
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_1 : label is "XLXI_1_2";
   attribute HU_SET of XLXI_2 : label is "XLXI_2_3";
   attribute HU_SET of XLXI_3 : label is "XLXI_3_4";
begin
   XLXI_1 : M4_1E_MXILINX_p2ej2
      port map (D0=>XLXN_44,
                D1=>XLXN_46,
                D2=>XLXN_47,
                D3=>XLXN_44,
                E=>XLXN_1,
                S0=>X2,
                S1=>X3,
                O=>FIN);
   
   XLXI_2 : M4_1E_MXILINX_p2ej2
      port map (D0=>XLXN_53,
                D1=>X0,
                D2=>XLXN_46,
                D3=>XLXN_46,
                E=>XLXN_2,
                S0=>X2,
                S1=>X3,
                O=>PREMIO);
   
   XLXI_3 : M4_1E_MXILINX_p2ej2
      port map (D0=>XLXN_51,
                D1=>XLXN_52,
                D2=>XLXN_44,
                D3=>XLXN_47,
                E=>XLXN_3,
                S0=>X2,
                S1=>X3,
                O=>BOLA);
   
   XLXI_4 : VCC
      port map (P=>XLXN_1);
   
   XLXI_5 : VCC
      port map (P=>XLXN_2);
   
   XLXI_6 : VCC
      port map (P=>XLXN_3);
   
   XLXI_9 : XNOR2
      port map (I0=>X0,
                I1=>X1,
                O=>XLXN_44);
   
   XLXI_10 : AND2B1
      port map (I0=>X0,
                I1=>X1,
                O=>XLXN_46);
   
   XLXI_11 : AND2B1
      port map (I0=>X1,
                I1=>X0,
                O=>XLXN_47);
   
   XLXI_12 : XOR2
      port map (I0=>X1,
                I1=>X0,
                O=>XLXN_51);
   
   XLXI_13 : NOR2
      port map (I0=>X1,
                I1=>X0,
                O=>XLXN_52);
   
   XLXI_15 : GND
      port map (G=>XLXN_53);
   
end BEHAVIORAL;


