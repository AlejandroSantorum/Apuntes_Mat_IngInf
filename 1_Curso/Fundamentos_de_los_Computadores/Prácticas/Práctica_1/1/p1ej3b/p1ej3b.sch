<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="A" />
        <signal name="C" />
        <signal name="B" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="Z" />
        <signal name="D" />
        <signal name="XLXN_18" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="B" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="D" />
        <blockdef name="nor3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="216" y1="-128" y2="-128" x1="256" />
            <circle r="12" cx="204" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="nor3" name="XLXI_1">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="B" name="I2" />
            <blockpin signalname="XLXN_15" name="O" />
        </block>
        <block symbolname="nor3" name="XLXI_2">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_12" name="I2" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_3">
            <blockpin signalname="XLXN_16" name="I0" />
            <blockpin signalname="XLXN_15" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_4">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="A">
            <wire x2="208" y1="256" y2="576" x1="208" />
        </branch>
        <instance x="176" y="576" name="XLXI_4" orien="R90" />
        <instance x="1152" y="1280" name="XLXI_1" orien="R0" />
        <branch name="C">
            <wire x2="528" y1="256" y2="1056" x1="528" />
            <wire x2="528" y1="1056" y2="1152" x1="528" />
            <wire x2="1152" y1="1152" y2="1152" x1="528" />
            <wire x2="528" y1="1152" y2="1584" x1="528" />
            <wire x2="1152" y1="1584" y2="1584" x1="528" />
        </branch>
        <branch name="B">
            <wire x2="384" y1="256" y2="1072" x1="384" />
            <wire x2="1152" y1="1072" y2="1072" x1="384" />
            <wire x2="1152" y1="1072" y2="1088" x1="1152" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="672" y1="592" y2="1216" x1="672" />
            <wire x2="1152" y1="1216" y2="1216" x1="672" />
            <wire x2="672" y1="1216" y2="1648" x1="672" />
            <wire x2="1152" y1="1648" y2="1648" x1="672" />
        </branch>
        <instance x="1152" y="1712" name="XLXI_2" orien="R0" />
        <branch name="XLXN_12">
            <wire x2="208" y1="800" y2="1520" x1="208" />
            <wire x2="1152" y1="1520" y2="1520" x1="208" />
        </branch>
        <instance x="1600" y="1440" name="XLXI_3" orien="R0" />
        <branch name="XLXN_15">
            <wire x2="1504" y1="1152" y2="1152" x1="1408" />
            <wire x2="1504" y1="1152" y2="1312" x1="1504" />
            <wire x2="1600" y1="1312" y2="1312" x1="1504" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="1504" y1="1584" y2="1584" x1="1408" />
            <wire x2="1504" y1="1376" y2="1584" x1="1504" />
            <wire x2="1600" y1="1376" y2="1376" x1="1504" />
        </branch>
        <iomarker fontsize="28" x="208" y="256" name="A" orien="R270" />
        <iomarker fontsize="28" x="384" y="256" name="B" orien="R270" />
        <iomarker fontsize="28" x="528" y="256" name="C" orien="R270" />
        <branch name="Z">
            <wire x2="1888" y1="1344" y2="1344" x1="1856" />
        </branch>
        <iomarker fontsize="28" x="1888" y="1344" name="Z" orien="R0" />
        <instance x="640" y="368" name="XLXI_5" orien="R90" />
        <branch name="D">
            <wire x2="672" y1="288" y2="352" x1="672" />
            <wire x2="672" y1="352" y2="368" x1="672" />
        </branch>
        <iomarker fontsize="28" x="672" y="288" name="D" orien="R270" />
    </sheet>
</drawing>