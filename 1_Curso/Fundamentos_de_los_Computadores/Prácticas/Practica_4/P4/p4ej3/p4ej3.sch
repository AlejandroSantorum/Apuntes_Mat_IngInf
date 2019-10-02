<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CLK" />
        <signal name="RESET" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="MARCHA" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="CALENTAR" />
        <signal name="READY" />
        <signal name="CAFE" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="RESET" />
        <port polarity="Input" name="MARCHA" />
        <port polarity="Output" name="CALENTAR" />
        <port polarity="Output" name="READY" />
        <port polarity="Output" name="CAFE" />
        <blockdef name="Memoria">
            <timestamp>2016-12-7T11:13:7</timestamp>
            <rect width="256" x="64" y="-448" height="448" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
        </blockdef>
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
        <block symbolname="Memoria" name="XLXI_1">
            <blockpin signalname="CAFE" name="CAFE" />
            <blockpin signalname="CALENTAR" name="CALENTAR" />
            <blockpin signalname="XLXN_12" name="D0" />
            <blockpin signalname="XLXN_13" name="D1" />
            <blockpin signalname="XLXN_14" name="D2" />
            <blockpin signalname="XLXN_15" name="D3" />
            <blockpin signalname="MARCHA" name="MARCHA" />
            <blockpin signalname="XLXN_6" name="Q0" />
            <blockpin signalname="XLXN_7" name="Q1" />
            <blockpin signalname="XLXN_9" name="Q2" />
            <blockpin signalname="XLXN_10" name="Q3" />
            <blockpin signalname="READY" name="READY" />
        </block>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_12" name="D" />
            <blockpin signalname="XLXN_6" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_13" name="D" />
            <blockpin signalname="XLXN_7" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_14" name="D" />
            <blockpin signalname="XLXN_9" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_5">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="RESET" name="CLR" />
            <blockpin signalname="XLXN_15" name="D" />
            <blockpin signalname="XLXN_10" name="Q" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1808" y="1904" name="XLXI_5" orien="R0" />
        <instance x="2400" y="864" name="XLXI_1" orien="R0">
        </instance>
        <branch name="CLK">
            <wire x2="240" y1="1776" y2="1776" x1="160" />
            <wire x2="672" y1="1776" y2="1776" x1="240" />
            <wire x2="1232" y1="1776" y2="1776" x1="672" />
            <wire x2="1808" y1="1776" y2="1776" x1="1232" />
            <wire x2="320" y1="560" y2="560" x1="240" />
            <wire x2="240" y1="560" y2="1776" x1="240" />
            <wire x2="800" y1="960" y2="960" x1="672" />
            <wire x2="672" y1="960" y2="1776" x1="672" />
            <wire x2="1312" y1="1360" y2="1360" x1="1232" />
            <wire x2="1232" y1="1360" y2="1776" x1="1232" />
        </branch>
        <branch name="RESET">
            <wire x2="320" y1="1872" y2="1872" x1="160" />
            <wire x2="800" y1="1872" y2="1872" x1="320" />
            <wire x2="1312" y1="1872" y2="1872" x1="800" />
            <wire x2="1808" y1="1872" y2="1872" x1="1312" />
            <wire x2="320" y1="656" y2="1872" x1="320" />
            <wire x2="800" y1="1056" y2="1872" x1="800" />
            <wire x2="1312" y1="1456" y2="1872" x1="1312" />
        </branch>
        <iomarker fontsize="28" x="160" y="1776" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="160" y="1872" name="RESET" orien="R180" />
        <instance x="320" y="688" name="XLXI_2" orien="R0" />
        <instance x="800" y="1088" name="XLXI_3" orien="R0" />
        <instance x="1312" y="1488" name="XLXI_4" orien="R0" />
        <branch name="XLXN_6">
            <wire x2="1552" y1="432" y2="432" x1="704" />
            <wire x2="1552" y1="432" y2="512" x1="1552" />
            <wire x2="2400" y1="512" y2="512" x1="1552" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="1792" y1="832" y2="832" x1="1184" />
            <wire x2="1792" y1="576" y2="832" x1="1792" />
            <wire x2="2400" y1="576" y2="576" x1="1792" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="2048" y1="1232" y2="1232" x1="1696" />
            <wire x2="2048" y1="640" y2="1232" x1="2048" />
            <wire x2="2400" y1="640" y2="640" x1="2048" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="2288" y1="1648" y2="1648" x1="2192" />
            <wire x2="2288" y1="704" y2="1648" x1="2288" />
            <wire x2="2400" y1="704" y2="704" x1="2288" />
        </branch>
        <branch name="MARCHA">
            <wire x2="1792" y1="176" y2="176" x1="1568" />
            <wire x2="1792" y1="176" y2="448" x1="1792" />
            <wire x2="2400" y1="448" y2="448" x1="1792" />
        </branch>
        <iomarker fontsize="28" x="1568" y="176" name="MARCHA" orien="R180" />
        <branch name="XLXN_12">
            <wire x2="320" y1="432" y2="432" x1="272" />
            <wire x2="272" y1="432" y2="1984" x1="272" />
            <wire x2="2816" y1="1984" y2="1984" x1="272" />
            <wire x2="2816" y1="640" y2="640" x1="2784" />
            <wire x2="2816" y1="640" y2="1984" x1="2816" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="800" y1="832" y2="832" x1="736" />
            <wire x2="736" y1="832" y2="2032" x1="736" />
            <wire x2="2848" y1="2032" y2="2032" x1="736" />
            <wire x2="2848" y1="704" y2="704" x1="2784" />
            <wire x2="2848" y1="704" y2="2032" x1="2848" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="1184" y1="1232" y2="2096" x1="1184" />
            <wire x2="2896" y1="2096" y2="2096" x1="1184" />
            <wire x2="1312" y1="1232" y2="1232" x1="1184" />
            <wire x2="2896" y1="768" y2="768" x1="2784" />
            <wire x2="2896" y1="768" y2="2096" x1="2896" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="1808" y1="1648" y2="1648" x1="1728" />
            <wire x2="1728" y1="1648" y2="2144" x1="1728" />
            <wire x2="2944" y1="2144" y2="2144" x1="1728" />
            <wire x2="2944" y1="832" y2="832" x1="2784" />
            <wire x2="2944" y1="832" y2="2144" x1="2944" />
        </branch>
        <branch name="CALENTAR">
            <wire x2="2816" y1="448" y2="448" x1="2784" />
        </branch>
        <iomarker fontsize="28" x="2816" y="448" name="CALENTAR" orien="R0" />
        <branch name="READY">
            <wire x2="2816" y1="512" y2="512" x1="2784" />
        </branch>
        <iomarker fontsize="28" x="2816" y="512" name="READY" orien="R0" />
        <branch name="CAFE">
            <wire x2="2816" y1="576" y2="576" x1="2784" />
        </branch>
        <iomarker fontsize="28" x="2816" y="576" name="CAFE" orien="R0" />
    </sheet>
</drawing>