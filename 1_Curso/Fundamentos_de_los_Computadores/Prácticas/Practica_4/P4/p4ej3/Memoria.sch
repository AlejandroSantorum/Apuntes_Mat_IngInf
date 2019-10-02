<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="MARCHA" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="Q3" />
        <signal name="D0" />
        <signal name="D1" />
        <signal name="D2" />
        <signal name="XLXN_10" />
        <signal name="D3" />
        <signal name="CALENTAR" />
        <signal name="READY" />
        <signal name="CAFE" />
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
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="XLXN_42" />
        <signal name="XLXN_43" />
        <port polarity="Input" name="MARCHA" />
        <port polarity="Input" name="Q0" />
        <port polarity="Input" name="Q1" />
        <port polarity="Input" name="Q2" />
        <port polarity="Input" name="Q3" />
        <port polarity="Output" name="D0" />
        <port polarity="Output" name="D1" />
        <port polarity="Output" name="D2" />
        <port polarity="Output" name="D3" />
        <port polarity="Output" name="CALENTAR" />
        <port polarity="Output" name="READY" />
        <port polarity="Output" name="CAFE" />
        <blockdef name="rom32x1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-384" y2="-384" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <rect width="256" x="64" y="-448" height="384" />
        </blockdef>
        <block symbolname="rom32x1" name="XLXI_1">
            <attr value="00FFC000" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="MARCHA" name="A0" />
            <blockpin signalname="Q0" name="A1" />
            <blockpin signalname="Q1" name="A2" />
            <blockpin signalname="Q2" name="A3" />
            <blockpin signalname="Q3" name="A4" />
            <blockpin signalname="D3" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_2">
            <attr value="000000FC" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="MARCHA" name="A0" />
            <blockpin signalname="Q0" name="A1" />
            <blockpin signalname="Q1" name="A2" />
            <blockpin signalname="Q2" name="A3" />
            <blockpin signalname="Q3" name="A4" />
            <blockpin signalname="CALENTAR" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_3">
            <attr value="00000300" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="MARCHA" name="A0" />
            <blockpin signalname="Q0" name="A1" />
            <blockpin signalname="Q1" name="A2" />
            <blockpin signalname="Q2" name="A3" />
            <blockpin signalname="Q3" name="A4" />
            <blockpin signalname="READY" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_4">
            <attr value="03FFFC00" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="MARCHA" name="A0" />
            <blockpin signalname="Q0" name="A1" />
            <blockpin signalname="Q1" name="A2" />
            <blockpin signalname="Q2" name="A3" />
            <blockpin signalname="Q3" name="A4" />
            <blockpin signalname="CAFE" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_5">
            <attr value="00333233" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="MARCHA" name="A0" />
            <blockpin signalname="Q0" name="A1" />
            <blockpin signalname="Q1" name="A2" />
            <blockpin signalname="Q2" name="A3" />
            <blockpin signalname="Q3" name="A4" />
            <blockpin signalname="D0" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_6">
            <attr value="003C3C3C" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="MARCHA" name="A0" />
            <blockpin signalname="Q0" name="A1" />
            <blockpin signalname="Q1" name="A2" />
            <blockpin signalname="Q2" name="A3" />
            <blockpin signalname="Q3" name="A4" />
            <blockpin signalname="D1" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_7">
            <attr value="03C03FC0" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="MARCHA" name="A0" />
            <blockpin signalname="Q0" name="A1" />
            <blockpin signalname="Q1" name="A2" />
            <blockpin signalname="Q2" name="A3" />
            <blockpin signalname="Q3" name="A4" />
            <blockpin signalname="D2" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="368" y="1568" name="XLXI_5" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="0" y="-532" type="instance" />
        </instance>
        <instance x="384" y="2336" name="XLXI_7" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="0" y="-532" type="instance" />
        </instance>
        <instance x="912" y="2624" name="XLXI_1" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="0" y="-532" type="instance" />
        </instance>
        <branch name="MARCHA">
            <wire x2="336" y1="1184" y2="1184" x1="192" />
            <wire x2="368" y1="1184" y2="1184" x1="336" />
            <wire x2="336" y1="1184" y2="1584" x1="336" />
            <wire x2="336" y1="1584" y2="1952" x1="336" />
            <wire x2="384" y1="1952" y2="1952" x1="336" />
            <wire x2="336" y1="1952" y2="2288" x1="336" />
            <wire x2="832" y1="2288" y2="2288" x1="336" />
            <wire x2="720" y1="1584" y2="1584" x1="336" />
            <wire x2="336" y1="112" y2="1184" x1="336" />
            <wire x2="2176" y1="112" y2="112" x1="336" />
            <wire x2="2176" y1="112" y2="576" x1="2176" />
            <wire x2="2176" y1="576" y2="1136" x1="2176" />
            <wire x2="2288" y1="1136" y2="1136" x1="2176" />
            <wire x2="2224" y1="576" y2="576" x1="2176" />
            <wire x2="2224" y1="576" y2="656" x1="2224" />
            <wire x2="2288" y1="656" y2="656" x1="2224" />
            <wire x2="2224" y1="112" y2="112" x1="2176" />
            <wire x2="2224" y1="112" y2="160" x1="2224" />
            <wire x2="2288" y1="160" y2="160" x1="2224" />
            <wire x2="720" y1="1504" y2="1584" x1="720" />
            <wire x2="912" y1="1504" y2="1504" x1="720" />
            <wire x2="912" y1="2240" y2="2240" x1="832" />
            <wire x2="832" y1="2240" y2="2288" x1="832" />
        </branch>
        <branch name="Q0">
            <wire x2="304" y1="1248" y2="1248" x1="192" />
            <wire x2="368" y1="1248" y2="1248" x1="304" />
            <wire x2="304" y1="1248" y2="1632" x1="304" />
            <wire x2="304" y1="1632" y2="2016" x1="304" />
            <wire x2="384" y1="2016" y2="2016" x1="304" />
            <wire x2="304" y1="2016" y2="2304" x1="304" />
            <wire x2="912" y1="2304" y2="2304" x1="304" />
            <wire x2="752" y1="1632" y2="1632" x1="304" />
            <wire x2="304" y1="176" y2="1248" x1="304" />
            <wire x2="2112" y1="176" y2="176" x1="304" />
            <wire x2="2112" y1="176" y2="640" x1="2112" />
            <wire x2="2112" y1="640" y2="1200" x1="2112" />
            <wire x2="2288" y1="1200" y2="1200" x1="2112" />
            <wire x2="2192" y1="640" y2="640" x1="2112" />
            <wire x2="2192" y1="640" y2="720" x1="2192" />
            <wire x2="2288" y1="720" y2="720" x1="2192" />
            <wire x2="2192" y1="176" y2="176" x1="2112" />
            <wire x2="2192" y1="176" y2="224" x1="2192" />
            <wire x2="2288" y1="224" y2="224" x1="2192" />
            <wire x2="912" y1="1568" y2="1568" x1="752" />
            <wire x2="752" y1="1568" y2="1632" x1="752" />
        </branch>
        <branch name="Q1">
            <wire x2="272" y1="1312" y2="1312" x1="192" />
            <wire x2="368" y1="1312" y2="1312" x1="272" />
            <wire x2="272" y1="1312" y2="1696" x1="272" />
            <wire x2="272" y1="1696" y2="2080" x1="272" />
            <wire x2="384" y1="2080" y2="2080" x1="272" />
            <wire x2="272" y1="2080" y2="2368" x1="272" />
            <wire x2="912" y1="2368" y2="2368" x1="272" />
            <wire x2="832" y1="1696" y2="1696" x1="272" />
            <wire x2="272" y1="240" y2="1312" x1="272" />
            <wire x2="2048" y1="240" y2="240" x1="272" />
            <wire x2="2048" y1="240" y2="704" x1="2048" />
            <wire x2="2048" y1="704" y2="1264" x1="2048" />
            <wire x2="2288" y1="1264" y2="1264" x1="2048" />
            <wire x2="2160" y1="704" y2="704" x1="2048" />
            <wire x2="2160" y1="704" y2="784" x1="2160" />
            <wire x2="2288" y1="784" y2="784" x1="2160" />
            <wire x2="2160" y1="240" y2="240" x1="2048" />
            <wire x2="2160" y1="240" y2="288" x1="2160" />
            <wire x2="2288" y1="288" y2="288" x1="2160" />
            <wire x2="832" y1="1632" y2="1696" x1="832" />
            <wire x2="912" y1="1632" y2="1632" x1="832" />
        </branch>
        <branch name="Q2">
            <wire x2="256" y1="1376" y2="1376" x1="192" />
            <wire x2="368" y1="1376" y2="1376" x1="256" />
            <wire x2="256" y1="1376" y2="1744" x1="256" />
            <wire x2="256" y1="1744" y2="2144" x1="256" />
            <wire x2="384" y1="2144" y2="2144" x1="256" />
            <wire x2="256" y1="2144" y2="2432" x1="256" />
            <wire x2="912" y1="2432" y2="2432" x1="256" />
            <wire x2="896" y1="1744" y2="1744" x1="256" />
            <wire x2="256" y1="304" y2="1376" x1="256" />
            <wire x2="1984" y1="304" y2="304" x1="256" />
            <wire x2="1984" y1="304" y2="768" x1="1984" />
            <wire x2="1984" y1="768" y2="1328" x1="1984" />
            <wire x2="2288" y1="1328" y2="1328" x1="1984" />
            <wire x2="2128" y1="768" y2="768" x1="1984" />
            <wire x2="2128" y1="768" y2="848" x1="2128" />
            <wire x2="2288" y1="848" y2="848" x1="2128" />
            <wire x2="2128" y1="304" y2="304" x1="1984" />
            <wire x2="2128" y1="304" y2="352" x1="2128" />
            <wire x2="2288" y1="352" y2="352" x1="2128" />
            <wire x2="896" y1="1696" y2="1744" x1="896" />
            <wire x2="912" y1="1696" y2="1696" x1="896" />
        </branch>
        <branch name="Q3">
            <wire x2="224" y1="1440" y2="1440" x1="192" />
            <wire x2="368" y1="1440" y2="1440" x1="224" />
            <wire x2="224" y1="1440" y2="1760" x1="224" />
            <wire x2="912" y1="1760" y2="1760" x1="224" />
            <wire x2="224" y1="1760" y2="2208" x1="224" />
            <wire x2="384" y1="2208" y2="2208" x1="224" />
            <wire x2="224" y1="2208" y2="2496" x1="224" />
            <wire x2="912" y1="2496" y2="2496" x1="224" />
            <wire x2="224" y1="368" y2="1440" x1="224" />
            <wire x2="1904" y1="368" y2="368" x1="224" />
            <wire x2="1904" y1="368" y2="832" x1="1904" />
            <wire x2="1904" y1="832" y2="1392" x1="1904" />
            <wire x2="2288" y1="1392" y2="1392" x1="1904" />
            <wire x2="2096" y1="832" y2="832" x1="1904" />
            <wire x2="2096" y1="832" y2="912" x1="2096" />
            <wire x2="2288" y1="912" y2="912" x1="2096" />
            <wire x2="2096" y1="368" y2="368" x1="1904" />
            <wire x2="2096" y1="368" y2="416" x1="2096" />
            <wire x2="2288" y1="416" y2="416" x1="2096" />
        </branch>
        <iomarker fontsize="28" x="192" y="1184" name="MARCHA" orien="R180" />
        <iomarker fontsize="28" x="192" y="1312" name="Q1" orien="R180" />
        <iomarker fontsize="28" x="192" y="1376" name="Q2" orien="R180" />
        <iomarker fontsize="28" x="192" y="1440" name="Q3" orien="R180" />
        <iomarker fontsize="28" x="192" y="1248" name="Q0" orien="R180" />
        <instance x="912" y="1888" name="XLXI_6" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="0" y="-532" type="instance" />
        </instance>
        <branch name="D0">
            <wire x2="1792" y1="1184" y2="1184" x1="752" />
            <wire x2="1792" y1="1184" y2="1552" x1="1792" />
            <wire x2="2848" y1="1552" y2="1552" x1="1792" />
        </branch>
        <branch name="D1">
            <wire x2="1296" y1="1504" y2="1680" x1="1296" />
            <wire x2="2864" y1="1680" y2="1680" x1="1296" />
        </branch>
        <branch name="D2">
            <wire x2="2192" y1="1952" y2="1952" x1="768" />
            <wire x2="2192" y1="1824" y2="1952" x1="2192" />
            <wire x2="2848" y1="1824" y2="1824" x1="2192" />
        </branch>
        <branch name="D3">
            <wire x2="2304" y1="2240" y2="2240" x1="1296" />
            <wire x2="2304" y1="1984" y2="2240" x1="2304" />
            <wire x2="2848" y1="1984" y2="1984" x1="2304" />
        </branch>
        <branch name="CALENTAR">
            <wire x2="2752" y1="160" y2="160" x1="2672" />
            <wire x2="2768" y1="112" y2="112" x1="2752" />
            <wire x2="2752" y1="112" y2="160" x1="2752" />
        </branch>
        <branch name="READY">
            <wire x2="2800" y1="656" y2="656" x1="2672" />
            <wire x2="2816" y1="576" y2="576" x1="2800" />
            <wire x2="2800" y1="576" y2="656" x1="2800" />
        </branch>
        <branch name="CAFE">
            <wire x2="2816" y1="1136" y2="1136" x1="2672" />
            <wire x2="2832" y1="1040" y2="1040" x1="2816" />
            <wire x2="2816" y1="1040" y2="1136" x1="2816" />
        </branch>
        <iomarker fontsize="28" x="2768" y="112" name="CALENTAR" orien="R0" />
        <iomarker fontsize="28" x="2816" y="576" name="READY" orien="R0" />
        <iomarker fontsize="28" x="2832" y="1040" name="CAFE" orien="R0" />
        <iomarker fontsize="28" x="2848" y="1552" name="D0" orien="R0" />
        <iomarker fontsize="28" x="2864" y="1680" name="D1" orien="R0" />
        <iomarker fontsize="28" x="2848" y="1824" name="D2" orien="R0" />
        <iomarker fontsize="28" x="2848" y="1984" name="D3" orien="R0" />
        <instance x="2288" y="1520" name="XLXI_4" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="192" y="-298" type="instance" />
        </instance>
        <instance x="2288" y="1040" name="XLXI_3" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="0" y="-532" type="instance" />
        </instance>
        <instance x="2288" y="544" name="XLXI_2" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="0" y="-532" type="instance" />
        </instance>
    </sheet>
</drawing>