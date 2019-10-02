--
--Design Name: p4ej1_tb
--Device: Xilinx
--

library UNISIM;
use UNISIM.Vcomponents.ALL;
library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
USE IEEE.STD_LOGIC_TEXTIO.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE STD.TEXTIO.ALL;

ENTITY p4ej1_tb IS
END p4ej1_tb;

ARCHITECTURE testbench_arch OF p4ej1_tb IS
    FILE RESULTS: TEXT OPEN WRITE_MODE IS "results.txt";

    COMPONENT p4ej1
        PORT (
            CLK : In std_logic;
            RESET : In std_logic;
            MARCHA : In std_logic;
            CAFE : Out std_logic;
            CALENTAR : Out std_logic;
            READY : Out std_logic
        );
    END COMPONENT;

    SIGNAL CLK : std_logic := '0';
    SIGNAL RESET : std_logic := '0';
    SIGNAL MARCHA : std_logic := '0';
    SIGNAL CAFE : std_logic := '0';
    SIGNAL CALENTAR : std_logic := '0';
    SIGNAL READY : std_logic := '0';

    constant PERIOD : time := 200 ns;
    constant DUTY_CYCLE : real := 0.5;
    constant OFFSET : time := 100 ns;

    BEGIN
        UUT : p4ej1
        PORT MAP (
            CLK => CLK,
            RESET => RESET,
            MARCHA => MARCHA,
            CAFE => CAFE,
            CALENTAR => CALENTAR,
            READY => READY
        );

        PROCESS    -- clock process for CLK
        BEGIN
            WAIT for OFFSET;
            CLOCK_LOOP : LOOP
                CLK <= '0';
                WAIT FOR (PERIOD - (PERIOD * DUTY_CYCLE));
                CLK <= '1';
                WAIT FOR (PERIOD * DUTY_CYCLE);
            END LOOP CLOCK_LOOP;
        END PROCESS;

        PROCESS
            BEGIN
                -- -------------  Current Time:  385ns
                WAIT FOR 385 ns;
                RESET <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  1185ns
                WAIT FOR 800 ns;
                RESET <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  2785ns
                WAIT FOR 1600 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  3385ns
                WAIT FOR 600 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  3785ns
                WAIT FOR 400 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  4385ns
                WAIT FOR 600 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  4985ns
                WAIT FOR 600 ns;
                RESET <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  5385ns
                WAIT FOR 400 ns;
                RESET <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  5585ns
                WAIT FOR 200 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  5785ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  6585ns
                WAIT FOR 800 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  6985ns
                WAIT FOR 400 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  7585ns
                WAIT FOR 600 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  7785ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                WAIT FOR 2415 ns;

            END PROCESS;

    END testbench_arch;