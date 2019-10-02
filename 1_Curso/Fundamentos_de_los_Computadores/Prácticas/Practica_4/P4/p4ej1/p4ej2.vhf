--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p4ej2.vhf
-- /___/   /\     Timestamp : 11/30/2016 12:57:39
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/P4/p4ej1/p4ej2.vhf -w C:/Users/eps/Desktop/P4/p4ej1/p4ej2.sch
--Design Name: p4ej2
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

entity M2_1B1_MXILINX_p4ej2 is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          S0 : in    std_logic; 
          O  : out   std_logic);
end M2_1B1_MXILINX_p4ej2;

architecture BEHAVIORAL of M2_1B1_MXILINX_p4ej2 is
   attribute BOX_TYPE   : string ;
   signal M0 : std_logic;
   signal M1 : std_logic;
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
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
begin
   I_36_7 : AND2B2
      port map (I0=>S0,
                I1=>D0,
                O=>M0);
   
   I_36_8 : OR2
      port map (I0=>M1,
                I1=>M0,
                O=>O);
   
   I_36_9 : AND2
      port map (I0=>D1,
                I1=>S0,
                O=>M1);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity M2_1_MXILINX_p4ej2 is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          S0 : in    std_logic; 
          O  : out   std_logic);
end M2_1_MXILINX_p4ej2;

architecture BEHAVIORAL of M2_1_MXILINX_p4ej2 is
   attribute BOX_TYPE   : string ;
   signal M0 : std_logic;
   signal M1 : std_logic;
   component AND2B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B1 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
begin
   I_36_7 : AND2B1
      port map (I0=>S0,
                I1=>D0,
                O=>M0);
   
   I_36_8 : OR2
      port map (I0=>M1,
                I1=>M0,
                O=>O);
   
   I_36_9 : AND2
      port map (I0=>D1,
                I1=>S0,
                O=>M1);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity FTCLEX_MXILINX_p4ej2 is
   generic( INIT : bit :=  '0');
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          D   : in    std_logic; 
          L   : in    std_logic; 
          T   : in    std_logic; 
          Q   : out   std_logic);
end FTCLEX_MXILINX_p4ej2;

architecture BEHAVIORAL of FTCLEX_MXILINX_p4ej2 is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   attribute RLOC       : string ;
   signal MD      : std_logic;
   signal TQ      : std_logic;
   signal Q_DUMMY : std_logic;
   component M2_1_MXILINX_p4ej2
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             S0 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component FDCE
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   attribute BOX_TYPE of FDCE : component is "BLACK_BOX";
   
   attribute HU_SET of I_36_30 : label is "I_36_30_0";
   attribute RLOC of I_36_35 : label is "X0Y0";
begin
   Q <= Q_DUMMY;
   I_36_30 : M2_1_MXILINX_p4ej2
      port map (D0=>TQ,
                D1=>D,
                S0=>L,
                O=>MD);
   
   I_36_32 : XOR2
      port map (I0=>T,
                I1=>Q_DUMMY,
                O=>TQ);
   
   I_36_35 : FDCE
   generic map( INIT => INIT)
      port map (C=>C,
                CE=>CE,
                CLR=>CLR,
                D=>MD,
                Q=>Q_DUMMY);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity CB4CLED_MXILINX_p4ej2 is
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          D0  : in    std_logic; 
          D1  : in    std_logic; 
          D2  : in    std_logic; 
          D3  : in    std_logic; 
          L   : in    std_logic; 
          UP  : in    std_logic; 
          CEO : out   std_logic; 
          Q0  : out   std_logic; 
          Q1  : out   std_logic; 
          Q2  : out   std_logic; 
          Q3  : out   std_logic; 
          TC  : out   std_logic);
end CB4CLED_MXILINX_p4ej2;

