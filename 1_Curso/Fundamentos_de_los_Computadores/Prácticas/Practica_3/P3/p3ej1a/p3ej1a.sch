<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CLR" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="CLK" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="XLXN_8" />
        <signal name="Q3" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q3" />
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
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_8" name="D" />
            <blockpin signalname="Q0" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q0" name="D" />
            <blockpin signalname="Q1" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q1" name="D" />
            <blockpin signalname="Q2" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="Q2" name="D" />
            <blockpin signalname="Q3" name="Q" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="Q3" name="I" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="496" y="928" name="XLXI_1" orien="R0" />
        <instance x="1232" y="928" name="XLXI_2" orien="R0" />
        <instance x="1792" y="928" name="XLXI_3" orien="R0" />
        <instance x="2512" y="928" name="XLXI_4" orien="R0" />
        <branch name="CLR">
            <wire x2="496" y1="912" y2="912" x1="352" />
            <wire x2="1232" y1="912" y2="912" x1="496" />
            <wire x2="1792" y1="912" y2="912" x1="1232" />
            <wire x2="2512" y1="912" y2="912" x1="1792" />
            <wire x2="496" y1="896" y2="912" x1="496" />
            <wire x2="1232" y1="896" y2="912" x1="1232" />
            <wire x2="1792" y1="896" y2="912" x1="1792" />
            <wire x2="2512" y1="896" y2="912" x1="2512" />
        </branch>
        <iomarker fontsize="28" x="352" y="912" name="CLR" orien="R180" />
        <branch name="CLK">
            <wire x2="432" y1="976" y2="976" x1="352" />
            <wire x2="944" y1="976" y2="976" x1="432" />
            <wire x2="1680" y1="976" y2="976" x1="944" />
            <wire x2="2192" y1="976" y2="976" x1="1680" />
            <wire x2="496" y1="800" y2="800" x1="432" />
            <wire x2="432" y1="800" y2="976" x1="432" />
            <wire x2="944" y1="800" y2="976" x1="944" />
            <wire x2="1232" y1="800" y2="800" x1="944" />
            <wire x2="1680" y1="800" y2="976" x1="1680" />
            <wire x2="1792" y1="800" y2="800" x1="1680" />
            <wire x2="2192" y1="800" y2="976" x1="2192" />
            <wire x2="2512" y1="800" y2="800" x1="2192" />
        </branch>
        <iomarker fontsize="28" x="352" y="976" name="CLK" orien="R180" />
        <branch name="Q0">
            <wire x2="1040" y1="672" y2="672" x1="880" />
            <wire x2="1232" y1="672" y2="672" x1="1040" />
            <wire x2="1040" y1="608" y2="672" x1="1040" />
        </branch>
        <branch name="Q1">
            <wire x2="1696" y1="672" y2="672" x1="1616" />
            <wire x2="1792" y1="672" y2="672" x1="1696" />
            <wire x2="1696" y1="608" y2="672" x1="1696" />
        </branch>
        <branch name="Q2">
            <wire x2="2304" y1="672" y2="672" x1="2176" />
            <wire x2="2512" y1="672" y2="672" x1="2304" />
            <wire x2="2304" y1="608" y2="672" x1="2304" />
        </branch>
        <instance x="1504" y="400" name="XLXI_5" orien="R180" />
        <branch name="XLXN_8">
            <wire x2="416" y1="432" y2="672" x1="416" />
            <wire x2="496" y1="672" y2="672" x1="416" />
            <wire x2="1280" y1="432" y2="432" x1="416" />
        </branch>
        <branch name="Q3">
            <wire x2="2960" y1="432" y2="432" x1="1504" />
            <wire x2="2960" y1="432" y2="672" x1="2960" />
            <wire x2="3024" y1="672" y2="672" x1="2960" />
            <wire x2="2960" y1="672" y2="672" x1="2896" />
        </branch>
        <iomarker fontsize="28" x="1040" y="608" name="Q0" orien="R270" />
        <iomarker fontsize="28" x="1696" y="608" name="Q1" orien="R270" />
        <iomarker fontsize="28" x="2304" y="608" name="Q2" orien="R270" />
        <iomarker fontsize="28" x="3024" y="672" name="Q3" orien="R0" />
    </sheet>
</drawing>