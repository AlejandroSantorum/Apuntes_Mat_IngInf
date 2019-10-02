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
        <signal name="XLXN_7" />
        <signal name="XLXN_10" />
        <signal name="CLK" />
        <signal name="XLXN_12" />
        <signal name="INIT" />
        <signal name="XLXN_19" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="SIG_DIV" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="INIT" />
        <port polarity="Output" name="SIG_DIV" />
        <blockdef name="cd4cle">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-384" y2="-384" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <rect width="256" x="64" y="-640" height="576" />
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
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <block symbolname="cd4cle" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_6" name="CE" />
            <blockpin signalname="XLXN_28" name="CLR" />
            <blockpin signalname="XLXN_27" name="D0" />
            <blockpin signalname="XLXN_28" name="D1" />
            <blockpin signalname="XLXN_27" name="D2" />
            <blockpin signalname="XLXN_28" name="D3" />
            <blockpin signalname="XLXN_19" name="L" />
            <blockpin name="CEO" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin name="Q3" />
            <blockpin signalname="XLXN_5" name="TC" />
        </block>
        <block symbolname="cd4cle" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_5" name="CE" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_33" name="D0" />
            <blockpin signalname="XLXN_31" name="D1" />
            <blockpin signalname="XLXN_33" name="D2" />
            <blockpin signalname="XLXN_31" name="D3" />
            <blockpin signalname="XLXN_19" name="L" />
            <blockpin name="CEO" />
            <blockpin name="Q0" />
            <blockpin name="Q1" />
            <blockpin name="Q2" />
            <blockpin name="Q3" />
            <blockpin signalname="SIG_DIV" name="TC" />
        </block>
        <block symbolname="gnd" name="XLXI_3">
            <blockpin signalname="XLXN_28" name="G" />
        </block>
        <block symbolname="or2" name="XLXI_4">
            <blockpin signalname="SIG_DIV" name="I0" />
            <blockpin signalname="INIT" name="I1" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_5">
            <blockpin signalname="XLXN_6" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_6">
            <blockpin signalname="XLXN_31" name="G" />
        </block>
        <block symbolname="vcc" name="XLXI_8">
            <blockpin signalname="XLXN_33" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_9">
            <blockpin signalname="XLXN_27" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1056" y="992" name="XLXI_1" orien="R0" />
        <instance x="1392" y="2000" name="XLXI_2" orien="R0" />
        <instance x="1040" y="240" name="XLXI_3" orien="R180" />
        <branch name="XLXN_5">
            <wire x2="1248" y1="1152" y2="1808" x1="1248" />
            <wire x2="1392" y1="1808" y2="1808" x1="1248" />
            <wire x2="1520" y1="1152" y2="1152" x1="1248" />
            <wire x2="1520" y1="864" y2="864" x1="1440" />
            <wire x2="1520" y1="864" y2="1152" x1="1520" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1056" y1="800" y2="800" x1="880" />
        </branch>
        <instance x="880" y="864" name="XLXI_5" orien="R270" />
        <instance x="1424" y="1280" name="XLXI_6" orien="R180" />
        <branch name="CLK">
            <wire x2="992" y1="1024" y2="1024" x1="304" />
            <wire x2="992" y1="1024" y2="1872" x1="992" />
            <wire x2="1392" y1="1872" y2="1872" x1="992" />
            <wire x2="1056" y1="864" y2="864" x1="992" />
            <wire x2="992" y1="864" y2="1024" x1="992" />
        </branch>
        <iomarker fontsize="28" x="304" y="1024" name="CLK" orien="R180" />
        <instance x="544" y="832" name="XLXI_4" orien="R0" />
        <branch name="INIT">
            <wire x2="544" y1="704" y2="704" x1="368" />
        </branch>
        <iomarker fontsize="28" x="368" y="704" name="INIT" orien="R180" />
        <branch name="XLXN_19">
            <wire x2="1024" y1="736" y2="736" x1="800" />
            <wire x2="1056" y1="736" y2="736" x1="1024" />
            <wire x2="1024" y1="736" y2="1744" x1="1024" />
            <wire x2="1392" y1="1744" y2="1744" x1="1024" />
        </branch>
        <branch name="SIG_DIV">
            <wire x2="544" y1="768" y2="768" x1="464" />
            <wire x2="464" y1="768" y2="2112" x1="464" />
            <wire x2="1840" y1="2112" y2="2112" x1="464" />
            <wire x2="2064" y1="2112" y2="2112" x1="1840" />
            <wire x2="1840" y1="1872" y2="1872" x1="1776" />
            <wire x2="1840" y1="1872" y2="2112" x1="1840" />
        </branch>
        <iomarker fontsize="28" x="2064" y="2112" name="SIG_DIV" orien="R0" />
        <instance x="960" y="704" name="XLXI_9" orien="R270" />
        <branch name="XLXN_27">
            <wire x2="1008" y1="640" y2="640" x1="960" />
            <wire x2="1056" y1="416" y2="416" x1="1008" />
            <wire x2="1008" y1="416" y2="544" x1="1008" />
            <wire x2="1008" y1="544" y2="640" x1="1008" />
            <wire x2="1056" y1="544" y2="544" x1="1008" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="976" y1="368" y2="384" x1="976" />
            <wire x2="976" y1="384" y2="480" x1="976" />
            <wire x2="1056" y1="480" y2="480" x1="976" />
            <wire x2="976" y1="480" y2="608" x1="976" />
            <wire x2="1056" y1="608" y2="608" x1="976" />
            <wire x2="976" y1="608" y2="960" x1="976" />
            <wire x2="1056" y1="960" y2="960" x1="976" />
        </branch>
        <branch name="XLXN_31">
            <wire x2="1360" y1="1408" y2="1488" x1="1360" />
            <wire x2="1360" y1="1488" y2="1616" x1="1360" />
            <wire x2="1392" y1="1616" y2="1616" x1="1360" />
            <wire x2="1360" y1="1616" y2="1968" x1="1360" />
            <wire x2="1392" y1="1968" y2="1968" x1="1360" />
            <wire x2="1392" y1="1488" y2="1488" x1="1360" />
        </branch>
        <branch name="XLXN_33">
            <wire x2="1392" y1="1424" y2="1424" x1="1312" />
            <wire x2="1312" y1="1424" y2="1552" x1="1312" />
            <wire x2="1392" y1="1552" y2="1552" x1="1312" />
            <wire x2="1312" y1="1552" y2="1600" x1="1312" />
        </branch>
        <instance x="1376" y="1600" name="XLXI_8" orien="R180" />
    </sheet>
</drawing>