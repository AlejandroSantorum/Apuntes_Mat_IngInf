<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="INIT" />
        <signal name="XLXN_25" />
        <signal name="CLK" />
        <signal name="Q3" />
        <signal name="Q2" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="XLXN_21" />
        <port polarity="Input" name="INIT" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="Q3" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q1" />
        <blockdef name="cb4cled">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-704" height="640" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-640" y2="-640" x1="384" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-640" y2="-640" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <block symbolname="cb4cled" name="XLXI_7">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_22" name="CE" />
            <blockpin signalname="XLXN_21" name="CLR" />
            <blockpin signalname="XLXN_21" name="D0" />
            <blockpin signalname="XLXN_21" name="D1" />
            <blockpin signalname="XLXN_22" name="D2" />
            <blockpin signalname="XLXN_21" name="D3" />
            <blockpin signalname="XLXN_23" name="L" />
            <blockpin signalname="XLXN_22" name="UP" />
            <blockpin name="CEO" />
            <blockpin signalname="Q0" name="Q0" />
            <blockpin signalname="Q1" name="Q1" />
            <blockpin signalname="Q2" name="Q2" />
            <blockpin signalname="Q3" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="vcc" name="XLXI_8">
            <blockpin signalname="XLXN_22" name="P" />
        </block>
        <block symbolname="or2" name="XLXI_10">
            <blockpin signalname="XLXN_25" name="I0" />
            <blockpin signalname="INIT" name="I1" />
            <blockpin signalname="XLXN_23" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_32">
            <blockpin signalname="Q3" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="Q0" name="I2" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="gnd" name="XLXI_9">
            <blockpin signalname="XLXN_21" name="G" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1312" y="1328" name="XLXI_7" orien="R0" />
        <instance x="1072" y="880" name="XLXI_8" orien="R270" />
        <branch name="XLXN_22">
            <wire x2="1120" y1="816" y2="816" x1="1072" />
            <wire x2="1136" y1="816" y2="816" x1="1120" />
            <wire x2="1312" y1="816" y2="816" x1="1136" />
            <wire x2="1120" y1="816" y2="1008" x1="1120" />
            <wire x2="1120" y1="1008" y2="1136" x1="1120" />
            <wire x2="1312" y1="1136" y2="1136" x1="1120" />
            <wire x2="1312" y1="1008" y2="1008" x1="1120" />
        </branch>
        <instance x="800" y="1168" name="XLXI_10" orien="R0" />
        <branch name="XLXN_23">
            <wire x2="1312" y1="1072" y2="1072" x1="1056" />
        </branch>
        <branch name="INIT">
            <wire x2="656" y1="768" y2="1040" x1="656" />
            <wire x2="800" y1="1040" y2="1040" x1="656" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="800" y1="1104" y2="1104" x1="752" />
            <wire x2="752" y1="1104" y2="1376" x1="752" />
            <wire x2="1984" y1="1376" y2="1376" x1="752" />
            <wire x2="1984" y1="1232" y2="1376" x1="1984" />
        </branch>
        <branch name="CLK">
            <wire x2="1312" y1="1200" y2="1200" x1="624" />
        </branch>
        <instance x="1856" y="976" name="XLXI_32" orien="R90" />
        <branch name="Q3">
            <wire x2="1920" y1="880" y2="880" x1="1696" />
            <wire x2="1920" y1="880" y2="976" x1="1920" />
            <wire x2="2160" y1="880" y2="880" x1="1920" />
        </branch>
        <branch name="Q2">
            <wire x2="1984" y1="816" y2="816" x1="1696" />
            <wire x2="1984" y1="816" y2="976" x1="1984" />
            <wire x2="2160" y1="816" y2="816" x1="1984" />
        </branch>
        <branch name="Q0">
            <wire x2="2048" y1="688" y2="688" x1="1696" />
            <wire x2="2048" y1="688" y2="976" x1="2048" />
            <wire x2="2160" y1="688" y2="688" x1="2048" />
        </branch>
        <branch name="Q1">
            <wire x2="2160" y1="752" y2="752" x1="1696" />
        </branch>
        <instance x="944" y="560" name="XLXI_9" orien="R180" />
        <branch name="XLXN_21">
            <wire x2="880" y1="688" y2="768" x1="880" />
            <wire x2="928" y1="768" y2="768" x1="880" />
            <wire x2="928" y1="688" y2="768" x1="928" />
            <wire x2="1216" y1="688" y2="688" x1="928" />
            <wire x2="1312" y1="688" y2="688" x1="1216" />
            <wire x2="1216" y1="688" y2="752" x1="1216" />
            <wire x2="1312" y1="752" y2="752" x1="1216" />
            <wire x2="1216" y1="752" y2="880" x1="1216" />
            <wire x2="1312" y1="880" y2="880" x1="1216" />
            <wire x2="1216" y1="880" y2="1296" x1="1216" />
            <wire x2="1312" y1="1296" y2="1296" x1="1216" />
        </branch>
        <iomarker fontsize="28" x="656" y="768" name="INIT" orien="R270" />
        <iomarker fontsize="28" x="624" y="1200" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="2160" y="688" name="Q0" orien="R0" />
        <iomarker fontsize="28" x="2160" y="752" name="Q1" orien="R0" />
        <iomarker fontsize="28" x="2160" y="816" name="Q2" orien="R0" />
        <iomarker fontsize="28" x="2160" y="880" name="Q3" orien="R0" />
    </sheet>
</drawing>