architecture BEHAVIORAL of CB4CLED_MXILINX_p4ej2 is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal OR_CE_L  : std_logic;
   signal TC_DN    : std_logic;
   signal TC_UP    : std_logic;
   signal T1       : std_logic;
   signal T2       : std_logic;
   signal T2_DN    : std_logic;
   signal T2_UP    : std_logic;
   signal T3       : std_logic;
   signal T3_DN    : std_logic;
   signal T3_UP    : std_logic;
   signal XLXN_1   : std_logic;
   signal Q0_DUMMY : std_logic;
   signal Q1_DUMMY : std_logic;
   signal Q2_DUMMY : std_logic;
   signal Q3_DUMMY : std_logic;
   signal TC_DUMMY : std_logic;
   component FTCLEX_MXILINX_p4ej2
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             L   : in    std_logic; 
             T   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   
   component M2_1_MXILINX_p4ej2
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             S0 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component M2_1B1_MXILINX_p4ej2
      port ( D0 : in    std_logic; 
             D1 : in    std_logic; 
             S0 : in    std_logic; 
             O  : out   std_logic);
   end component;
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   component AND2B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B2 : component is "BLACK_BOX";
   
   component AND4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND4 : component is "BLACK_BOX";
   
   component AND4B4
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND4B4 : component is "BLACK_BOX";
   
   component AND3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3 : component is "BLACK_BOX";
   
   component AND3B3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND3B3 : component is "BLACK_BOX";
   
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
   
   attribute HU_SET of I_Q0 : label is "I_Q0_4";
   attribute HU_SET of I_Q1 : label is "I_Q1_3";
   attribute HU_SET of I_Q2 : label is "I_Q2_2";
   attribute HU_SET of I_Q3 : label is "I_Q3_1";
   attribute HU_SET of I_TC : label is "I_TC_7";
   attribute HU_SET of I_T1 : label is "I_T1_8";
   attribute HU_SET of I_T2 : label is "I_T2_5";
   attribute HU_SET of I_T3 : label is "I_T3_6";
begin
   Q0 <= Q0_DUMMY;
   Q1 <= Q1_DUMMY;
   Q2 <= Q2_DUMMY;
   Q3 <= Q3_DUMMY;
   TC <= TC_DUMMY;
   I_Q0 : FTCLEX_MXILINX_p4ej2
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D0,
                L=>L,
                T=>XLXN_1,
                Q=>Q0_DUMMY);
   
   I_Q1 : FTCLEX_MXILINX_p4ej2
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D1,
                L=>L,
                T=>T1,
                Q=>Q1_DUMMY);
   
   I_Q2 : FTCLEX_MXILINX_p4ej2
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D2,
                L=>L,
                T=>T2,
                Q=>Q2_DUMMY);
   
   I_Q3 : FTCLEX_MXILINX_p4ej2
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D3,
                L=>L,
                T=>T3,
                Q=>Q3_DUMMY);
   
   I_TC : M2_1_MXILINX_p4ej2
      port map (D0=>TC_DN,
                D1=>TC_UP,
                S0=>UP,
                O=>TC_DUMMY);
   
   I_T1 : M2_1B1_MXILINX_p4ej2
      port map (D0=>Q0_DUMMY,
                D1=>Q0_DUMMY,
                S0=>UP,
                O=>T1);
   
   I_T2 : M2_1_MXILINX_p4ej2
      port map (D0=>T2_DN,
                D1=>T2_UP,
                S0=>UP,
                O=>T2);
   
   I_T3 : M2_1_MXILINX_p4ej2
      port map (D0=>T3_DN,
                D1=>T3_UP,
                S0=>UP,
                O=>T3);
   
   I_36_1 : VCC
      port map (P=>XLXN_1);
   
   I_36_3 : AND2B2
      port map (I0=>Q1_DUMMY,
                I1=>Q0_DUMMY,
                O=>T2_DN);
   
   I_36_10 : AND4
      port map (I0=>Q3_DUMMY,
                I1=>Q2_DUMMY,
                I2=>Q1_DUMMY,
                I3=>Q0_DUMMY,
                O=>TC_UP);
   
   I_36_11 : AND4B4
      port map (I0=>Q3_DUMMY,
                I1=>Q2_DUMMY,
                I2=>Q1_DUMMY,
                I3=>Q0_DUMMY,
                O=>TC_DN);
   
   I_36_15 : AND3
      port map (I0=>Q2_DUMMY,
                I1=>Q1_DUMMY,
                I2=>Q0_DUMMY,
                O=>T3_UP);
   
   I_36_16 : AND3B3
      port map (I0=>Q2_DUMMY,
                I1=>Q1_DUMMY,
                I2=>Q0_DUMMY,
                O=>T3_DN);
   
   I_36_37 : AND2
      port map (I0=>Q1_DUMMY,
                I1=>Q0_DUMMY,
                O=>T2_UP);
   
   I_36_50 : AND2
      port map (I0=>CE,
                I1=>TC_DUMMY,
                O=>CEO);
   
   I_36_60 : OR2
      port map (I0=>CE,
                I1=>L,
                O=>OR_CE_L);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity p4ej1_MUSER_p4ej2 is
   port ( CLK      : in    std_logic; 
          MARCHA   : in    std_logic; 
          RESET    : in    std_logic; 
          CAFE     : out   std_logic; 
          CALENTAR : out   std_logic; 
          READY    : out   std_logic);
