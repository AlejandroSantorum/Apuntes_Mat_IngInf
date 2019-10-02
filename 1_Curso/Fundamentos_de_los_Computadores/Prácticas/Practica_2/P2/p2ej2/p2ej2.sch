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
        <signal name="X2" />
        <signal name="X3" />
        <signal name="X1" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="XLXN_25" />
        <signal name="XLXN_27" />
        <signal name="XLXN_29" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_35" />
        <signal name="FIN" />
        <signal name="PREMIO" />
        <signal name="BOLA" />
        <signal name="X0" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="XLXN_42" />
        <signal name="XLXN_43" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_46" />
        <signal name="XLXN_47" />
        <signal name="XLXN_48" />
        <signal name="XLXN_51" />
        <signal name="XLXN_52" />
        <signal name="XLXN_53" />
        <port polarity="Input" name="X2" />
        <port polarity="Input" name="X3" />
        <port polarity="Input" name="X1" />
        <port polarity="Output" name="FIN" />
        <port polarity="Output" name="PREMIO" />
        <port polarity="Output" name="BOLA" />
        <port polarity="Input" name="X0" />
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
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="xnor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
            <circle r="8" cx="220" cy="-96" />
            <line x2="256" y1="-96" y2="-96" x1="228" />
            <line x2="60" y1="-28" y2="-28" x1="60" />
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
        <blockdef name="xor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <line x2="208" y1="-96" y2="-96" x1="256" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
        </blockdef>
        <blockdef name="nor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
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
        <block symbolname="m4_1e" name="XLXI_1">
            <blockpin signalname="XLXN_44" name="D0" />
            <blockpin signalname="XLXN_46" name="D1" />
            <blockpin signalname="XLXN_47" name="D2" />
            <blockpin signalname="XLXN_44" name="D3" />
            <blockpin signalname="XLXN_1" name="E" />
            <blockpin signalname="X2" name="S0" />
            <blockpin signalname="X3" name="S1" />
            <blockpin signalname="FIN" name="O" />
        </block>
        <block symbolname="m4_1e" name="XLXI_2">
            <blockpin signalname="XLXN_53" name="D0" />
            <blockpin signalname="X0" name="D1" />
            <blockpin signalname="XLXN_46" name="D2" />
            <blockpin signalname="XLXN_46" name="D3" />
            <blockpin signalname="XLXN_2" name="E" />
            <blockpin signalname="X2" name="S0" />
            <blockpin signalname="X3" name="S1" />
            <blockpin signalname="PREMIO" name="O" />
        </block>
        <block symbolname="m4_1e" name="XLXI_3">
            <blockpin signalname="XLXN_51" name="D0" />
            <blockpin signalname="XLXN_52" name="D1" />
            <blockpin signalname="XLXN_44" name="D2" />
            <blockpin signalname="XLXN_47" name="D3" />
            <blockpin signalname="XLXN_3" name="E" />
            <blockpin signalname="X2" name="S0" />
            <blockpin signalname="X3" name="S1" />
            <blockpin signalname="BOLA" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_4">
            <blockpin signalname="XLXN_1" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_5">
            <blockpin signalname="XLXN_2" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_6">
            <blockpin signalname="XLXN_3" name="P" />
        </block>
        <block symbolname="xnor2" name="XLXI_9">
            <blockpin signalname="X0" name="I0" />
            <blockpin signalname="X1" name="I1" />
            <blockpin signalname="XLXN_44" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_10">
            <blockpin signalname="X0" name="I0" />
            <blockpin signalname="X1" name="I1" />
            <blockpin signalname="XLXN_46" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_11">
            <blockpin signalname="X1" name="I0" />
            <blockpin signalname="X0" name="I1" />
            <blockpin signalname="XLXN_47" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_12">
            <blockpin signalname="X1" name="I0" />
            <blockpin signalname="X0" name="I1" />
            <blockpin signalname="XLXN_51" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_13">
            <blockpin signalname="X1" name="I0" />
            <blockpin signalname="X0" name="I1" />
            <blockpin signalname="XLXN_52" name="O" />
        </block>
        <block symbolname="gnd" name="XLXI_15">
            <blockpin signalname="XLXN_53" name="G" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="2128" y="784" name="XLXI_1" orien="R0" />
        <instance x="2128" y="1376" name="XLXI_2" orien="R0" />
        <instance x="2144" y="2032" name="XLXI_3" orien="R0" />
        <instance x="2096" y="816" name="XLXI_4" orien="R270" />
        <instance x="2096" y="1408" name="XLXI_5" orien="R270" />
        <instance x="2128" y="2064" name="XLXI_6" orien="R270" />
        <branch name="XLXN_1">
            <wire x2="2128" y1="752" y2="752" x1="2096" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="2128" y1="1344" y2="1344" x1="2096" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="2144" y1="2000" y2="2000" x1="2128" />
        </branch>
        <branch name="X2">
            <wire x2="640" y1="192" y2="656" x1="640" />
            <wire x2="1376" y1="656" y2="656" x1="640" />
            <wire x2="1376" y1="624" y2="656" x1="1376" />
            <wire x2="1776" y1="624" y2="624" x1="1376" />
            <wire x2="2128" y1="624" y2="624" x1="1776" />
            <wire x2="1776" y1="624" y2="1216" x1="1776" />
            <wire x2="2128" y1="1216" y2="1216" x1="1776" />
            <wire x2="1776" y1="1216" y2="1872" x1="1776" />
            <wire x2="2144" y1="1872" y2="1872" x1="1776" />
        </branch>
        <branch name="X3">
            <wire x2="448" y1="192" y2="672" x1="448" />
            <wire x2="448" y1="672" y2="688" x1="448" />
            <wire x2="1840" y1="688" y2="688" x1="448" />
            <wire x2="2128" y1="688" y2="688" x1="1840" />
            <wire x2="1840" y1="688" y2="1280" x1="1840" />
            <wire x2="2128" y1="1280" y2="1280" x1="1840" />
            <wire x2="1840" y1="1280" y2="1936" x1="1840" />
            <wire x2="2144" y1="1936" y2="1936" x1="1840" />
        </branch>
        <iomarker fontsize="28" x="448" y="192" name="X3" orien="R270" />
        <iomarker fontsize="28" x="640" y="192" name="X2" orien="R270" />
        <branch name="X1">
            <wire x2="800" y1="192" y2="768" x1="800" />
            <wire x2="1040" y1="768" y2="768" x1="800" />
            <wire x2="800" y1="768" y2="992" x1="800" />
            <wire x2="1008" y1="992" y2="992" x1="800" />
            <wire x2="800" y1="992" y2="1248" x1="800" />
            <wire x2="1024" y1="1248" y2="1248" x1="800" />
            <wire x2="800" y1="1248" y2="1456" x1="800" />
            <wire x2="1008" y1="1456" y2="1456" x1="800" />
            <wire x2="800" y1="1456" y2="1632" x1="800" />
            <wire x2="992" y1="1632" y2="1632" x1="800" />
        </branch>
        <iomarker fontsize="28" x="800" y="192" name="X1" orien="R270" />
        <instance x="1040" y="896" name="XLXI_9" orien="R0" />
        <instance x="1008" y="1120" name="XLXI_10" orien="R0" />
        <instance x="1024" y="1312" name="XLXI_11" orien="R0" />
        <instance x="1008" y="1520" name="XLXI_12" orien="R0" />
        <instance x="992" y="1696" name="XLXI_13" orien="R0" />
        <branch name="FIN">
            <wire x2="2480" y1="464" y2="464" x1="2448" />
        </branch>
        <iomarker fontsize="28" x="2480" y="464" name="FIN" orien="R0" />
        <branch name="PREMIO">
            <wire x2="2480" y1="1056" y2="1056" x1="2448" />
        </branch>
        <iomarker fontsize="28" x="2480" y="1056" name="PREMIO" orien="R0" />
        <branch name="BOLA">
            <wire x2="2496" y1="1712" y2="1712" x1="2464" />
        </branch>
        <iomarker fontsize="28" x="2496" y="1712" name="BOLA" orien="R0" />
        <branch name="X0">
            <wire x2="960" y1="176" y2="832" x1="960" />
            <wire x2="1040" y1="832" y2="832" x1="960" />
            <wire x2="960" y1="832" y2="1056" x1="960" />
            <wire x2="1008" y1="1056" y2="1056" x1="960" />
            <wire x2="960" y1="1056" y2="1104" x1="960" />
            <wire x2="960" y1="1104" y2="1184" x1="960" />
            <wire x2="1024" y1="1184" y2="1184" x1="960" />
            <wire x2="960" y1="1184" y2="1392" x1="960" />
            <wire x2="1008" y1="1392" y2="1392" x1="960" />
            <wire x2="960" y1="1392" y2="1568" x1="960" />
            <wire x2="992" y1="1568" y2="1568" x1="960" />
            <wire x2="1744" y1="1104" y2="1104" x1="960" />
            <wire x2="1744" y1="1024" y2="1104" x1="1744" />
            <wire x2="2128" y1="1024" y2="1024" x1="1744" />
        </branch>
        <iomarker fontsize="28" x="960" y="176" name="X0" orien="R270" />
        <branch name="XLXN_44">
            <wire x2="1712" y1="800" y2="800" x1="1296" />
            <wire x2="1920" y1="800" y2="800" x1="1712" />
            <wire x2="1712" y1="800" y2="1744" x1="1712" />
            <wire x2="2144" y1="1744" y2="1744" x1="1712" />
            <wire x2="1712" y1="368" y2="800" x1="1712" />
            <wire x2="2128" y1="368" y2="368" x1="1712" />
            <wire x2="1920" y1="560" y2="800" x1="1920" />
            <wire x2="2128" y1="560" y2="560" x1="1920" />
        </branch>
        <branch name="XLXN_46">
            <wire x2="1696" y1="1024" y2="1024" x1="1264" />
            <wire x2="1696" y1="1024" y2="1088" x1="1696" />
            <wire x2="2128" y1="1088" y2="1088" x1="1696" />
            <wire x2="1728" y1="1024" y2="1024" x1="1696" />
            <wire x2="1728" y1="1024" y2="1152" x1="1728" />
            <wire x2="2096" y1="1152" y2="1152" x1="1728" />
            <wire x2="2128" y1="1152" y2="1152" x1="2096" />
            <wire x2="1696" y1="432" y2="1024" x1="1696" />
            <wire x2="2128" y1="432" y2="432" x1="1696" />
        </branch>
        <branch name="XLXN_47">
            <wire x2="1680" y1="1216" y2="1216" x1="1280" />
            <wire x2="1760" y1="1216" y2="1216" x1="1680" />
            <wire x2="1760" y1="1216" y2="1808" x1="1760" />
            <wire x2="2144" y1="1808" y2="1808" x1="1760" />
            <wire x2="1680" y1="496" y2="1216" x1="1680" />
            <wire x2="2128" y1="496" y2="496" x1="1680" />
        </branch>
        <branch name="XLXN_51">
            <wire x2="1696" y1="1424" y2="1424" x1="1264" />
            <wire x2="1696" y1="1424" y2="1616" x1="1696" />
            <wire x2="2144" y1="1616" y2="1616" x1="1696" />
        </branch>
        <branch name="XLXN_52">
            <wire x2="1680" y1="1600" y2="1600" x1="1248" />
            <wire x2="1680" y1="1600" y2="1680" x1="1680" />
            <wire x2="2144" y1="1680" y2="1680" x1="1680" />
        </branch>
        <branch name="XLXN_53">
            <wire x2="2128" y1="960" y2="960" x1="2096" />
        </branch>
        <instance x="1968" y="896" name="XLXI_15" orien="R90" />
    </sheet>
</drawing>