--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 14.7
--  \   \         Application : sch2hdl
--  /   /         Filename : p3ej3.vhf
-- /___/   /\     Timestamp : 11/16/2016 12:05:12
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family spartan3 -flat -suppress -vhdl C:/Users/eps/Desktop/P3/p3ej3/p3ej3.vhf -w C:/Users/eps/Desktop/P3/p3ej3/p3ej3.sch
--Design Name: p3ej3
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

entity M2_1_MXILINX_p3ej3 is
   port ( D0 : in    std_logic; 
          D1 : in    std_logic; 
          S0 : in    std_logic; 
          O  : out   std_logic);
end M2_1_MXILINX_p3ej3;

architecture BEHAVIORAL of M2_1_MXILINX_p3ej3 is
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

entity FTCLEX_MXILINX_p3ej3 is
   generic( INIT : bit :=  '0');
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          D   : in    std_logic; 
          L   : in    std_logic; 
          T   : in    std_logic; 
          Q   : out   std_logic);
end FTCLEX_MXILINX_p3ej3;

architecture BEHAVIORAL of FTCLEX_MXILINX_p3ej3 is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   attribute RLOC       : string ;
   signal MD      : std_logic;
   signal TQ      : std_logic;
   signal Q_DUMMY : std_logic;
   component M2_1_MXILINX_p3ej3
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
   I_36_30 : M2_1_MXILINX_p3ej3
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

entity CD4CLE_MXILINX_p3ej3 is
   port ( C   : in    std_logic; 
          CE  : in    std_logic; 
          CLR : in    std_logic; 
          D0  : in    std_logic; 
          D1  : in    std_logic; 
          D2  : in    std_logic; 
          D3  : in    std_logic; 
          L   : in    std_logic; 
          CEO : out   std_logic; 
          Q0  : out   std_logic; 
          Q1  : out   std_logic; 
          Q2  : out   std_logic; 
          Q3  : out   std_logic; 
          TC  : out   std_logic);
end CD4CLE_MXILINX_p3ej3;

architecture BEHAVIORAL of CD4CLE_MXILINX_p3ej3 is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal OR_CE_L  : std_logic;
   signal TQ2      : std_logic;
   signal TQ03     : std_logic;
   signal T1       : std_logic;
   signal T2       : std_logic;
   signal T3       : std_logic;
   signal Q0_DUMMY : std_logic;
   signal Q1_DUMMY : std_logic;
   signal Q2_DUMMY : std_logic;
   signal Q3_DUMMY : std_logic;
   signal TC_DUMMY : std_logic;
   component FTCLEX_MXILINX_p3ej3
      generic( INIT : bit :=  '0');
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             L   : in    std_logic; 
             T   : in    std_logic; 
             Q   : out   std_logic);
   end component;
   
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
   
   component AND2B1
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2B1 : component is "BLACK_BOX";
   
   component AND4B2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND4B2 : component is "BLACK_BOX";
   
   attribute HU_SET of I_Q0 : label is "I_Q0_4";
   attribute HU_SET of I_Q1 : label is "I_Q1_3";
   attribute HU_SET of I_Q2 : label is "I_Q2_2";
   attribute HU_SET of I_Q3 : label is "I_Q3_1";
