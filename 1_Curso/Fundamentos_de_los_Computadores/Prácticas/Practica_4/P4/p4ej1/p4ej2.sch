<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="MARCHA" />
        <signal name="RESET" />
        <signal name="CLK" />
        <signal name="CAFE" />
        <signal name="READY" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="CALENTAR" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_17" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="XLXN_24" />
        <signal name="XLXN_27" />
        <signal name="XLXN_29" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_36" />
        <port polarity="Input" name="MARCHA" />
        <port polarity="Input" name="RESET" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="CAFE" />
        <port polarity="Output" name="READY" />
        <port polarity="Output" name="CALENTAR" />
        <blockdef name="p4ej1">
            <timestamp>2016-11-30T11:30:44</timestamp>
            <rect width="256" x="64" y="-192" height="192" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
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
        <block symbolname="p4ej1" name="XLXI_1">
            <blockpin signalname="CAFE" name="CAFE" />
            <blockpin signalname="CALENTAR" name="CALENTAR" />
            <blockpin signalname="CLK" name="CLK" />
            <blockpin signalname="XLXN_1" name="MARCHA" />
            <blockpin signalname="READY" name="READY" />
            <blockpin signalname="RESET" name="RESET" />
        </block>
        <block symbolname="or2" name="XLXI_2">
            <blockpin signalname="XLXN_24" name="I0" />
            <blockpin signalname="MARCHA" name="I1" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="cb4cled" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CAFE" name="CE" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_32" name="D0" />
            <blockpin signalname="XLXN_33" name="D1" />
            <blockpin signalname="XLXN_33" name="D2" />
            <blockpin signalname="XLXN_32" name="D3" />
            <blockpin signalname="XLXN_7" name="L" />
            <blockpin signalname="XLXN_32" name="UP" />
            <blockpin name="CEO" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin signalname="XLXN_24" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="READY" name="I0" />
            <blockpin signalname="MARCHA" name="I1" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="gnd" name="XLXI_6">
            <blockpin signalname="XLXN_33" name="G" />
        </block>
        <block symbolname="vcc" name="XLXI_12">
            <blockpin signalname="XLXN_32" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="976" y="896" name="XLXI_1" orien="R0">
        </instance>
        <instance x="608" y="832" name="XLXI_2" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="976" y1="736" y2="736" x1="864" />
        </branch>
        <branch name="MARCHA">
            <wire x2="512" y1="320" y2="480" x1="512" />
            <wire x2="512" y1="480" y2="704" x1="512" />
            <wire x2="608" y1="704" y2="704" x1="512" />
            <wire x2="1440" y1="480" y2="480" x1="512" />
            <wire x2="1440" y1="480" y2="720" x1="1440" />
            <wire x2="1568" y1="720" y2="720" x1="1440" />
        </branch>
        <branch name="RESET">
            <wire x2="912" y1="320" y2="800" x1="912" />
            <wire x2="976" y1="800" y2="800" x1="912" />
            <wire x2="912" y1="800" y2="1104" x1="912" />
            <wire x2="2048" y1="1104" y2="1104" x1="912" />
        </branch>
        <branch name="CLK">
            <wire x2="496" y1="864" y2="864" x1="208" />
            <wire x2="976" y1="864" y2="864" x1="496" />
            <wire x2="496" y1="864" y2="1008" x1="496" />
            <wire x2="2048" y1="1008" y2="1008" x1="496" />
        </branch>
        <iomarker fontsize="28" x="512" y="320" name="MARCHA" orien="R270" />
        <iomarker fontsize="28" x="912" y="320" name="RESET" orien="R270" />
        <iomarker fontsize="28" x="208" y="864" name="CLK" orien="R180" />
        <instance x="2048" y="1136" name="XLXI_3" orien="R0" />
        <branch name="CAFE">
            <wire x2="1696" y1="864" y2="864" x1="1360" />
            <wire x2="1696" y1="864" y2="944" x1="1696" />
            <wire x2="2048" y1="944" y2="944" x1="1696" />
            <wire x2="1696" y1="944" y2="1632" x1="1696" />
            <wire x2="1936" y1="1632" y2="1632" x1="1696" />
        </branch>
        <instance x="1568" y="848" name="XLXI_4" orien="R0" />
        <branch name="READY">
            <wire x2="1456" y1="800" y2="800" x1="1360" />
            <wire x2="1456" y1="800" y2="1488" x1="1456" />
            <wire x2="1936" y1="1488" y2="1488" x1="1456" />
            <wire x2="1456" y1="784" y2="800" x1="1456" />
            <wire x2="1568" y1="784" y2="784" x1="1456" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="1936" y1="752" y2="752" x1="1824" />
            <wire x2="1936" y1="752" y2="880" x1="1936" />
            <wire x2="2048" y1="880" y2="880" x1="1936" />
        </branch>
        <branch name="CALENTAR">
            <wire x2="1392" y1="736" y2="736" x1="1360" />
            <wire x2="1392" y1="736" y2="1360" x1="1392" />
            <wire x2="1936" y1="1360" y2="1360" x1="1392" />
        </branch>
        <iomarker fontsize="28" x="1936" y="1360" name="CALENTAR" orien="R0" />
        <iomarker fontsize="28" x="1936" y="1488" name="READY" orien="R0" />
        <iomarker fontsize="28" x="1936" y="1632" name="CAFE" orien="R0" />
        <branch name="XLXN_24">
            <wire x2="608" y1="768" y2="768" x1="528" />
            <wire x2="528" y1="768" y2="1184" x1="528" />
            <wire x2="2768" y1="1184" y2="1184" x1="528" />
            <wire x2="2768" y1="688" y2="688" x1="2432" />
            <wire x2="2768" y1="688" y2="1184" x1="2768" />
        </branch>
        <instance x="1904" y="608" name="XLXI_12" orien="R270" />
        <branch name="XLXN_33">
            <wire x2="1984" y1="320" y2="448" x1="1984" />
            <wire x2="1984" y1="448" y2="560" x1="1984" />
            <wire x2="2048" y1="560" y2="560" x1="1984" />
            <wire x2="1984" y1="448" y2="624" x1="1984" />
            <wire x2="2048" y1="624" y2="624" x1="1984" />
        </branch>
        <instance x="2048" y="192" name="XLXI_6" orien="R180" />
        <branch name="XLXN_32">
            <wire x2="1968" y1="544" y2="544" x1="1904" />
            <wire x2="1968" y1="544" y2="688" x1="1968" />
            <wire x2="2048" y1="688" y2="688" x1="1968" />
            <wire x2="1968" y1="688" y2="816" x1="1968" />
            <wire x2="2048" y1="816" y2="816" x1="1968" />
            <wire x2="2048" y1="496" y2="496" x1="1968" />
            <wire x2="1968" y1="496" y2="544" x1="1968" />
        </branch>
    </sheet>
</drawing>