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
        <signal name="CLK" />
        <signal name="XLXN_9" />
        <signal name="XLXN_21" />
        <signal name="INIT" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="Q3" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="XLXN_42" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="INIT" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q3" />
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
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
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
        <block symbolname="cb4cled" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_37" name="CE" />
            <blockpin signalname="XLXN_38" name="CLR" />
            <blockpin signalname="XLXN_38" name="D0" />
            <blockpin signalname="XLXN_38" name="D1" />
            <blockpin signalname="XLXN_37" name="D2" />
            <blockpin signalname="XLXN_38" name="D3" />
            <blockpin signalname="XLXN_21" name="L" />
            <blockpin signalname="XLXN_38" name="UP" />
            <blockpin name="CEO" />
            <blockpin signalname="Q0" name="Q0" />
            <blockpin signalname="Q1" name="Q1" />
            <blockpin signalname="Q2" name="Q2" />
            <blockpin signalname="Q3" name="Q3" />
            <blockpin signalname="XLXN_24" name="TC" />
        </block>
        <block symbolname="vcc" name="XLXI_2">
            <blockpin signalname="XLXN_37" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_5">
            <blockpin signalname="XLXN_38" name="G" />
        </block>
        <block symbolname="or2" name="XLXI_9">
            <blockpin signalname="XLXN_24" name="I0" />
            <blockpin signalname="INIT" name="I1" />
            <blockpin signalname="XLXN_21" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1408" y="1280" name="XLXI_1" orien="R0" />
        <instance x="1376" y="464" name="XLXI_5" orien="R180" />
        <instance x="1248" y="832" name="XLXI_2" orien="R270" />
        <branch name="CLK">
            <wire x2="1408" y1="1152" y2="1152" x1="496" />
        </branch>
        <branch name="XLXN_21">
            <wire x2="1392" y1="1008" y2="1008" x1="1184" />
            <wire x2="1392" y1="1008" y2="1024" x1="1392" />
            <wire x2="1408" y1="1024" y2="1024" x1="1392" />
        </branch>
        <instance x="928" y="1104" name="XLXI_9" orien="R0" />
        <iomarker fontsize="28" x="496" y="1152" name="CLK" orien="R180" />
        <branch name="INIT">
            <wire x2="720" y1="688" y2="976" x1="720" />
            <wire x2="928" y1="976" y2="976" x1="720" />
        </branch>
        <iomarker fontsize="28" x="720" y="688" name="INIT" orien="R270" />
        <branch name="XLXN_24">
            <wire x2="928" y1="1040" y2="1040" x1="848" />
            <wire x2="848" y1="1040" y2="1312" x1="848" />
            <wire x2="1904" y1="1312" y2="1312" x1="848" />
            <wire x2="1904" y1="1152" y2="1152" x1="1792" />
            <wire x2="1904" y1="1152" y2="1312" x1="1904" />
        </branch>
        <branch name="Q0">
            <wire x2="1824" y1="640" y2="640" x1="1792" />
        </branch>
        <iomarker fontsize="28" x="1824" y="640" name="Q0" orien="R0" />
        <branch name="Q1">
            <wire x2="1824" y1="704" y2="704" x1="1792" />
        </branch>
        <iomarker fontsize="28" x="1824" y="704" name="Q1" orien="R0" />
        <branch name="Q2">
            <wire x2="1824" y1="768" y2="768" x1="1792" />
        </branch>
        <iomarker fontsize="28" x="1824" y="768" name="Q2" orien="R0" />
        <branch name="Q3">
            <wire x2="1824" y1="832" y2="832" x1="1792" />
        </branch>
        <iomarker fontsize="28" x="1824" y="832" name="Q3" orien="R0" />
        <branch name="XLXN_37">
            <wire x2="1264" y1="768" y2="768" x1="1248" />
            <wire x2="1408" y1="768" y2="768" x1="1264" />
            <wire x2="1264" y1="768" y2="1088" x1="1264" />
            <wire x2="1408" y1="1088" y2="1088" x1="1264" />
        </branch>
        <branch name="XLXN_38">
            <wire x2="1312" y1="592" y2="640" x1="1312" />
            <wire x2="1408" y1="640" y2="640" x1="1312" />
            <wire x2="1312" y1="640" y2="704" x1="1312" />
            <wire x2="1408" y1="704" y2="704" x1="1312" />
            <wire x2="1312" y1="704" y2="832" x1="1312" />
            <wire x2="1408" y1="832" y2="832" x1="1312" />
            <wire x2="1312" y1="832" y2="960" x1="1312" />
            <wire x2="1408" y1="960" y2="960" x1="1312" />
            <wire x2="1312" y1="960" y2="1248" x1="1312" />
            <wire x2="1408" y1="1248" y2="1248" x1="1312" />
        </branch>
    </sheet>
</drawing>