begin
   Q0 <= Q0_DUMMY;
   Q1 <= Q1_DUMMY;
   Q2 <= Q2_DUMMY;
   Q3 <= Q3_DUMMY;
   TC <= TC_DUMMY;
   I_Q0 : FTCLEX_MXILINX_p3ej3
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D0,
                L=>L,
                T=>OR_CE_L,
                Q=>Q0_DUMMY);
   
   I_Q1 : FTCLEX_MXILINX_p3ej3
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D1,
                L=>L,
                T=>T1,
                Q=>Q1_DUMMY);
   
   I_Q2 : FTCLEX_MXILINX_p3ej3
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D2,
                L=>L,
                T=>T2,
                Q=>Q2_DUMMY);
   
   I_Q3 : FTCLEX_MXILINX_p3ej3
      port map (C=>C,
                CE=>OR_CE_L,
                CLR=>CLR,
                D=>D3,
                L=>L,
                T=>T3,
                Q=>Q3_DUMMY);
   
   I_36_2 : AND2
      port map (I0=>T2,
                I1=>Q2_DUMMY,
                O=>TQ2);
   
   I_36_13 : OR2
      port map (I0=>TQ03,
                I1=>TQ2,
                O=>T3);
   
   I_36_123 : AND2
      port map (I0=>Q0_DUMMY,
                I1=>Q1_DUMMY,
                O=>T2);
   
   I_36_136 : AND2B1
      port map (I0=>Q3_DUMMY,
                I1=>Q0_DUMMY,
                O=>T1);
   
   I_36_143 : AND2
      port map (I0=>CE,
                I1=>TC_DUMMY,
                O=>CEO);
   
   I_36_168 : AND2
      port map (I0=>Q0_DUMMY,
                I1=>Q3_DUMMY,
                O=>TQ03);
   
   I_36_175 : AND4B2
      port map (I0=>Q1_DUMMY,
                I1=>Q2_DUMMY,
                I2=>Q0_DUMMY,
                I3=>Q3_DUMMY,
                O=>TC_DUMMY);
   
   I_36_178 : OR2
      port map (I0=>CE,
                I1=>L,
                O=>OR_CE_L);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity p3ej3 is
   port ( CLK     : in    std_logic; 
          INIT    : in    std_logic; 
          SIG_DIV : out   std_logic);
end p3ej3;

architecture BEHAVIORAL of p3ej3 is
   attribute HU_SET     : string ;
   attribute BOX_TYPE   : string ;
   signal XLXN_5        : std_logic;
   signal XLXN_6        : std_logic;
   signal XLXN_19       : std_logic;
   signal XLXN_27       : std_logic;
   signal XLXN_28       : std_logic;
   signal XLXN_31       : std_logic;
   signal XLXN_33       : std_logic;
   signal SIG_DIV_DUMMY : std_logic;
   component CD4CLE_MXILINX_p3ej3
      port ( C   : in    std_logic; 
             CE  : in    std_logic; 
             CLR : in    std_logic; 
             D0  : in    std_logic; 
             D1  : in    std_logic; 
             D2  : in    std_logic; 
             D3  : in    std_logic; 
             L   : in    std_logic; 
             CEO : out   std_logic; 
             Q0  : out   std_logic; 
             Q1  : out   std_logic; 
             Q2  : out   std_logic; 
             Q3  : out   std_logic; 
             TC  : out   std_logic);
   end component;
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
   component VCC
      port ( P : out   std_logic);
   end component;
   attribute BOX_TYPE of VCC : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_1 : label is "XLXI_1_5";
   attribute HU_SET of XLXI_2 : label is "XLXI_2_6";
begin
   SIG_DIV <= SIG_DIV_DUMMY;
   XLXI_1 : CD4CLE_MXILINX_p3ej3
      port map (C=>CLK,
                CE=>XLXN_6,
                CLR=>XLXN_28,
                D0=>XLXN_27,
                D1=>XLXN_28,
                D2=>XLXN_27,
                D3=>XLXN_28,
                L=>XLXN_19,
                CEO=>open,
                Q0=>open,
                Q1=>open,
                Q2=>open,
                Q3=>open,
                TC=>XLXN_5);
   
   XLXI_2 : CD4CLE_MXILINX_p3ej3
      port map (C=>CLK,
                CE=>XLXN_5,
                CLR=>XLXN_31,
                D0=>XLXN_33,
                D1=>XLXN_31,
                D2=>XLXN_33,
                D3=>XLXN_31,
                L=>XLXN_19,
                CEO=>open,
                Q0=>open,
                Q1=>open,
                Q2=>open,
                Q3=>open,
                TC=>SIG_DIV_DUMMY);
   
   XLXI_3 : GND
      port map (G=>XLXN_28);
   
   XLXI_4 : OR2
      port map (I0=>SIG_DIV_DUMMY,
                I1=>INIT,
                O=>XLXN_19);
   
   XLXI_5 : VCC
      port map (P=>XLXN_6);
   
   XLXI_6 : GND
      port map (G=>XLXN_31);
   
   XLXI_8 : VCC
      port map (P=>XLXN_33);
   
   XLXI_9 : VCC
      port map (P=>XLXN_27);
   
end BEHAVIORAL;


