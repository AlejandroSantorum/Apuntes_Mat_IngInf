<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="Q3" />
        <signal name="CLR" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="XLXN_13" />
        <signal name="CLK" />
        <port polarity="Output" name="Q3" />
        <port polarity="Input" name="CLR" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q2" />
        <port polarity="Input" name="CLK" />
        <blockdef name="fdc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="fdc" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_4" name="CLR" />
            <blockpin signalname="XLXN_13" name="D" />
            <blockpin signalname="Q0" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_4" name="CLR" />
            <blockpin signalname="Q0" name="D" />
            <blockpin signalname="Q1" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_4" name="CLR" />
            <blockpin signalname="Q1" name="D" />
            <blockpin signalname="Q2" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_4" name="CLR" />
            <blockpin signalname="Q2" name="D" />
            <blockpin signalname="Q3" name="Q" />
        </block>
        <block symbolname="or2" name="XLXI_5">
            <blockpin signalname="Q3" name="I0" />
            <blockpin signalname="CLR" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="Q3" name="I" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="288" y="928" name="XLXI_1" orien="R0" />
        <instance x="816" y="928" name="XLXI_2" orien="R0" />
        <instance x="1312" y="928" name="XLXI_3" orien="R0" />
        <instance x="1824" y="928" name="XLXI_4" orien="R0" />
        <branch name="XLXN_4">
            <wire x2="288" y1="896" y2="912" x1="288" />
            <wire x2="816" y1="912" y2="912" x1="288" />
            <wire x2="1312" y1="912" y2="912" x1="816" />
            <wire x2="1824" y1="912" y2="912" x1="1312" />
            <wire x2="1824" y1="912" y2="992" x1="1824" />
            <wire x2="2272" y1="992" y2="992" x1="1824" />
            <wire x2="816" y1="896" y2="912" x1="816" />
            <wire x2="1312" y1="896" y2="912" x1="1312" />
            <wire x2="1824" y1="896" y2="912" x1="1824" />
            <wire x2="2272" y1="976" y2="992" x1="2272" />
        </branch>
        <instance x="2176" y="720" name="XLXI_5" orien="R90" />
        <branch name="Q3">
            <wire x2="2240" y1="464" y2="464" x1="1296" />
            <wire x2="2240" y1="464" y2="672" x1="2240" />
            <wire x2="2240" y1="672" y2="720" x1="2240" />
            <wire x2="2336" y1="464" y2="464" x1="2240" />
            <wire x2="2240" y1="672" y2="672" x1="2208" />
        </branch>
        <branch name="CLR">
            <wire x2="2304" y1="688" y2="720" x1="2304" />
        </branch>
        <iomarker fontsize="28" x="2304" y="688" name="CLR" orien="R270" />
        <branch name="Q0">
            <wire x2="720" y1="672" y2="672" x1="672" />
            <wire x2="816" y1="672" y2="672" x1="720" />
            <wire x2="720" y1="608" y2="672" x1="720" />
        </branch>
        <branch name="Q1">
            <wire x2="1232" y1="672" y2="672" x1="1200" />
            <wire x2="1312" y1="672" y2="672" x1="1232" />
            <wire x2="1232" y1="624" y2="672" x1="1232" />
        </branch>
        <branch name="Q2">
            <wire x2="1760" y1="672" y2="672" x1="1696" />
            <wire x2="1824" y1="672" y2="672" x1="1760" />
            <wire x2="1760" y1="624" y2="672" x1="1760" />
        </branch>
        <instance x="1296" y="432" name="XLXI_6" orien="R180" />
        <branch name="XLXN_13">
            <wire x2="240" y1="464" y2="672" x1="240" />
            <wire x2="288" y1="672" y2="672" x1="240" />
            <wire x2="1072" y1="464" y2="464" x1="240" />
        </branch>
        <branch name="CLK">
            <wire x2="208" y1="976" y2="976" x1="160" />
            <wire x2="736" y1="976" y2="976" x1="208" />
            <wire x2="1264" y1="976" y2="976" x1="736" />
            <wire x2="1776" y1="976" y2="976" x1="1264" />
            <wire x2="288" y1="800" y2="800" x1="208" />
            <wire x2="208" y1="800" y2="976" x1="208" />
            <wire x2="736" y1="800" y2="976" x1="736" />
            <wire x2="816" y1="800" y2="800" x1="736" />
            <wire x2="1264" y1="800" y2="976" x1="1264" />
            <wire x2="1312" y1="800" y2="800" x1="1264" />
            <wire x2="1776" y1="800" y2="976" x1="1776" />
            <wire x2="1824" y1="800" y2="800" x1="1776" />
        </branch>
        <iomarker fontsize="28" x="160" y="976" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="720" y="608" name="Q0" orien="R270" />
        <iomarker fontsize="28" x="1232" y="624" name="Q1" orien="R270" />
        <iomarker fontsize="28" x="1760" y="624" name="Q2" orien="R270" />
        <iomarker fontsize="28" x="2336" y="464" name="Q3" orien="R0" />
    </sheet>
</drawing>