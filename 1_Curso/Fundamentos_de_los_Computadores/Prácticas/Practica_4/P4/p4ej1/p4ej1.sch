<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="RESET" />
        <signal name="CLK" />
        <signal name="XLXN_10" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="MARCHA" />
        <signal name="XLXN_17" />
        <signal name="XLXN_26" />
        <signal name="XLXN_29" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_35" />
        <signal name="CALENTAR" />
        <signal name="READY" />
        <signal name="CAFE" />
        <signal name="XLXN_46" />
        <signal name="XLXN_47" />
        <signal name="XLXN_49" />
        <signal name="XLXN_50" />
        <signal name="XLXN_51" />
        <signal name="XLXN_54" />
        <port polarity="Input" name="RESET" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="MARCHA" />
        <port polarity="Output" name="CALENTAR" />
        <port polarity="Output" name="READY" />
        <port polarity="Output" name="CAFE" />
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
        <blockdef name="and3b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="and2b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
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
        <blockdef name="and2b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
        </blockdef>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_10" name="D" />
            <blockpin signalname="XLXN_17" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_5">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_26" name="D" />
            <blockpin signalname="XLXN_31" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_6">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_32" name="D" />
            <blockpin signalname="XLXN_35" name="Q" />
        </block>
        <block symbolname="and2" name="XLXI_8">
            <blockpin signalname="XLXN_17" name="I0" />
            <blockpin signalname="XLXN_31" name="I1" />
            <blockpin signalname="XLXN_46" name="O" />
        </block>
        <block symbolname="and3b2" name="XLXI_10">
            <blockpin signalname="XLXN_35" name="I0" />
            <blockpin signalname="XLXN_31" name="I1" />
            <blockpin signalname="XLXN_17" name="I2" />
            <blockpin signalname="XLXN_29" name="O" />
        </block>
        <block symbolname="and2b2" name="XLXI_11">
            <blockpin signalname="XLXN_35" name="I0" />
            <blockpin signalname="XLXN_17" name="I1" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_12">
            <blockpin signalname="XLXN_13" name="I0" />
            <blockpin signalname="XLXN_12" name="I1" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_13">
            <blockpin signalname="XLXN_29" name="I0" />
            <blockpin signalname="XLXN_47" name="I1" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_14">
            <blockpin signalname="XLXN_46" name="I0" />
            <blockpin signalname="XLXN_35" name="I1" />
            <blockpin signalname="XLXN_32" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_15">
            <blockpin signalname="MARCHA" name="I0" />
            <blockpin signalname="XLXN_35" name="I1" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_16">
            <blockpin signalname="XLXN_54" name="I0" />
            <blockpin signalname="XLXN_31" name="I1" />
            <blockpin signalname="CALENTAR" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_17">
            <blockpin signalname="XLXN_17" name="I0" />
            <blockpin signalname="XLXN_35" name="I1" />
            <blockpin signalname="CAFE" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_18">
            <blockpin signalname="XLXN_17" name="I0" />
            <blockpin signalname="XLXN_35" name="I1" />
            <blockpin signalname="READY" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_19">
            <blockpin signalname="XLXN_35" name="I0" />
            <blockpin signalname="XLXN_17" name="I1" />
            <blockpin signalname="XLXN_54" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_20">
            <blockpin signalname="XLXN_17" name="I0" />
            <blockpin signalname="XLXN_31" name="I1" />
            <blockpin signalname="XLXN_47" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="784" y="1008" name="XLXI_4" orien="R0" />
        <branch name="RESET">
            <wire x2="784" y1="1024" y2="1024" x1="496" />
            <wire x2="1472" y1="1024" y2="1024" x1="784" />
            <wire x2="2480" y1="1024" y2="1024" x1="1472" />
            <wire x2="784" y1="976" y2="1024" x1="784" />
            <wire x2="1568" y1="976" y2="976" x1="1472" />
            <wire x2="1472" y1="976" y2="1024" x1="1472" />
            <wire x2="2480" y1="976" y2="1024" x1="2480" />
        </branch>
        <branch name="CLK">
            <wire x2="640" y1="1088" y2="1088" x1="496" />
            <wire x2="1440" y1="1088" y2="1088" x1="640" />
            <wire x2="2448" y1="1088" y2="1088" x1="1440" />
            <wire x2="640" y1="880" y2="1088" x1="640" />
            <wire x2="784" y1="880" y2="880" x1="640" />
            <wire x2="1568" y1="880" y2="880" x1="1440" />
            <wire x2="1440" y1="880" y2="1088" x1="1440" />
            <wire x2="2480" y1="880" y2="880" x1="2448" />
            <wire x2="2448" y1="880" y2="1088" x1="2448" />
        </branch>
        <iomarker fontsize="28" x="496" y="1024" name="RESET" orien="R180" />
        <iomarker fontsize="28" x="496" y="1088" name="CLK" orien="R180" />
        <branch name="XLXN_10">
            <wire x2="784" y1="752" y2="752" x1="752" />
        </branch>
        <instance x="496" y="848" name="XLXI_12" orien="R0" />
        <branch name="XLXN_12">
            <wire x2="496" y1="720" y2="720" x1="464" />
        </branch>
        <instance x="208" y="816" name="XLXI_15" orien="R0" />
        <instance x="192" y="960" name="XLXI_11" orien="R0" />
        <branch name="XLXN_13">
            <wire x2="464" y1="864" y2="864" x1="448" />
            <wire x2="464" y1="784" y2="864" x1="464" />
            <wire x2="496" y1="784" y2="784" x1="464" />
        </branch>
        <branch name="MARCHA">
            <wire x2="208" y1="752" y2="752" x1="192" />
        </branch>
        <iomarker fontsize="28" x="192" y="752" name="MARCHA" orien="R180" />
        <branch name="XLXN_17">
            <wire x2="16" y1="512" y2="832" x1="16" />
            <wire x2="192" y1="832" y2="832" x1="16" />
            <wire x2="1184" y1="512" y2="512" x1="16" />
            <wire x2="1184" y1="512" y2="752" x1="1184" />
            <wire x2="1184" y1="752" y2="1344" x1="1184" />
            <wire x2="1440" y1="1344" y2="1344" x1="1184" />
            <wire x2="1184" y1="1344" y2="1648" x1="1184" />
            <wire x2="1712" y1="1648" y2="1648" x1="1184" />
            <wire x2="1184" y1="1648" y2="1872" x1="1184" />
            <wire x2="1712" y1="1872" y2="1872" x1="1184" />
            <wire x2="1312" y1="512" y2="512" x1="1184" />
            <wire x2="1184" y1="752" y2="752" x1="1168" />
            <wire x2="1312" y1="208" y2="208" x1="1296" />
            <wire x2="1312" y1="208" y2="512" x1="1312" />
            <wire x2="1424" y1="208" y2="208" x1="1312" />
            <wire x2="1680" y1="208" y2="208" x1="1424" />
            <wire x2="1680" y1="208" y2="240" x1="1680" />
            <wire x2="1424" y1="208" y2="304" x1="1424" />
            <wire x2="1296" y1="208" y2="224" x1="1296" />
        </branch>
        <instance x="2480" y="1008" name="XLXI_6" orien="R0" />
        <instance x="1568" y="1008" name="XLXI_5" orien="R0" />
        <branch name="XLXN_26">
            <wire x2="1568" y1="752" y2="752" x1="1536" />
        </branch>
        <instance x="1280" y="848" name="XLXI_13" orien="R0" />
        <instance x="1104" y="224" name="XLXI_10" orien="R90" />
        <branch name="XLXN_29">
            <wire x2="1232" y1="480" y2="784" x1="1232" />
            <wire x2="1280" y1="784" y2="784" x1="1232" />
        </branch>
        <branch name="XLXN_32">
            <wire x2="2480" y1="752" y2="752" x1="2448" />
        </branch>
        <instance x="2192" y="848" name="XLXI_14" orien="R0" />
        <instance x="1712" y="1712" name="XLXI_18" orien="R0" />
        <instance x="1712" y="1936" name="XLXI_17" orien="R0" />
        <instance x="1440" y="1472" name="XLXI_19" orien="R0" />
        <branch name="XLXN_35">
            <wire x2="144" y1="592" y2="688" x1="144" />
            <wire x2="208" y1="688" y2="688" x1="144" />
            <wire x2="2192" y1="592" y2="592" x1="144" />
            <wire x2="2960" y1="592" y2="592" x1="2192" />
            <wire x2="2960" y1="592" y2="752" x1="2960" />
            <wire x2="2960" y1="752" y2="1184" x1="2960" />
            <wire x2="2192" y1="592" y2="720" x1="2192" />
            <wire x2="192" y1="896" y2="896" x1="144" />
            <wire x2="144" y1="896" y2="1184" x1="144" />
            <wire x2="1296" y1="1184" y2="1184" x1="144" />
            <wire x2="2960" y1="1184" y2="1184" x1="1296" />
            <wire x2="1296" y1="1184" y2="1408" x1="1296" />
            <wire x2="1440" y1="1408" y2="1408" x1="1296" />
            <wire x2="1296" y1="1408" y2="1584" x1="1296" />
            <wire x2="1712" y1="1584" y2="1584" x1="1296" />
            <wire x2="1296" y1="1584" y2="1808" x1="1296" />
            <wire x2="1712" y1="1808" y2="1808" x1="1296" />
            <wire x2="1168" y1="176" y2="224" x1="1168" />
            <wire x2="2960" y1="176" y2="176" x1="1168" />
            <wire x2="2960" y1="176" y2="592" x1="2960" />
            <wire x2="2960" y1="752" y2="752" x1="2864" />
        </branch>
        <branch name="CALENTAR">
            <wire x2="2128" y1="1408" y2="1408" x1="2080" />
        </branch>
        <branch name="READY">
            <wire x2="2000" y1="1616" y2="1616" x1="1968" />
        </branch>
        <iomarker fontsize="28" x="2000" y="1616" name="READY" orien="R0" />
        <branch name="CAFE">
            <wire x2="2000" y1="1840" y2="1840" x1="1968" />
        </branch>
        <iomarker fontsize="28" x="2000" y="1840" name="CAFE" orien="R0" />
        <instance x="1616" y="240" name="XLXI_8" orien="R90" />
        <branch name="XLXN_46">
            <wire x2="1712" y1="496" y2="528" x1="1712" />
            <wire x2="2112" y1="528" y2="528" x1="1712" />
            <wire x2="2112" y1="528" y2="784" x1="2112" />
            <wire x2="2192" y1="784" y2="784" x1="2112" />
        </branch>
        <instance x="1360" y="304" name="XLXI_20" orien="R90" />
        <branch name="XLXN_47">
            <wire x2="1456" y1="640" y2="640" x1="1264" />
            <wire x2="1264" y1="640" y2="720" x1="1264" />
            <wire x2="1280" y1="720" y2="720" x1="1264" />
            <wire x2="1456" y1="560" y2="640" x1="1456" />
        </branch>
        <iomarker fontsize="28" x="2128" y="1408" name="CALENTAR" orien="R0" />
        <instance x="1824" y="1504" name="XLXI_16" orien="R0" />
        <branch name="XLXN_31">
            <wire x2="1232" y1="144" y2="224" x1="1232" />
            <wire x2="1488" y1="144" y2="144" x1="1232" />
            <wire x2="1488" y1="144" y2="304" x1="1488" />
            <wire x2="1744" y1="144" y2="144" x1="1488" />
            <wire x2="1744" y1="144" y2="240" x1="1744" />
            <wire x2="2016" y1="144" y2="144" x1="1744" />
            <wire x2="2016" y1="144" y2="752" x1="2016" />
            <wire x2="2016" y1="752" y2="1264" x1="2016" />
            <wire x2="2016" y1="1264" y2="1264" x1="1824" />
            <wire x2="1824" y1="1264" y2="1376" x1="1824" />
            <wire x2="2016" y1="752" y2="752" x1="1952" />
        </branch>
        <branch name="XLXN_54">
            <wire x2="1728" y1="1376" y2="1376" x1="1696" />
            <wire x2="1728" y1="1376" y2="1440" x1="1728" />
            <wire x2="1824" y1="1440" y2="1440" x1="1728" />
        </branch>
    </sheet>
</drawing>