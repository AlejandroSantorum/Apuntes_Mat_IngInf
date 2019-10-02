<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="B" />
        <signal name="C" />
        <signal name="D" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="A" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="Z" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="A" />
        <port polarity="Output" name="Z" />
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
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
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
        <blockdef name="and3b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="xor3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="208" y1="-128" y2="-128" x1="256" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <arc ex="64" ey="-176" sx="64" sy="-80" r="56" cx="32" cy="-128" />
            <arc ex="128" ey="-176" sx="208" sy="-128" r="88" cx="132" cy="-88" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="64" y1="-80" y2="-80" x1="128" />
            <line x2="64" y1="-176" y2="-176" x1="128" />
            <arc ex="208" ey="-128" sx="128" sy="-80" r="88" cx="132" cy="-168" />
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
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="XLXN_25" name="I0" />
            <blockpin signalname="XLXN_19" name="I1" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="XLXN_15" name="I1" />
            <blockpin signalname="XLXN_23" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_3">
            <blockpin signalname="XLXN_9" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_4">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="XLXN_23" name="I1" />
            <blockpin signalname="XLXN_21" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_5">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="XLXN_9" name="I1" />
            <blockpin signalname="XLXN_28" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_6">
            <blockpin signalname="XLXN_28" name="I0" />
            <blockpin signalname="XLXN_27" name="I1" />
            <blockpin signalname="XLXN_26" name="I2" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_7">
            <blockpin signalname="XLXN_22" name="I0" />
            <blockpin signalname="XLXN_21" name="I1" />
            <blockpin signalname="XLXN_25" name="I2" />
            <blockpin signalname="XLXN_27" name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_8">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="XLXN_12" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_22" name="O" />
        </block>
        <block symbolname="xor3" name="XLXI_9">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_10">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_15" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_11">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_12">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_13">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="2784" y="1072" name="XLXI_6" orien="R0" />
        <instance x="2176" y="1120" name="XLXI_7" orien="R0" />
        <instance x="1504" y="608" name="XLXI_1" orien="R0" />
        <branch name="B">
            <wire x2="368" y1="256" y2="256" x1="320" />
            <wire x2="368" y1="256" y2="816" x1="368" />
            <wire x2="368" y1="816" y2="1120" x1="368" />
            <wire x2="912" y1="1120" y2="1120" x1="368" />
            <wire x2="944" y1="816" y2="816" x1="368" />
            <wire x2="320" y1="256" y2="272" x1="320" />
            <wire x2="368" y1="192" y2="256" x1="368" />
        </branch>
        <branch name="D">
            <wire x2="624" y1="272" y2="272" x1="576" />
            <wire x2="624" y1="272" y2="720" x1="624" />
            <wire x2="928" y1="720" y2="720" x1="624" />
            <wire x2="576" y1="272" y2="304" x1="576" />
            <wire x2="624" y1="224" y2="272" x1="624" />
        </branch>
        <instance x="160" y="272" name="XLXI_10" orien="R90" />
        <instance x="288" y="272" name="XLXI_11" orien="R90" />
        <instance x="416" y="272" name="XLXI_12" orien="R90" />
        <branch name="C">
            <wire x2="496" y1="256" y2="256" x1="448" />
            <wire x2="496" y1="256" y2="592" x1="496" />
            <wire x2="496" y1="592" y2="1872" x1="496" />
            <wire x2="1568" y1="1872" y2="1872" x1="496" />
            <wire x2="704" y1="592" y2="592" x1="496" />
            <wire x2="704" y1="592" y2="656" x1="704" />
            <wire x2="928" y1="656" y2="656" x1="704" />
            <wire x2="448" y1="256" y2="272" x1="448" />
            <wire x2="496" y1="192" y2="256" x1="496" />
        </branch>
        <instance x="544" y="304" name="XLXI_13" orien="R90" />
        <instance x="1568" y="1936" name="XLXI_5" orien="R0" />
        <instance x="1536" y="1264" name="XLXI_4" orien="R0" />
        <instance x="912" y="1184" name="XLXI_2" orien="R0" />
        <instance x="928" y="1632" name="XLXI_8" orien="R0" />
        <branch name="XLXN_9">
            <wire x2="576" y1="528" y2="880" x1="576" />
            <wire x2="576" y1="880" y2="1808" x1="576" />
            <wire x2="1568" y1="1808" y2="1808" x1="576" />
            <wire x2="944" y1="880" y2="880" x1="576" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="320" y1="496" y2="1200" x1="320" />
            <wire x2="320" y1="1200" y2="1568" x1="320" />
            <wire x2="928" y1="1568" y2="1568" x1="320" />
            <wire x2="1536" y1="1200" y2="1200" x1="320" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="448" y1="496" y2="1504" x1="448" />
            <wire x2="928" y1="1504" y2="1504" x1="448" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="192" y1="496" y2="1056" x1="192" />
            <wire x2="912" y1="1056" y2="1056" x1="192" />
        </branch>
        <instance x="928" y="784" name="XLXI_9" orien="R0" />
        <instance x="944" y="944" name="XLXI_3" orien="R0" />
        <branch name="A">
            <wire x2="240" y1="256" y2="256" x1="192" />
            <wire x2="240" y1="256" y2="528" x1="240" />
            <wire x2="240" y1="528" y2="576" x1="240" />
            <wire x2="240" y1="576" y2="720" x1="240" />
            <wire x2="240" y1="720" y2="1440" x1="240" />
            <wire x2="928" y1="1440" y2="1440" x1="240" />
            <wire x2="928" y1="576" y2="576" x1="240" />
            <wire x2="928" y1="576" y2="592" x1="928" />
            <wire x2="192" y1="256" y2="272" x1="192" />
            <wire x2="240" y1="192" y2="256" x1="240" />
        </branch>
        <branch name="XLXN_19">
            <wire x2="1344" y1="656" y2="656" x1="1184" />
            <wire x2="1344" y1="480" y2="656" x1="1344" />
            <wire x2="1504" y1="480" y2="480" x1="1344" />
        </branch>
        <branch name="XLXN_21">
            <wire x2="1984" y1="1168" y2="1168" x1="1792" />
            <wire x2="1984" y1="992" y2="1168" x1="1984" />
            <wire x2="2176" y1="992" y2="992" x1="1984" />
        </branch>
        <branch name="XLXN_22">
            <wire x2="2176" y1="1504" y2="1504" x1="1184" />
            <wire x2="2176" y1="1056" y2="1504" x1="2176" />
        </branch>
        <branch name="XLXN_23">
            <wire x2="1344" y1="1088" y2="1088" x1="1168" />
            <wire x2="1344" y1="1088" y2="1136" x1="1344" />
            <wire x2="1536" y1="1136" y2="1136" x1="1344" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="1296" y1="848" y2="848" x1="1200" />
            <wire x2="1504" y1="848" y2="848" x1="1296" />
            <wire x2="2176" y1="848" y2="848" x1="1504" />
            <wire x2="2176" y1="848" y2="928" x1="2176" />
            <wire x2="1504" y1="544" y2="544" x1="1440" />
            <wire x2="1440" y1="544" y2="624" x1="1440" />
            <wire x2="1504" y1="624" y2="624" x1="1440" />
            <wire x2="1504" y1="624" y2="848" x1="1504" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="2784" y1="512" y2="512" x1="1760" />
            <wire x2="2784" y1="512" y2="880" x1="2784" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="2608" y1="992" y2="992" x1="2432" />
            <wire x2="2608" y1="944" y2="992" x1="2608" />
            <wire x2="2784" y1="944" y2="944" x1="2608" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="2784" y1="1840" y2="1840" x1="1824" />
            <wire x2="2784" y1="1008" y2="1840" x1="2784" />
        </branch>
        <iomarker fontsize="28" x="240" y="192" name="A" orien="R270" />
        <iomarker fontsize="28" x="368" y="192" name="B" orien="R270" />
        <iomarker fontsize="28" x="496" y="192" name="C" orien="R270" />
        <iomarker fontsize="28" x="624" y="224" name="D" orien="R270" />
        <branch name="Z">
            <wire x2="3072" y1="944" y2="944" x1="3040" />
        </branch>
        <iomarker fontsize="28" x="3072" y="944" name="Z" orien="R0" />
    </sheet>
</drawing>