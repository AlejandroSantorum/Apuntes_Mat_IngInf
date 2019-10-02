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
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="D" />
        <signal name="XLXN_41" />
        <signal name="XLXN_42" />
        <signal name="XLXN_43" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_47" />
        <signal name="XLXN_48" />
        <signal name="XLXN_49" />
        <signal name="XLXN_50" />
        <signal name="XLXN_51" />
        <signal name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
        <port polarity="Output" name="Z" />
        <blockdef name="and4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-112" y2="-112" x1="144" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-64" y2="-64" x1="0" />
        </blockdef>
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="and4" name="XLXI_1">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="XLXN_27" name="I1" />
            <blockpin signalname="XLXN_26" name="I2" />
            <blockpin signalname="XLXN_25" name="I3" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_2">
            <blockpin signalname="XLXN_29" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_28" name="I2" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_3">
            <blockpin signalname="XLXN_30" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_4">
            <blockpin signalname="XLXN_51" name="I0" />
            <blockpin signalname="XLXN_31" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_5">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="XLXN_2" name="I2" />
            <blockpin signalname="XLXN_1" name="I3" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_10">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_11">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_12">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_27" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_13">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_28" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_14">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_29" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_15">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_30" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_16">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_31" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_17">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_51" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1184" y="704" name="XLXI_1" orien="R0" />
        <instance x="1184" y="992" name="XLXI_2" orien="R0" />
        <instance x="1184" y="1264" name="XLXI_3" orien="R0" />
        <instance x="1184" y="1568" name="XLXI_4" orien="R0" />
        <instance x="1920" y="1120" name="XLXI_5" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1920" y1="544" y2="544" x1="1440" />
            <wire x2="1920" y1="544" y2="864" x1="1920" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1680" y1="864" y2="864" x1="1440" />
            <wire x2="1680" y1="864" y2="928" x1="1680" />
            <wire x2="1920" y1="928" y2="928" x1="1680" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1680" y1="1136" y2="1136" x1="1440" />
            <wire x2="1680" y1="992" y2="1136" x1="1680" />
            <wire x2="1920" y1="992" y2="992" x1="1680" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1920" y1="1440" y2="1440" x1="1440" />
            <wire x2="1920" y1="1056" y2="1440" x1="1920" />
        </branch>
        <instance x="928" y="480" name="XLXI_10" orien="R0" />
        <instance x="944" y="544" name="XLXI_11" orien="R0" />
        <instance x="944" y="608" name="XLXI_12" orien="R0" />
        <instance x="928" y="832" name="XLXI_13" orien="R0" />
        <instance x="928" y="960" name="XLXI_14" orien="R0" />
        <instance x="912" y="1232" name="XLXI_15" orien="R0" />
        <instance x="928" y="1472" name="XLXI_16" orien="R0" />
        <instance x="928" y="1536" name="XLXI_17" orien="R0" />
        <branch name="XLXN_25">
            <wire x2="1184" y1="448" y2="448" x1="1152" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="1184" y1="512" y2="512" x1="1168" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="1184" y1="576" y2="576" x1="1168" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="1184" y1="800" y2="800" x1="1152" />
        </branch>
        <branch name="XLXN_29">
            <wire x2="1184" y1="928" y2="928" x1="1152" />
        </branch>
        <branch name="XLXN_30">
            <wire x2="1184" y1="1200" y2="1200" x1="1136" />
        </branch>
        <branch name="XLXN_31">
            <wire x2="1184" y1="1440" y2="1440" x1="1152" />
        </branch>
        <branch name="A">
            <wire x2="224" y1="448" y2="448" x1="176" />
            <wire x2="224" y1="448" y2="800" x1="224" />
            <wire x2="512" y1="800" y2="800" x1="224" />
            <wire x2="928" y1="800" y2="800" x1="512" />
            <wire x2="368" y1="448" y2="448" x1="224" />
            <wire x2="368" y1="448" y2="1072" x1="368" />
            <wire x2="1184" y1="1072" y2="1072" x1="368" />
            <wire x2="512" y1="448" y2="448" x1="368" />
            <wire x2="928" y1="448" y2="448" x1="512" />
            <wire x2="512" y1="448" y2="1376" x1="512" />
            <wire x2="1184" y1="1376" y2="1376" x1="512" />
        </branch>
        <branch name="B">
            <wire x2="400" y1="512" y2="512" x1="176" />
            <wire x2="944" y1="512" y2="512" x1="400" />
            <wire x2="400" y1="512" y2="1136" x1="400" />
            <wire x2="1184" y1="1136" y2="1136" x1="400" />
        </branch>
        <branch name="C">
            <wire x2="272" y1="576" y2="576" x1="176" />
            <wire x2="272" y1="576" y2="864" x1="272" />
            <wire x2="1184" y1="864" y2="864" x1="272" />
            <wire x2="560" y1="576" y2="576" x1="272" />
            <wire x2="944" y1="576" y2="576" x1="560" />
            <wire x2="560" y1="576" y2="1440" x1="560" />
            <wire x2="928" y1="1440" y2="1440" x1="560" />
        </branch>
        <iomarker fontsize="28" x="176" y="448" name="A" orien="R180" />
        <iomarker fontsize="28" x="176" y="512" name="B" orien="R180" />
        <iomarker fontsize="28" x="176" y="576" name="C" orien="R180" />
        <iomarker fontsize="28" x="176" y="640" name="D" orien="R180" />
        <branch name="D">
            <wire x2="304" y1="640" y2="640" x1="176" />
            <wire x2="304" y1="640" y2="928" x1="304" />
            <wire x2="608" y1="928" y2="928" x1="304" />
            <wire x2="928" y1="928" y2="928" x1="608" />
            <wire x2="448" y1="640" y2="640" x1="304" />
            <wire x2="448" y1="640" y2="1200" x1="448" />
            <wire x2="912" y1="1200" y2="1200" x1="448" />
            <wire x2="608" y1="640" y2="640" x1="448" />
            <wire x2="1184" y1="640" y2="640" x1="608" />
            <wire x2="608" y1="640" y2="1504" x1="608" />
            <wire x2="928" y1="1504" y2="1504" x1="608" />
        </branch>
        <branch name="XLXN_51">
            <wire x2="1168" y1="1504" y2="1504" x1="1152" />
            <wire x2="1184" y1="1504" y2="1504" x1="1168" />
        </branch>
        <branch name="Z">
            <wire x2="2208" y1="960" y2="960" x1="2176" />
        </branch>
        <iomarker fontsize="28" x="2208" y="960" name="Z" orien="R0" />
    </sheet>
</drawing>