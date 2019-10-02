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
        <signal name="X1" />
        <signal name="X0" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <signal name="PREMIO" />
        <signal name="FIN" />
        <signal name="X2" />
        <signal name="X3" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_7" />
        <signal name="BOLA" />
        <port polarity="Input" name="X1" />
        <port polarity="Input" name="X0" />
        <port polarity="Output" name="PREMIO" />
        <port polarity="Output" name="FIN" />
        <port polarity="Input" name="X2" />
        <port polarity="Input" name="X3" />
        <port polarity="Output" name="BOLA" />
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
        <blockdef name="m4_1e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="96" y1="-416" y2="-416" x1="0" />
            <line x2="96" y1="-352" y2="-352" x1="0" />
            <line x2="96" y1="-288" y2="-288" x1="0" />
            <line x2="96" y1="-224" y2="-224" x1="0" />
            <line x2="96" y1="-32" y2="-32" x1="0" />
            <line x2="256" y1="-320" y2="-320" x1="320" />
            <line x2="96" y1="-160" y2="-160" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="176" />
            <line x2="176" y1="-208" y2="-96" x1="176" />
            <line x2="96" y1="-32" y2="-32" x1="224" />
            <line x2="224" y1="-216" y2="-32" x1="224" />
            <line x2="96" y1="-224" y2="-192" x1="256" />
            <line x2="256" y1="-416" y2="-224" x1="256" />
            <line x2="256" y1="-448" y2="-416" x1="96" />
            <line x2="96" y1="-192" y2="-448" x1="96" />
            <line x2="96" y1="-160" y2="-160" x1="128" />
            <line x2="128" y1="-200" y2="-160" x1="128" />
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
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="XLXN_12" name="I0" />
            <blockpin signalname="X1" name="I1" />
            <blockpin signalname="XLXN_14" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="X0" name="I0" />
            <blockpin signalname="XLXN_11" name="I1" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="XLXN_12" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="X1" name="I0" />
            <blockpin signalname="X0" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_5">
            <blockpin signalname="XLXN_3" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="XLXN_18" name="O" />
        </block>
        <block symbolname="m4_1e" name="XLXI_7">
            <blockpin signalname="XLXN_13" name="D0" />
            <blockpin signalname="X0" name="D1" />
            <blockpin signalname="XLXN_14" name="D2" />
            <blockpin signalname="XLXN_14" name="D3" />
            <blockpin signalname="XLXN_27" name="E" />
            <blockpin signalname="X2" name="S0" />
            <blockpin signalname="X3" name="S1" />
            <blockpin signalname="PREMIO" name="O" />
        </block>
        <block symbolname="m4_1e" name="XLXI_8">
            <blockpin signalname="XLXN_18" name="D0" />
            <blockpin signalname="XLXN_14" name="D1" />
            <blockpin signalname="XLXN_16" name="D2" />
            <blockpin signalname="XLXN_18" name="D3" />
            <blockpin signalname="XLXN_28" name="E" />
            <blockpin signalname="X2" name="S0" />
            <blockpin signalname="X3" name="S1" />
            <blockpin signalname="FIN" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="X0" name="I" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_10">
            <blockpin signalname="X1" name="I" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="gnd" name="XLXI_14">
            <blockpin signalname="XLXN_13" name="G" />
        </block>
        <block symbolname="or2" name="XLXI_6">
            <blockpin signalname="FIN" name="I0" />
            <blockpin signalname="PREMIO" name="I1" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_17">
            <blockpin signalname="XLXN_27" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_18">
            <blockpin signalname="XLXN_28" name="P" />
        </block>
        <block symbolname="inv" name="XLXI_11">
            <blockpin signalname="XLXN_7" name="I" />
            <blockpin signalname="BOLA" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1024" y="880" name="XLXI_1" orien="R0" />
        <instance x="1024" y="1136" name="XLXI_2" orien="R0" />
        <instance x="880" y="1536" name="XLXI_3" orien="R0" />
        <instance x="880" y="1712" name="XLXI_4" orien="R0" />
        <instance x="1824" y="1728" name="XLXI_8" orien="R0" />
        <instance x="1200" y="1616" name="XLXI_5" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="1168" y1="1440" y2="1440" x1="1136" />
            <wire x2="1168" y1="1440" y2="1488" x1="1168" />
            <wire x2="1200" y1="1488" y2="1488" x1="1168" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1168" y1="1616" y2="1616" x1="1136" />
            <wire x2="1168" y1="1552" y2="1616" x1="1168" />
            <wire x2="1200" y1="1552" y2="1552" x1="1168" />
        </branch>
        <instance x="416" y="592" name="XLXI_10" orien="R90" />
        <instance x="576" y="592" name="XLXI_9" orien="R90" />
        <branch name="X1">
            <wire x2="400" y1="480" y2="576" x1="400" />
            <wire x2="448" y1="576" y2="576" x1="400" />
            <wire x2="448" y1="576" y2="592" x1="448" />
            <wire x2="400" y1="576" y2="832" x1="400" />
            <wire x2="400" y1="832" y2="1648" x1="400" />
            <wire x2="880" y1="1648" y2="1648" x1="400" />
            <wire x2="704" y1="832" y2="832" x1="400" />
            <wire x2="704" y1="752" y2="832" x1="704" />
            <wire x2="1024" y1="752" y2="752" x1="704" />
        </branch>
        <branch name="X0">
            <wire x2="544" y1="480" y2="560" x1="544" />
            <wire x2="608" y1="560" y2="560" x1="544" />
            <wire x2="608" y1="560" y2="592" x1="608" />
            <wire x2="544" y1="560" y2="912" x1="544" />
            <wire x2="544" y1="912" y2="1072" x1="544" />
            <wire x2="544" y1="1072" y2="1584" x1="544" />
            <wire x2="880" y1="1584" y2="1584" x1="544" />
            <wire x2="1024" y1="1072" y2="1072" x1="544" />
            <wire x2="1296" y1="912" y2="912" x1="544" />
            <wire x2="1296" y1="480" y2="912" x1="1296" />
            <wire x2="1856" y1="480" y2="480" x1="1296" />
        </branch>
        <iomarker fontsize="28" x="400" y="480" name="X1" orien="R270" />
        <iomarker fontsize="28" x="544" y="480" name="X0" orien="R270" />
        <branch name="XLXN_11">
            <wire x2="448" y1="816" y2="1008" x1="448" />
            <wire x2="448" y1="1008" y2="1472" x1="448" />
            <wire x2="880" y1="1472" y2="1472" x1="448" />
            <wire x2="1024" y1="1008" y2="1008" x1="448" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="608" y1="816" y2="864" x1="608" />
            <wire x2="608" y1="864" y2="1408" x1="608" />
            <wire x2="880" y1="1408" y2="1408" x1="608" />
            <wire x2="816" y1="864" y2="864" x1="608" />
            <wire x2="816" y1="816" y2="864" x1="816" />
            <wire x2="1024" y1="816" y2="816" x1="816" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="1840" y1="416" y2="416" x1="1824" />
            <wire x2="1856" y1="416" y2="416" x1="1840" />
        </branch>
        <instance x="1696" y="352" name="XLXI_14" orien="R90" />
        <branch name="XLXN_14">
            <wire x2="1568" y1="784" y2="784" x1="1280" />
            <wire x2="1568" y1="784" y2="1376" x1="1568" />
            <wire x2="1824" y1="1376" y2="1376" x1="1568" />
            <wire x2="1568" y1="544" y2="608" x1="1568" />
            <wire x2="1568" y1="608" y2="784" x1="1568" />
            <wire x2="1856" y1="608" y2="608" x1="1568" />
            <wire x2="1856" y1="544" y2="544" x1="1568" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="1552" y1="1040" y2="1040" x1="1280" />
            <wire x2="1552" y1="1040" y2="1440" x1="1552" />
            <wire x2="1824" y1="1440" y2="1440" x1="1552" />
        </branch>
        <branch name="XLXN_18">
            <wire x2="1536" y1="1520" y2="1520" x1="1456" />
            <wire x2="1824" y1="1312" y2="1312" x1="1536" />
            <wire x2="1536" y1="1312" y2="1504" x1="1536" />
            <wire x2="1536" y1="1504" y2="1520" x1="1536" />
            <wire x2="1824" y1="1504" y2="1504" x1="1536" />
        </branch>
        <branch name="X2">
            <wire x2="1632" y1="672" y2="1600" x1="1632" />
            <wire x2="1632" y1="1600" y2="1744" x1="1632" />
            <wire x2="1728" y1="1600" y2="1600" x1="1632" />
            <wire x2="1856" y1="672" y2="672" x1="1632" />
            <wire x2="1728" y1="1568" y2="1600" x1="1728" />
            <wire x2="1824" y1="1568" y2="1568" x1="1728" />
        </branch>
        <branch name="X3">
            <wire x2="1696" y1="736" y2="1632" x1="1696" />
            <wire x2="1696" y1="1632" y2="1744" x1="1696" />
            <wire x2="1824" y1="1632" y2="1632" x1="1696" />
            <wire x2="1856" y1="736" y2="736" x1="1696" />
        </branch>
        <iomarker fontsize="28" x="1632" y="1744" name="X2" orien="R90" />
        <iomarker fontsize="28" x="1696" y="1744" name="X3" orien="R90" />
        <branch name="XLXN_27">
            <wire x2="1856" y1="800" y2="816" x1="1856" />
            <wire x2="1856" y1="816" y2="832" x1="1856" />
        </branch>
        <instance x="1920" y="832" name="XLXI_17" orien="R180" />
        <branch name="XLXN_28">
            <wire x2="1824" y1="1696" y2="1728" x1="1824" />
        </branch>
        <instance x="1888" y="1728" name="XLXI_18" orien="R180" />
        <instance x="1856" y="832" name="XLXI_7" orien="R0" />
        <branch name="XLXN_7">
            <wire x2="2608" y1="1008" y2="1008" x1="2576" />
        </branch>
        <instance x="2608" y="1040" name="XLXI_11" orien="R0" />
        <branch name="BOLA">
            <wire x2="2864" y1="1008" y2="1008" x1="2832" />
        </branch>
        <instance x="2320" y="1104" name="XLXI_6" orien="R0" />
        <branch name="FIN">
            <wire x2="2160" y1="1408" y2="1408" x1="2144" />
            <wire x2="2512" y1="1408" y2="1408" x1="2160" />
            <wire x2="2320" y1="1040" y2="1040" x1="2160" />
            <wire x2="2160" y1="1040" y2="1408" x1="2160" />
        </branch>
        <branch name="PREMIO">
            <wire x2="2240" y1="512" y2="512" x1="2176" />
            <wire x2="2240" y1="512" y2="976" x1="2240" />
            <wire x2="2320" y1="976" y2="976" x1="2240" />
            <wire x2="2496" y1="512" y2="512" x1="2240" />
        </branch>
        <iomarker fontsize="28" x="2496" y="512" name="PREMIO" orien="R0" />
        <iomarker fontsize="28" x="2512" y="1408" name="FIN" orien="R0" />
        <iomarker fontsize="28" x="2864" y="1008" name="BOLA" orien="R0" />
    </sheet>
</drawing>