end p4ej1_MUSER_p4ej2;

architecture BEHAVIORAL of p4ej1_MUSER_p4ej2 is
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



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity p4ej2 is
   port ( CLK      : in    std_logic; 
          MARCHA   : in    std_logic; 
          RESET    : in    std_logic; 
          CAFE     : out   std_logic; 
          CALENTAR : out   std_logic; 
          READY    : out   std_logic);
end p4ej2;

architecture BEHAVIORAL of p4ej2 is
   attribute BOX_TYPE   : string ;
   attribute HU_SET     : string ;
   signal XLXN_1      : std_logic;
   signal XLXN_7      : std_logic;
   signal XLXN_17     : std_logic;
   signal XLXN_24     : std_logic;
   signal XLXN_32     : std_logic;
   signal XLXN_33     : std_logic;
   signal CAFE_DUMMY  : std_logic;
   signal READY_DUMMY : std_logic;
   component p4ej1_MUSER_p4ej2
      port ( CAFE     : out   std_logic; 
             CALENTAR : out   std_logic; 
             CLK      : in    std_logic; 
             MARCHA   : in    std_logic; 
             READY    : out   std_logic; 
             RESET    : in    std_logic);
   end component;
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component CB4CLED_MXILINX_p4ej2
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             D0  : in    std_logic; 
             D1  : in    std_logic; 
             D2  : in    std_logic; 
             D3  : in    std_logic; 
             L   : in    std_logic; 
             UP  : in    std_logic; 
             CEO : out   std_logic; 
             Q0  : out   std_logic; 
             Q1  : out   std_logic; 
             Q2  : out   std_logic; 
             Q3  : out   std_logic; 
             TC  : out   std_logic);
   end component;
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_3 : label is "XLXI_3_9";
begin
   CAFE <= CAFE_DUMMY;
   READY <= READY_DUMMY;
   XLXI_1 : p4ej1_MUSER_p4ej2
      port map (CLK=>CLK,
                MARCHA=>XLXN_1,
                RESET=>RESET,
                CAFE=>CAFE_DUMMY,
                CALENTAR=>CALENTAR,
                READY=>READY_DUMMY);
   
   XLXI_2 : OR2
      port map (I0=>XLXN_24,
                I1=>MARCHA,
                O=>XLXN_1);
   
   XLXI_3 : CB4CLED_MXILINX_p4ej2
      port map (C=>CLK,
                CE=>CAFE_DUMMY,
                CLR=>RESET,
                D0=>XLXN_32,
                D1=>XLXN_33,
                D2=>XLXN_33,
                D3=>XLXN_32,
                L=>XLXN_7,
                UP=>XLXN_17,
                CEO=>open,
                Q0=>open,
                Q1=>open,
                Q2=>open,
                Q3=>XLXN_24,
                TC=>open);
   
   XLXI_4 : AND2
      port map (I0=>READY_DUMMY,
                I1=>MARCHA,
                O=>XLXN_7);
   
   XLXI_6 : GND
      port map (G=>XLXN_33);
   
   XLXI_8 : VCC
      port map (P=>XLXN_17);
   
   XLXI_12 : VCC
      port map (P=>XLXN_32);
   
end BEHAVIORAL;


