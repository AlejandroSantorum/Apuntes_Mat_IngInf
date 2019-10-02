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
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="X0" />
        <signal name="X1" />
        <signal name="X2" />
        <signal name="X3" />
        <signal name="FIN" />
        <signal name="PREMIO" />
        <signal name="BOLA" />
        <signal name="ENABLE">
        </signal>
        <signal name="XLXN_16" />
        <port polarity="Input" name="X0" />
        <port polarity="Input" name="X1" />
        <port polarity="Input" name="X2" />
        <port polarity="Input" name="X3" />
        <port polarity="Output" name="FIN" />
        <port polarity="Output" name="PREMIO" />
        <port polarity="Output" name="BOLA" />
        <blockdef name="d4_16e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-1152" height="1088" />
            <line x2="320" y1="-1088" y2="-1088" x1="384" />
            <line x2="320" y1="-1024" y2="-1024" x1="384" />
            <line x2="320" y1="-960" y2="-960" x1="384" />
            <line x2="320" y1="-896" y2="-896" x1="384" />
            <line x2="320" y1="-832" y2="-832" x1="384" />
            <line x2="320" y1="-768" y2="-768" x1="384" />
            <line x2="320" y1="-704" y2="-704" x1="384" />
            <line x2="320" y1="-640" y2="-640" x1="384" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-320" y2="-320" x1="384" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <line x2="64" y1="-896" y2="-896" x1="0" />
            <line x2="64" y1="-960" y2="-960" x1="0" />
            <line x2="64" y1="-1024" y2="-1024" x1="0" />
            <line x2="64" y1="-1088" y2="-1088" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="or6">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="48" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-320" y2="-320" x1="0" />
            <line x2="48" y1="-384" y2="-384" x1="0" />
            <line x2="192" y1="-224" y2="-224" x1="256" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <arc ex="112" ey="-272" sx="192" sy="-224" r="88" cx="116" cy="-184" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
            <arc ex="192" ey="-224" sx="112" sy="-176" r="88" cx="116" cy="-264" />
            <arc ex="48" ey="-272" sx="48" sy="-176" r="56" cx="16" cy="-224" />
            <line x2="48" y1="-272" y2="-272" x1="112" />
            <line x2="48" y1="-64" y2="-176" x1="48" />
            <line x2="48" y1="-272" y2="-384" x1="48" />
        </blockdef>
        <blockdef name="or4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <arc ex="112" ey="-208" sx="192" sy="-160" r="88" cx="116" cy="-120" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <line x2="48" y1="-112" y2="-112" x1="112" />
            <line x2="48" y1="-256" y2="-208" x1="48" />
            <line x2="48" y1="-64" y2="-112" x1="48" />
            <arc ex="48" ey="-208" sx="48" sy="-112" r="56" cx="16" cy="-160" />
            <arc ex="192" ey="-160" sx="112" sy="-112" r="88" cx="116" cy="-200" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <block symbolname="d4_16e" name="XLXI_1">
            <blockpin signalname="X0" name="A0" />
            <blockpin signalname="X1" name="A1" />
            <blockpin signalname="X2" name="A2" />
            <blockpin signalname="X3" name="A3" />
            <blockpin signalname="ENABLE" name="E" />
            <blockpin signalname="XLXN_6" name="D0" />
            <blockpin signalname="XLXN_11" name="D1" />
            <blockpin signalname="XLXN_8" name="D10" />
            <blockpin signalname="XLXN_15" name="D11" />
            <blockpin signalname="XLXN_2" name="D12" />
            <blockpin signalname="XLXN_16" name="D13" />
            <blockpin signalname="XLXN_7" name="D14" />
            <blockpin signalname="XLXN_1" name="D15" />
            <blockpin signalname="XLXN_12" name="D2" />
            <blockpin signalname="XLXN_5" name="D3" />
            <blockpin signalname="XLXN_13" name="D4" />
            <blockpin signalname="XLXN_10" name="D5" />
            <blockpin signalname="XLXN_4" name="D6" />
            <blockpin signalname="XLXN_9" name="D7" />
            <blockpin signalname="XLXN_14" name="D8" />
            <blockpin signalname="XLXN_3" name="D9" />
        </block>
        <block symbolname="or6" name="XLXI_2">
            <blockpin signalname="XLXN_1" name="I0" />
            <blockpin signalname="XLXN_2" name="I1" />
            <blockpin signalname="XLXN_3" name="I2" />
            <blockpin signalname="XLXN_4" name="I3" />
            <blockpin signalname="XLXN_5" name="I4" />
            <blockpin signalname="XLXN_6" name="I5" />
            <blockpin signalname="FIN" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_3">
            <blockpin signalname="XLXN_7" name="I0" />
            <blockpin signalname="XLXN_8" name="I1" />
            <blockpin signalname="XLXN_9" name="I2" />
            <blockpin signalname="XLXN_10" name="I3" />
            <blockpin signalname="PREMIO" name="O" />
        </block>
        <block symbolname="or6" name="XLXI_4">
            <blockpin signalname="XLXN_16" name="I0" />
            <blockpin signalname="XLXN_15" name="I1" />
            <blockpin signalname="XLXN_14" name="I2" />
            <blockpin signalname="XLXN_13" name="I3" />
            <blockpin signalname="XLXN_12" name="I4" />
            <blockpin signalname="XLXN_11" name="I5" />
            <blockpin signalname="BOLA" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_5">
            <blockpin signalname="ENABLE" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <iomarker fontsize="28" x="1056" y="736" name="X0" orien="R180" />
        <iomarker fontsize="28" x="1056" y="800" name="X1" orien="R180" />
        <iomarker fontsize="28" x="1056" y="864" name="X2" orien="R180" />
        <iomarker fontsize="28" x="1056" y="928" name="X3" orien="R180" />
        <branch name="FIN">
            <wire x2="2384" y1="752" y2="752" x1="2368" />
            <wire x2="2400" y1="752" y2="752" x1="2384" />
        </branch>
        <branch name="PREMIO">
            <wire x2="2384" y1="1168" y2="1168" x1="2368" />
            <wire x2="2400" y1="1168" y2="1168" x1="2384" />
        </branch>
        <iomarker fontsize="28" x="2400" y="1168" name="PREMIO" orien="R0" />
        <branch name="BOLA">
            <wire x2="2368" y1="1520" y2="1520" x1="2352" />
            <wire x2="2384" y1="1520" y2="1520" x1="2368" />
        </branch>
        <iomarker fontsize="28" x="2384" y="1520" name="BOLA" orien="R0" />
        <iomarker fontsize="28" x="2400" y="752" name="FIN" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="1488" y1="1504" y2="1504" x1="1472" />
            <wire x2="1776" y1="1504" y2="1504" x1="1488" />
            <wire x2="1776" y1="848" y2="1504" x1="1776" />
            <wire x2="2096" y1="848" y2="848" x1="1776" />
            <wire x2="2112" y1="848" y2="848" x1="2096" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="1488" y1="1440" y2="1440" x1="1472" />
            <wire x2="1760" y1="1440" y2="1440" x1="1488" />
            <wire x2="1760" y1="1440" y2="1616" x1="1760" />
            <wire x2="2080" y1="1616" y2="1616" x1="1760" />
            <wire x2="2096" y1="1616" y2="1616" x1="2080" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="1488" y1="1376" y2="1376" x1="1472" />
            <wire x2="1744" y1="1376" y2="1376" x1="1488" />
            <wire x2="1744" y1="1200" y2="1376" x1="1744" />
            <wire x2="2096" y1="1200" y2="1200" x1="1744" />
            <wire x2="2112" y1="1200" y2="1200" x1="2096" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1488" y1="1312" y2="1312" x1="1472" />
            <wire x2="1760" y1="1312" y2="1312" x1="1488" />
            <wire x2="1760" y1="784" y2="1312" x1="1760" />
            <wire x2="2096" y1="784" y2="784" x1="1760" />
            <wire x2="2112" y1="784" y2="784" x1="2096" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="1488" y1="1248" y2="1248" x1="1472" />
            <wire x2="1712" y1="1248" y2="1248" x1="1488" />
            <wire x2="1712" y1="1248" y2="1552" x1="1712" />
            <wire x2="2080" y1="1552" y2="1552" x1="1712" />
            <wire x2="2096" y1="1552" y2="1552" x1="2080" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1488" y1="1120" y2="1120" x1="1472" />
            <wire x2="1744" y1="1120" y2="1120" x1="1488" />
            <wire x2="1744" y1="720" y2="1120" x1="1744" />
            <wire x2="2096" y1="720" y2="720" x1="1744" />
            <wire x2="2112" y1="720" y2="720" x1="2096" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="1488" y1="992" y2="992" x1="1472" />
            <wire x2="1728" y1="992" y2="992" x1="1488" />
            <wire x2="1728" y1="992" y2="1488" x1="1728" />
            <wire x2="2080" y1="1488" y2="1488" x1="1728" />
            <wire x2="2096" y1="1488" y2="1488" x1="2080" />
        </branch>
        <branch name="XLXN_5">
            <wire x2="1488" y1="928" y2="928" x1="1472" />
            <wire x2="1728" y1="928" y2="928" x1="1488" />
            <wire x2="1728" y1="656" y2="928" x1="1728" />
            <wire x2="2096" y1="656" y2="656" x1="1728" />
            <wire x2="2112" y1="656" y2="656" x1="2096" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="1488" y1="864" y2="864" x1="1472" />
            <wire x2="1824" y1="864" y2="864" x1="1488" />
            <wire x2="1824" y1="864" y2="1424" x1="1824" />
            <wire x2="2080" y1="1424" y2="1424" x1="1824" />
            <wire x2="2096" y1="1424" y2="1424" x1="2080" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="1488" y1="800" y2="800" x1="1472" />
            <wire x2="2096" y1="800" y2="800" x1="1488" />
            <wire x2="2096" y1="800" y2="1344" x1="2096" />
            <wire x2="2096" y1="1344" y2="1360" x1="2096" />
        </branch>
        <branch name="X3">
            <wire x2="1072" y1="928" y2="928" x1="1056" />
            <wire x2="1088" y1="928" y2="928" x1="1072" />
        </branch>
        <branch name="X2">
            <wire x2="1072" y1="864" y2="864" x1="1056" />
            <wire x2="1088" y1="864" y2="864" x1="1072" />
        </branch>
        <branch name="X1">
            <wire x2="1072" y1="800" y2="800" x1="1056" />
            <wire x2="1088" y1="800" y2="800" x1="1072" />
        </branch>
        <branch name="X0">
            <wire x2="1072" y1="736" y2="736" x1="1056" />
            <wire x2="1088" y1="736" y2="736" x1="1072" />
        </branch>
        <instance x="1088" y="1824" name="XLXI_1" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1488" y1="1696" y2="1696" x1="1472" />
            <wire x2="1792" y1="1696" y2="1696" x1="1488" />
            <wire x2="1792" y1="912" y2="1696" x1="1792" />
            <wire x2="2112" y1="912" y2="912" x1="1792" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1488" y1="736" y2="736" x1="1472" />
            <wire x2="1712" y1="736" y2="736" x1="1488" />
            <wire x2="1712" y1="592" y2="736" x1="1712" />
            <wire x2="2096" y1="592" y2="592" x1="1712" />
            <wire x2="2112" y1="592" y2="592" x1="2096" />
        </branch>
        <instance x="2112" y="976" name="XLXI_2" orien="R0" />
        <branch name="XLXN_7">
            <wire x2="1488" y1="1632" y2="1632" x1="1472" />
            <wire x2="1808" y1="1632" y2="1632" x1="1488" />
            <wire x2="1808" y1="1264" y2="1632" x1="1808" />
            <wire x2="2112" y1="1264" y2="1264" x1="1808" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1488" y1="1184" y2="1184" x1="1472" />
            <wire x2="1744" y1="1184" y2="1184" x1="1488" />
            <wire x2="1744" y1="1136" y2="1184" x1="1744" />
            <wire x2="2096" y1="1136" y2="1136" x1="1744" />
            <wire x2="2112" y1="1136" y2="1136" x1="2096" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1488" y1="1056" y2="1056" x1="1472" />
            <wire x2="2112" y1="1056" y2="1056" x1="1488" />
            <wire x2="2112" y1="1056" y2="1072" x1="2112" />
        </branch>
        <instance x="2112" y="1328" name="XLXI_3" orien="R0" />
        <branch name="XLXN_16">
            <wire x2="1488" y1="1568" y2="1568" x1="1472" />
            <wire x2="1776" y1="1568" y2="1568" x1="1488" />
            <wire x2="1776" y1="1568" y2="1680" x1="1776" />
            <wire x2="2080" y1="1680" y2="1680" x1="1776" />
            <wire x2="2096" y1="1680" y2="1680" x1="2080" />
        </branch>
        <instance x="2096" y="1744" name="XLXI_4" orien="R0" />
        <instance x="880" y="1616" name="XLXI_5" orien="R0" />
        <branch name="ENABLE">
            <wire x2="944" y1="1616" y2="1696" x1="944" />
            <wire x2="1056" y1="1696" y2="1696" x1="944" />
            <wire x2="1072" y1="1696" y2="1696" x1="1056" />
            <wire x2="1088" y1="1696" y2="1696" x1="1072" />
        </branch>
    </sheet>
</drawing>