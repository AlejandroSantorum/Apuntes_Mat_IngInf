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
        <signal name="XLXN_4" />
        <signal name="D" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="C" />
        <signal name="XLXN_10" />
        <signal name="B" />
        <signal name="XLXN_12" />
        <signal name="A" />
        <signal name="Z" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="A" />
        <port polarity="Output" name="Z" />
        <blockdef name="nand4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="216" y1="-160" y2="-160" x1="256" />
            <circle r="12" cx="204" cy="-160" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="64" y1="-112" y2="-112" x1="144" />
        </blockdef>
        <blockdef name="nand3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="216" y1="-128" y2="-128" x1="256" />
            <circle r="12" cx="204" cy="-128" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <blockdef name="nand2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
        </blockdef>
        <block symbolname="nand4" name="XLXI_1">
            <blockpin signalname="XLXN_26" name="I0" />
            <blockpin signalname="XLXN_25" name="I1" />
            <blockpin signalname="XLXN_24" name="I2" />
            <blockpin signalname="XLXN_23" name="I3" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="nand4" name="XLXI_2">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="XLXN_2" name="I2" />
            <blockpin signalname="XLXN_1" name="I3" />
            <blockpin signalname="XLXN_23" name="O" />
        </block>
        <block symbolname="nand3" name="XLXI_3">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_1" name="I2" />
            <blockpin signalname="XLXN_24" name="O" />
        </block>
        <block symbolname="nand3" name="XLXI_4">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="nand3" name="XLXI_5">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_6">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_7">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_8">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_10">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="2400" y="1568" name="XLXI_1" orien="R0" />
        <instance x="1664" y="1216" name="XLXI_2" orien="R0" />
        <instance x="1664" y="1520" name="XLXI_3" orien="R0" />
        <instance x="1680" y="1824" name="XLXI_4" orien="R0" />
        <instance x="1664" y="2176" name="XLXI_5" orien="R0" />
        <instance x="688" y="656" name="XLXI_6" orien="M90" />
        <instance x="672" y="672" name="XLXI_7" orien="R90" />
        <instance x="848" y="672" name="XLXI_8" orien="R90" />
        <instance x="1008" y="672" name="XLXI_10" orien="R90" />
        <branch name="XLXN_1">
            <wire x2="592" y1="912" y2="960" x1="592" />
            <wire x2="1664" y1="960" y2="960" x1="592" />
            <wire x2="592" y1="960" y2="1328" x1="592" />
            <wire x2="1664" y1="1328" y2="1328" x1="592" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="768" y1="928" y2="1024" x1="768" />
            <wire x2="1664" y1="1024" y2="1024" x1="768" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="944" y1="928" y2="1088" x1="944" />
            <wire x2="1664" y1="1088" y2="1088" x1="944" />
            <wire x2="944" y1="1088" y2="2048" x1="944" />
            <wire x2="1664" y1="2048" y2="2048" x1="944" />
        </branch>
        <branch name="D">
            <wire x2="1072" y1="656" y2="672" x1="1072" />
            <wire x2="1104" y1="656" y2="656" x1="1072" />
            <wire x2="1136" y1="656" y2="656" x1="1104" />
            <wire x2="1136" y1="656" y2="672" x1="1136" />
            <wire x2="1200" y1="576" y2="576" x1="1104" />
            <wire x2="1200" y1="576" y2="1152" x1="1200" />
            <wire x2="1664" y1="1152" y2="1152" x1="1200" />
            <wire x2="1104" y1="576" y2="656" x1="1104" />
            <wire x2="1200" y1="448" y2="576" x1="1200" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1104" y1="928" y2="1456" x1="1104" />
            <wire x2="1664" y1="1456" y2="1456" x1="1104" />
            <wire x2="1104" y1="1456" y2="1760" x1="1104" />
            <wire x2="1680" y1="1760" y2="1760" x1="1104" />
            <wire x2="1104" y1="1760" y2="2112" x1="1104" />
            <wire x2="1664" y1="2112" y2="2112" x1="1104" />
        </branch>
        <branch name="C">
            <wire x2="912" y1="656" y2="672" x1="912" />
            <wire x2="944" y1="656" y2="656" x1="912" />
            <wire x2="976" y1="656" y2="656" x1="944" />
            <wire x2="976" y1="656" y2="672" x1="976" />
            <wire x2="1008" y1="592" y2="592" x1="944" />
            <wire x2="1008" y1="592" y2="1392" x1="1008" />
            <wire x2="1664" y1="1392" y2="1392" x1="1008" />
            <wire x2="944" y1="592" y2="656" x1="944" />
            <wire x2="1008" y1="448" y2="560" x1="1008" />
            <wire x2="1008" y1="560" y2="592" x1="1008" />
        </branch>
        <branch name="B">
            <wire x2="736" y1="656" y2="672" x1="736" />
            <wire x2="768" y1="656" y2="656" x1="736" />
            <wire x2="800" y1="656" y2="656" x1="768" />
            <wire x2="800" y1="656" y2="672" x1="800" />
            <wire x2="848" y1="560" y2="560" x1="768" />
            <wire x2="848" y1="560" y2="576" x1="848" />
            <wire x2="848" y1="576" y2="1696" x1="848" />
            <wire x2="1680" y1="1696" y2="1696" x1="848" />
            <wire x2="768" y1="560" y2="656" x1="768" />
            <wire x2="848" y1="448" y2="560" x1="848" />
        </branch>
        <branch name="A">
            <wire x2="464" y1="432" y2="560" x1="464" />
            <wire x2="464" y1="560" y2="576" x1="464" />
            <wire x2="464" y1="576" y2="1632" x1="464" />
            <wire x2="1680" y1="1632" y2="1632" x1="464" />
            <wire x2="464" y1="1632" y2="1984" x1="464" />
            <wire x2="1664" y1="1984" y2="1984" x1="464" />
            <wire x2="592" y1="576" y2="576" x1="464" />
            <wire x2="592" y1="576" y2="640" x1="592" />
            <wire x2="624" y1="640" y2="640" x1="592" />
            <wire x2="624" y1="640" y2="656" x1="624" />
            <wire x2="560" y1="640" y2="656" x1="560" />
            <wire x2="592" y1="640" y2="640" x1="560" />
        </branch>
        <branch name="Z">
            <wire x2="2688" y1="1408" y2="1408" x1="2656" />
        </branch>
        <branch name="XLXN_23">
            <wire x2="2400" y1="1056" y2="1056" x1="1920" />
            <wire x2="2400" y1="1056" y2="1312" x1="2400" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="2160" y1="1392" y2="1392" x1="1920" />
            <wire x2="2160" y1="1376" y2="1392" x1="2160" />
            <wire x2="2400" y1="1376" y2="1376" x1="2160" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="2160" y1="1696" y2="1696" x1="1936" />
            <wire x2="2160" y1="1440" y2="1696" x1="2160" />
            <wire x2="2400" y1="1440" y2="1440" x1="2160" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="2400" y1="2048" y2="2048" x1="1920" />
            <wire x2="2400" y1="1504" y2="2048" x1="2400" />
        </branch>
        <iomarker fontsize="28" x="464" y="432" name="A" orien="R270" />
        <iomarker fontsize="28" x="848" y="448" name="B" orien="R270" />
        <iomarker fontsize="28" x="1008" y="448" name="C" orien="R270" />
        <iomarker fontsize="28" x="1200" y="448" name="D" orien="R270" />
        <iomarker fontsize="28" x="2688" y="1408" name="Z" orien="R0" />
    </sheet>
</drawing>