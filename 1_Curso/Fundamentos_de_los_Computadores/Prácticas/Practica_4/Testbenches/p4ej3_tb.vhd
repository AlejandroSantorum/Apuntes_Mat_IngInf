---Design Name: p4ej2_tb
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

ENTITY p4ej3_tb IS
END p4ej3_tb;

ARCHITECTURE testbench_arch OF p4ej3_tb IS
    FILE RESULTS: TEXT OPEN WRITE_MODE IS "results.txt";

    COMPONENT p4ej3
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
        UUT : p4ej3
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
                -- -------------  Current Time:  785ns
                WAIT FOR 785 ns;
                RESET <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  1185ns
                WAIT FOR 400 ns;
                RESET <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  2985ns
                WAIT FOR 1800 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  3185ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  5585ns
                WAIT FOR 2400 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  5785ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  5985ns
                WAIT FOR 200 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  6185ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  8385ns
                WAIT FOR 2200 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  8585ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  9185ns
                WAIT FOR 600 ns;
                RESET <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  9585ns
                WAIT FOR 400 ns;
                RESET <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  11185ns
                WAIT FOR 1600 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  11385ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                -- -------------  Current Time:  13585ns
                WAIT FOR 2200 ns;
                MARCHA <= '1';
                -- -------------------------------------
                -- -------------  Current Time:  13785ns
                WAIT FOR 200 ns;
                MARCHA <= '0';
                -- -------------------------------------
                WAIT FOR 11415 ns;

            END PROCESS;

    END testbench_arch;

