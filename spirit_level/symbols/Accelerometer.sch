<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3e" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_55(15:0)" />
        <signal name="XLXN_56(15:0)" />
        <signal name="SW(3:0)" />
        <signal name="btn_east" />
        <signal name="Clk_50MHz" />
        <signal name="INT1" />
        <signal name="SDA" />
        <signal name="SCL" />
        <signal name="btn_south" />
        <signal name="XLXN_64(10:0)" />
        <signal name="XLXN_65(9:0)" />
        <signal name="XLXN_67" />
        <signal name="XLXN_68(3:0)" />
        <signal name="XLXN_69(3:0)" />
        <signal name="XLXN_70(11:0)" />
        <signal name="VGA_R" />
        <signal name="VGA_G" />
        <signal name="VGA_B" />
        <signal name="VGA_HS" />
        <signal name="VGA_VS" />
        <signal name="XLXN_76(2:0)" />
        <signal name="btn_west" />
        <signal name="SPI_MOSI" />
        <signal name="SPI_SCK" />
        <signal name="DAC_CS" />
        <signal name="DAC_CLR" />
        <signal name="SPI_SS_B" />
        <signal name="AMP_CS" />
        <signal name="AD_CONV" />
        <signal name="SF_CE0" />
        <signal name="FPGA_INIT_B" />
        <signal name="SPI_MISO" />
        <signal name="XLXN_80(12:0)" />
        <signal name="LED(7:0)" />
        <signal name="XLXN_85" />
        <signal name="ROT_A" />
        <signal name="ROT_B" />
        <signal name="XLXN_91" />
        <signal name="XLXN_94(15:0)" />
        <signal name="LCD_E" />
        <signal name="LCD_RS" />
        <signal name="LCD_RW" />
        <signal name="LCD_D(3:0)" />
        <signal name="XLXN_99" />
        <signal name="XLXN_106(15:0)" />
        <signal name="XLXN_107" />
        <signal name="XLXN_108" />
        <signal name="XLXN_110(15:0)" />
        <signal name="XLXN_111" />
        <signal name="XLXN_112" />
        <signal name="XLXN_113" />
        <signal name="XLXN_114" />
        <signal name="XLXN_115(3:0)" />
        <signal name="XLXN_117" />
        <signal name="XLXN_118" />
        <signal name="XLXN_119" />
        <signal name="XLXN_120" />
        <signal name="XLXN_121(3:0)" />
        <port polarity="Input" name="SW(3:0)" />
        <port polarity="Input" name="btn_east" />
        <port polarity="Input" name="Clk_50MHz" />
        <port polarity="Input" name="INT1" />
        <port polarity="BiDirectional" name="SDA" />
        <port polarity="BiDirectional" name="SCL" />
        <port polarity="Input" name="btn_south" />
        <port polarity="Output" name="VGA_R" />
        <port polarity="Output" name="VGA_G" />
        <port polarity="Output" name="VGA_B" />
        <port polarity="Output" name="VGA_HS" />
        <port polarity="Output" name="VGA_VS" />
        <port polarity="Input" name="btn_west" />
        <port polarity="Output" name="SPI_MOSI" />
        <port polarity="Output" name="SPI_SCK" />
        <port polarity="Output" name="DAC_CS" />
        <port polarity="Output" name="DAC_CLR" />
        <port polarity="Output" name="SPI_SS_B" />
        <port polarity="Output" name="AMP_CS" />
        <port polarity="Output" name="AD_CONV" />
        <port polarity="Output" name="SF_CE0" />
        <port polarity="Output" name="FPGA_INIT_B" />
        <port polarity="Input" name="SPI_MISO" />
        <port polarity="Output" name="LED(7:0)" />
        <port polarity="Input" name="ROT_A" />
        <port polarity="Input" name="ROT_B" />
        <port polarity="Output" name="LCD_E" />
        <port polarity="Output" name="LCD_RS" />
        <port polarity="Output" name="LCD_RW" />
        <port polarity="BiDirectional" name="LCD_D(3:0)" />
        <blockdef name="AccelADXL345">
            <timestamp>2017-2-6T15:4:38</timestamp>
            <rect width="288" x="32" y="-448" height="512" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="320" y1="-288" y2="-288" x1="384" />
            <rect width="64" x="320" y="-236" height="24" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <rect width="64" x="320" y="-172" height="24" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <rect width="64" x="320" y="-108" height="24" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
            <line x2="384" y1="32" y2="32" x1="320" />
            <line x2="-32" y1="32" y2="32" x1="32" />
            <line x2="-32" y1="-32" y2="-32" x1="32" />
            <rect width="64" x="-32" y="-428" height="24" />
            <line x2="-32" y1="-416" y2="-416" x1="32" />
        </blockdef>
        <blockdef name="VGA_800x600">
            <timestamp>2019-4-4T20:23:46</timestamp>
            <rect width="256" x="64" y="-448" height="448" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <rect width="64" x="320" y="-108" height="24" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <rect width="64" x="320" y="-44" height="24" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <blockdef name="DACWrite">
            <timestamp>2019-4-15T12:59:33</timestamp>
            <line x2="0" y1="-544" y2="-544" x1="64" />
            <rect width="64" x="0" y="-492" height="24" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <rect width="64" x="0" y="-428" height="24" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <rect width="64" x="0" y="-364" height="24" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="448" y1="-224" y2="-224" x1="384" />
            <line x2="448" y1="-160" y2="-160" x1="384" />
            <line x2="448" y1="-96" y2="-96" x1="384" />
            <line x2="448" y1="-32" y2="-32" x1="384" />
            <line x2="448" y1="32" y2="32" x1="384" />
            <line x2="448" y1="96" y2="96" x1="384" />
            <line x2="448" y1="-544" y2="-544" x1="384" />
            <line x2="448" y1="-416" y2="-416" x1="384" />
            <line x2="384" y1="-480" y2="-480" x1="448" />
            <line x2="448" y1="-352" y2="-352" x1="384" />
            <line x2="448" y1="-288" y2="-288" x1="384" />
            <line x2="0" y1="32" y2="32" x1="64" />
            <rect width="320" x="64" y="-576" height="760" />
            <line x2="0" y1="96" y2="96" x1="64" />
            <line x2="0" y1="160" y2="160" x1="64" />
        </blockdef>
        <blockdef name="SquarePOS_800x600">
            <timestamp>2019-4-15T13:8:6</timestamp>
            <rect width="256" x="64" y="-384" height="384" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <rect width="64" x="0" y="-236" height="24" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <rect width="64" x="0" y="-172" height="24" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <rect width="64" x="0" y="-108" height="24" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <rect width="64" x="320" y="-364" height="24" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <rect width="64" x="320" y="-44" height="24" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <blockdef name="ErrLevel_LEDS">
            <timestamp>2019-4-16T8:40:36</timestamp>
            <rect width="256" x="64" y="-64" height="64" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <rect width="64" x="320" y="-44" height="24" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <blockdef name="RotaryEnc">
            <timestamp>2019-4-25T10:53:20</timestamp>
            <rect width="256" x="64" y="-256" height="192" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-160" y2="-160" x1="64" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="FSM_BEEP">
            <timestamp>2019-4-25T12:27:4</timestamp>
            <rect width="256" x="64" y="-320" height="320" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-208" y2="-208" x1="64" />
            <line x2="0" y1="-128" y2="-128" x1="64" />
            <rect width="64" x="0" y="-60" height="24" />
            <line x2="0" y1="-48" y2="-48" x1="64" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <rect width="64" x="320" y="-236" height="24" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <rect width="64" x="320" y="-172" height="24" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <rect width="64" x="320" y="-108" height="24" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <rect width="64" x="320" y="-44" height="24" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <blockdef name="LCD1x64">
            <timestamp>2019-4-25T12:16:49</timestamp>
            <line x2="416" y1="-288" y2="-288" x1="352" />
            <line x2="0" y1="-32" y2="-32" x1="64" />
            <line x2="416" y1="-224" y2="-224" x1="352" />
            <line x2="416" y1="-160" y2="-160" x1="352" />
            <rect width="64" x="352" y="-108" height="24" />
            <line x2="416" y1="-96" y2="-96" x1="352" />
            <line x2="416" y1="-32" y2="-32" x1="352" />
            <rect width="288" x="64" y="-320" height="320" />
            <rect width="64" x="0" y="-300" height="24" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <rect width="64" x="0" y="-236" height="24" />
            <line x2="0" y1="-224" y2="-224" x1="64" />
            <line x2="0" y1="-96" y2="-96" x1="64" />
        </blockdef>
        <block symbolname="AccelADXL345" name="XLXI_8">
            <blockpin signalname="SDA" name="SDA" />
            <blockpin signalname="SCL" name="SCL" />
            <blockpin signalname="INT1" name="INT1" />
            <blockpin signalname="XLXN_55(15:0)" name="X(15:0)" />
            <blockpin signalname="XLXN_56(15:0)" name="Y(15:0)" />
            <blockpin name="Z(15:0)" />
            <blockpin name="NewData" />
            <blockpin name="I2C_NACK" />
            <blockpin signalname="Clk_50MHz" name="Clk_50MHz" />
            <blockpin signalname="btn_east" name="Reset" />
            <blockpin signalname="SW(3:0)" name="DataRate(3:0)" />
        </block>
        <block symbolname="VGA_800x600" name="XLXI_10">
            <blockpin signalname="Clk_50MHz" name="CLK_50MHz" />
            <blockpin signalname="XLXN_76(2:0)" name="RGB(2:0)" />
            <blockpin signalname="VGA_R" name="VGA_R" />
            <blockpin signalname="VGA_G" name="VGA_G" />
            <blockpin signalname="VGA_B" name="VGA_B" />
            <blockpin signalname="VGA_HS" name="VGA_HS" />
            <blockpin signalname="VGA_VS" name="VGA_VS" />
            <blockpin signalname="XLXN_64(10:0)" name="PIX_X(10:0)" />
            <blockpin signalname="XLXN_65(9:0)" name="PIX_Y(9:0)" />
        </block>
        <block symbolname="DACWrite" name="XLXI_11">
            <blockpin signalname="btn_west" name="Reset" />
            <blockpin signalname="XLXN_67" name="Start" />
            <blockpin signalname="SPI_MISO" name="SPI_MISO" />
            <blockpin signalname="XLXN_68(3:0)" name="Cmd(3:0)" />
            <blockpin signalname="XLXN_69(3:0)" name="Addr(3:0)" />
            <blockpin signalname="XLXN_70(11:0)" name="DATA(11:0)" />
            <blockpin signalname="DAC_CLR" name="DAC_CLR" />
            <blockpin signalname="DAC_CS" name="DAC_CS" />
            <blockpin signalname="SPI_MOSI" name="SPI_MOSI" />
            <blockpin signalname="SPI_SCK" name="SPI_SCK" />
            <blockpin signalname="SPI_SS_B" name="SPI_SS_B" />
            <blockpin signalname="AMP_CS" name="AMP_CS" />
            <blockpin signalname="AD_CONV" name="AD_CONV" />
            <blockpin signalname="SF_CE0" name="SF_CE0" />
            <blockpin signalname="FPGA_INIT_B" name="FPGA_INIT_B" />
            <blockpin name="Busy" />
            <blockpin signalname="Clk_50MHz" name="Clk_50MHz" />
            <blockpin signalname="Clk_50MHz" name="Clk_Sys" />
        </block>
        <block symbolname="SquarePOS_800x600" name="XLXI_13">
            <blockpin signalname="btn_south" name="SetOffset" />
            <blockpin signalname="Clk_50MHz" name="Clk_50MHz" />
            <blockpin signalname="XLXN_64(10:0)" name="PIX_X(10:0)" />
            <blockpin signalname="XLXN_65(9:0)" name="PIX_Y(9:0)" />
            <blockpin signalname="XLXN_55(15:0)" name="X(15:0)" />
            <blockpin signalname="XLXN_56(15:0)" name="Y(15:0)" />
            <blockpin signalname="XLXN_80(12:0)" name="Error(12:0)" />
            <blockpin signalname="XLXN_76(2:0)" name="RGB(2:0)" />
        </block>
        <block symbolname="ErrLevel_LEDS" name="XLXI_14">
            <blockpin signalname="XLXN_80(12:0)" name="Error(12:0)" />
            <blockpin signalname="LED(7:0)" name="LED(7:0)" />
        </block>
        <block symbolname="RotaryEnc" name="XLXI_15">
            <blockpin signalname="ROT_A" name="ROT_A" />
            <blockpin signalname="ROT_B" name="ROT_B" />
            <blockpin signalname="XLXN_91" name="RotL" />
            <blockpin signalname="XLXN_85" name="RotR" />
            <blockpin signalname="Clk_50MHz" name="Clk" />
        </block>
        <block symbolname="FSM_BEEP" name="XLXI_16">
            <blockpin signalname="XLXN_85" name="VolUp" />
            <blockpin signalname="XLXN_91" name="VolDown" />
            <blockpin signalname="Clk_50MHz" name="Clk_50MHz" />
            <blockpin signalname="XLXN_80(12:0)" name="Error(12:0)" />
            <blockpin signalname="XLXN_67" name="Start" />
            <blockpin signalname="XLXN_68(3:0)" name="Cmd(3:0)" />
            <blockpin signalname="XLXN_69(3:0)" name="Addr(3:0)" />
            <blockpin signalname="XLXN_70(11:0)" name="Data(11:0)" />
            <blockpin signalname="XLXN_94(15:0)" name="Blank(15:0)" />
        </block>
        <block symbolname="LCD1x64" name="XLXI_17">
            <blockpin signalname="Clk_50MHz" name="Clk_50MHz" />
            <blockpin signalname="btn_west" name="Reset" />
            <blockpin name="Line(63:0)" />
            <blockpin signalname="XLXN_94(15:0)" name="Blank(15:0)" />
            <blockpin signalname="LCD_D(3:0)" name="LCD_D(3:0)" />
            <blockpin signalname="LCD_E" name="LCD_E" />
            <blockpin signalname="LCD_RW" name="LCD_RW" />
            <blockpin signalname="LCD_RS" name="LCD_RS" />
            <blockpin name="SF_CE" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="576" y="912" name="XLXI_8" orien="R0">
        </instance>
        <instance x="2512" y="880" name="XLXI_10" orien="R0">
        </instance>
        <instance x="1536" y="1680" name="XLXI_13" orien="R0">
        </instance>
        <branch name="XLXN_55(15:0)">
            <wire x2="1200" y1="688" y2="688" x1="960" />
            <wire x2="1200" y1="688" y2="1584" x1="1200" />
            <wire x2="1536" y1="1584" y2="1584" x1="1200" />
        </branch>
        <branch name="XLXN_56(15:0)">
            <wire x2="1152" y1="752" y2="752" x1="960" />
            <wire x2="1152" y1="752" y2="1648" x1="1152" />
            <wire x2="1536" y1="1648" y2="1648" x1="1152" />
        </branch>
        <branch name="SW(3:0)">
            <wire x2="544" y1="496" y2="496" x1="432" />
        </branch>
        <branch name="btn_east">
            <wire x2="544" y1="880" y2="880" x1="432" />
        </branch>
        <branch name="INT1">
            <wire x2="1040" y1="624" y2="624" x1="960" />
        </branch>
        <branch name="SDA">
            <wire x2="1040" y1="496" y2="496" x1="960" />
        </branch>
        <branch name="SCL">
            <wire x2="1040" y1="560" y2="560" x1="960" />
        </branch>
        <branch name="btn_south">
            <wire x2="1536" y1="1328" y2="1328" x1="1488" />
        </branch>
        <branch name="XLXN_64(10:0)">
            <wire x2="1280" y1="912" y2="1456" x1="1280" />
            <wire x2="1536" y1="1456" y2="1456" x1="1280" />
            <wire x2="3008" y1="912" y2="912" x1="1280" />
            <wire x2="3008" y1="784" y2="784" x1="2896" />
            <wire x2="3008" y1="784" y2="912" x1="3008" />
        </branch>
        <branch name="XLXN_65(9:0)">
            <wire x2="1312" y1="928" y2="1520" x1="1312" />
            <wire x2="1536" y1="1520" y2="1520" x1="1312" />
            <wire x2="2992" y1="928" y2="928" x1="1312" />
            <wire x2="2992" y1="848" y2="848" x1="2896" />
            <wire x2="2992" y1="848" y2="928" x1="2992" />
        </branch>
        <branch name="XLXN_67">
            <wire x2="2080" y1="2048" y2="2048" x1="1872" />
            <wire x2="2080" y1="1104" y2="2048" x1="2080" />
            <wire x2="2496" y1="1104" y2="1104" x1="2080" />
        </branch>
        <branch name="XLXN_68(3:0)">
            <wire x2="2144" y1="2112" y2="2112" x1="1872" />
            <wire x2="2496" y1="1168" y2="1168" x1="2144" />
            <wire x2="2144" y1="1168" y2="2112" x1="2144" />
        </branch>
        <branch name="XLXN_69(3:0)">
            <wire x2="2208" y1="2176" y2="2176" x1="1872" />
            <wire x2="2208" y1="1232" y2="2176" x1="2208" />
            <wire x2="2496" y1="1232" y2="1232" x1="2208" />
        </branch>
        <branch name="XLXN_70(11:0)">
            <wire x2="2256" y1="2240" y2="2240" x1="1872" />
            <wire x2="2256" y1="1296" y2="2240" x1="2256" />
            <wire x2="2496" y1="1296" y2="1296" x1="2256" />
        </branch>
        <branch name="VGA_R">
            <wire x2="2960" y1="464" y2="464" x1="2896" />
        </branch>
        <branch name="VGA_G">
            <wire x2="2960" y1="528" y2="528" x1="2896" />
        </branch>
        <branch name="VGA_B">
            <wire x2="2960" y1="592" y2="592" x1="2896" />
        </branch>
        <branch name="VGA_HS">
            <wire x2="2960" y1="656" y2="656" x1="2896" />
        </branch>
        <branch name="VGA_VS">
            <wire x2="2960" y1="720" y2="720" x1="2896" />
        </branch>
        <branch name="XLXN_76(2:0)">
            <wire x2="2048" y1="1648" y2="1648" x1="1920" />
            <wire x2="2048" y1="848" y2="1648" x1="2048" />
            <wire x2="2512" y1="848" y2="848" x1="2048" />
        </branch>
        <instance x="2496" y="1648" name="XLXI_11" orien="R0">
        </instance>
        <branch name="SPI_MOSI">
            <wire x2="3040" y1="1104" y2="1104" x1="2944" />
        </branch>
        <branch name="SPI_SCK">
            <wire x2="3040" y1="1232" y2="1232" x1="2944" />
        </branch>
        <branch name="DAC_CS">
            <wire x2="3040" y1="1296" y2="1296" x1="2944" />
        </branch>
        <branch name="DAC_CLR">
            <wire x2="3040" y1="1360" y2="1360" x1="2944" />
        </branch>
        <branch name="SPI_SS_B">
            <wire x2="3040" y1="1424" y2="1424" x1="2944" />
        </branch>
        <branch name="AMP_CS">
            <wire x2="3040" y1="1488" y2="1488" x1="2944" />
        </branch>
        <branch name="AD_CONV">
            <wire x2="3040" y1="1552" y2="1552" x1="2944" />
        </branch>
        <branch name="SF_CE0">
            <wire x2="3040" y1="1616" y2="1616" x1="2944" />
        </branch>
        <branch name="FPGA_INIT_B">
            <wire x2="3040" y1="1680" y2="1680" x1="2944" />
        </branch>
        <branch name="SPI_MISO">
            <wire x2="3024" y1="1168" y2="1168" x1="2944" />
        </branch>
        <iomarker fontsize="28" x="432" y="496" name="SW(3:0)" orien="R180" />
        <iomarker fontsize="28" x="432" y="880" name="btn_east" orien="R180" />
        <iomarker fontsize="28" x="384" y="1456" name="Clk_50MHz" orien="R180" />
        <iomarker fontsize="28" x="1488" y="1328" name="btn_south" orien="R180" />
        <iomarker fontsize="28" x="1040" y="496" name="SDA" orien="R0" />
        <iomarker fontsize="28" x="1040" y="560" name="SCL" orien="R0" />
        <iomarker fontsize="28" x="1040" y="624" name="INT1" orien="R0" />
        <branch name="LED(7:0)">
            <wire x2="3040" y1="1968" y2="1968" x1="2912" />
        </branch>
        <iomarker fontsize="28" x="3040" y="1680" name="FPGA_INIT_B" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1616" name="SF_CE0" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1552" name="AD_CONV" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1488" name="AMP_CS" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1424" name="SPI_SS_B" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1360" name="DAC_CLR" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1296" name="DAC_CS" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1232" name="SPI_SCK" orien="R0" />
        <iomarker fontsize="28" x="3040" y="1104" name="SPI_MOSI" orien="R0" />
        <iomarker fontsize="28" x="3024" y="1168" name="SPI_MISO" orien="R0" />
        <iomarker fontsize="28" x="2960" y="720" name="VGA_VS" orien="R0" />
        <iomarker fontsize="28" x="2960" y="656" name="VGA_HS" orien="R0" />
        <iomarker fontsize="28" x="2960" y="592" name="VGA_B" orien="R0" />
        <iomarker fontsize="28" x="2960" y="528" name="VGA_G" orien="R0" />
        <iomarker fontsize="28" x="2960" y="464" name="VGA_R" orien="R0" />
        <instance x="2528" y="2000" name="XLXI_14" orien="R0">
        </instance>
        <branch name="XLXN_80(12:0)">
            <wire x2="2000" y1="1856" y2="1856" x1="1408" />
            <wire x2="2000" y1="1856" y2="1968" x1="2000" />
            <wire x2="2528" y1="1968" y2="1968" x1="2000" />
            <wire x2="1408" y1="1856" y2="2288" x1="1408" />
            <wire x2="1488" y1="2288" y2="2288" x1="1408" />
            <wire x2="2000" y1="1328" y2="1328" x1="1920" />
            <wire x2="2000" y1="1328" y2="1856" x1="2000" />
        </branch>
        <iomarker fontsize="28" x="3040" y="1968" name="LED(7:0)" orien="R0" />
        <branch name="XLXN_85">
            <wire x2="1488" y1="2048" y2="2048" x1="832" />
        </branch>
        <branch name="ROT_A">
            <wire x2="448" y1="1984" y2="1984" x1="224" />
        </branch>
        <branch name="ROT_B">
            <wire x2="448" y1="2048" y2="2048" x1="224" />
        </branch>
        <iomarker fontsize="28" x="224" y="1984" name="ROT_A" orien="R180" />
        <iomarker fontsize="28" x="224" y="2048" name="ROT_B" orien="R180" />
        <instance x="1488" y="2336" name="XLXI_16" orien="R0">
        </instance>
        <branch name="LCD_E">
            <wire x2="2960" y1="2240" y2="2240" x1="2944" />
            <wire x2="3040" y1="2240" y2="2240" x1="2960" />
        </branch>
        <branch name="LCD_D(3:0)">
            <wire x2="2960" y1="2432" y2="2432" x1="2944" />
            <wire x2="3040" y1="2432" y2="2432" x1="2960" />
        </branch>
        <instance x="448" y="2208" name="XLXI_15" orien="R0">
        </instance>
        <branch name="XLXN_91">
            <wire x2="1152" y1="1984" y2="1984" x1="832" />
            <wire x2="1152" y1="1984" y2="2128" x1="1152" />
            <wire x2="1488" y1="2128" y2="2128" x1="1152" />
        </branch>
        <branch name="LCD_RW">
            <wire x2="2960" y1="2368" y2="2368" x1="2944" />
            <wire x2="3040" y1="2368" y2="2368" x1="2960" />
        </branch>
        <branch name="LCD_RS">
            <wire x2="2960" y1="2304" y2="2304" x1="2944" />
            <wire x2="3040" y1="2304" y2="2304" x1="2960" />
        </branch>
        <branch name="Clk_50MHz">
            <wire x2="224" y1="192" y2="1136" x1="224" />
            <wire x2="528" y1="1136" y2="1136" x1="224" />
            <wire x2="528" y1="1136" y2="1392" x1="528" />
            <wire x2="1024" y1="1392" y2="1392" x1="528" />
            <wire x2="1536" y1="1392" y2="1392" x1="1024" />
            <wire x2="1024" y1="1392" y2="1632" x1="1024" />
            <wire x2="1024" y1="1632" y2="1744" x1="1024" />
            <wire x2="2400" y1="1744" y2="1744" x1="1024" />
            <wire x2="2496" y1="1744" y2="1744" x1="2400" />
            <wire x2="2400" y1="1744" y2="1808" x1="2400" />
            <wire x2="2496" y1="1808" y2="1808" x1="2400" />
            <wire x2="1024" y1="1744" y2="1856" x1="1024" />
            <wire x2="1296" y1="1856" y2="1856" x1="1024" />
            <wire x2="1296" y1="1856" y2="2208" x1="1296" />
            <wire x2="1488" y1="2208" y2="2208" x1="1296" />
            <wire x2="1024" y1="1856" y2="2496" x1="1024" />
            <wire x2="2528" y1="2496" y2="2496" x1="1024" />
            <wire x2="528" y1="1392" y2="1456" x1="528" />
            <wire x2="1280" y1="192" y2="192" x1="224" />
            <wire x2="1280" y1="192" y2="464" x1="1280" />
            <wire x2="2512" y1="464" y2="464" x1="1280" />
            <wire x2="368" y1="1632" y2="2112" x1="368" />
            <wire x2="448" y1="2112" y2="2112" x1="368" />
            <wire x2="1024" y1="1632" y2="1632" x1="368" />
            <wire x2="528" y1="1456" y2="1456" x1="384" />
            <wire x2="544" y1="944" y2="944" x1="528" />
            <wire x2="528" y1="944" y2="1136" x1="528" />
        </branch>
        <branch name="btn_west">
            <wire x2="2464" y1="1680" y2="1680" x1="2416" />
            <wire x2="2496" y1="1680" y2="1680" x1="2464" />
            <wire x2="2464" y1="1680" y2="2432" x1="2464" />
            <wire x2="2528" y1="2432" y2="2432" x1="2464" />
        </branch>
        <branch name="XLXN_94(15:0)">
            <wire x2="2528" y1="2304" y2="2304" x1="1872" />
        </branch>
        <iomarker fontsize="28" x="2416" y="1680" name="btn_west" orien="R180" />
        <instance x="2528" y="2528" name="XLXI_17" orien="R0">
        </instance>
        <iomarker fontsize="28" x="3040" y="2240" name="LCD_E" orien="R0" />
        <iomarker fontsize="28" x="3040" y="2304" name="LCD_RS" orien="R0" />
        <iomarker fontsize="28" x="3040" y="2368" name="LCD_RW" orien="R0" />
        <iomarker fontsize="28" x="3040" y="2432" name="LCD_D(3:0)" orien="R0" />
    </sheet>
</drawing>