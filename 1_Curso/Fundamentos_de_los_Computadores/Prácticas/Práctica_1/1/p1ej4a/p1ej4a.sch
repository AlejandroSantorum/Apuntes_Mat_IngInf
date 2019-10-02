<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="Cout" />
        <signal name="S" />
        <signal name="XLXN_6" />
        <signal name="Cin" />
        <signal name="A" />
        <signal name="XLXN_9" />
        <signal name="B" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <port polarity="Output" name="Cout" />
        <port polarity="Output" name="S" />
        <port polarity="Input" name="Cin" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <blockdef name="xor3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="208" y1="-128" y2="-128" x1="256" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <arc ex="64" ey="-176" sx="64" sy="-80" r="56" cx="32" cy="-128" />
            <arc ex="128" ey="-176" sx="208" sy="-128" r="88" cx="132" cy="-88" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="64" y1="-80" y2="-80" x1="128" />
            <line x2="64" y1="-176" y2="-176" x1="128" />
            <arc ex="208" ey="-128" sx="128" sy="-80" r="88" cx="132" cy="-168" />
        </blockdef>
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <block symbolname="xor3" name="XLXI_1">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="Cin" name="I2" />
            <blockpin signalname="S" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_2">
            <blockpin signalname="XLXN_3" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="XLXN_1" name="I2" />
            <blockpin signalname="Cout" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="Cin" name="I1" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="Cin" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_5">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1616" y="848" name="XLXI_1" orien="R0" />
        <instance x="1600" y="1280" name="XLXI_2" orien="R0" />
        <instance x="1056" y="1072" name="XLXI_3" orien="R0" />
        <instance x="1056" y="1264" name="XLXI_4" orien="R0" />
        <instance x="1056" y="1456" name="XLXI_5" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1600" y1="976" y2="976" x1="1312" />
            <wire x2="1600" y1="976" y2="1088" x1="1600" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1456" y1="1168" y2="1168" x1="1312" />
            <wire x2="1456" y1="1152" y2="1168" x1="1456" />
            <wire x2="1600" y1="1152" y2="1152" x1="1456" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1600" y1="1360" y2="1360" x1="1312" />
            <wire x2="1600" y1="1216" y2="1360" x1="1600" />
        </branch>
        <branch name="Cout">
            <wire x2="1952" y1="1152" y2="1152" x1="1856" />
        </branch>
        <branch name="S">
            <wire x2="1984" y1="720" y2="720" x1="1872" />
        </branch>
        <branch name="Cin">
            <wire x2="272" y1="352" y2="592" x1="272" />
            <wire x2="1616" y1="592" y2="592" x1="272" />
            <wire x2="1616" y1="592" y2="656" x1="1616" />
            <wire x2="272" y1="592" y2="944" x1="272" />
            <wire x2="1056" y1="944" y2="944" x1="272" />
            <wire x2="272" y1="944" y2="1136" x1="272" />
            <wire x2="1056" y1="1136" y2="1136" x1="272" />
        </branch>
        <branch name="A">
            <wire x2="400" y1="352" y2="704" x1="400" />
            <wire x2="400" y1="704" y2="720" x1="400" />
            <wire x2="1616" y1="720" y2="720" x1="400" />
            <wire x2="400" y1="720" y2="1008" x1="400" />
            <wire x2="1056" y1="1008" y2="1008" x1="400" />
            <wire x2="400" y1="1008" y2="1328" x1="400" />
            <wire x2="1056" y1="1328" y2="1328" x1="400" />
        </branch>
        <branch name="B">
            <wire x2="544" y1="352" y2="784" x1="544" />
            <wire x2="1616" y1="784" y2="784" x1="544" />
            <wire x2="544" y1="784" y2="1200" x1="544" />
            <wire x2="1056" y1="1200" y2="1200" x1="544" />
            <wire x2="544" y1="1200" y2="1392" x1="544" />
            <wire x2="1056" y1="1392" y2="1392" x1="544" />
        </branch>
        <iomarker fontsize="28" x="272" y="352" name="Cin" orien="R270" />
        <iomarker fontsize="28" x="400" y="352" name="A" orien="R270" />
        <iomarker fontsize="28" x="544" y="352" name="B" orien="R270" />
        <iomarker fontsize="28" x="1984" y="720" name="S" orien="R0" />
        <iomarker fontsize="28" x="1952" y="1152" name="Cout" orien="R0" />
    </sheet>
</drawing>