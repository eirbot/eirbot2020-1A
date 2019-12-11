EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Switching:LM2576T-5 U2
U 1 1 5DDFFFDA
P 6200 3850
F 0 "U2" H 6200 4217 50  0000 C CNN
F 1 "LM2576T-5" H 6200 4126 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220F-5_P3.4x2.06mm_StaggerEven_Lead1.86mm_Vertical" H 6200 3600 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2576.pdf" H 6200 3850 50  0001 C CNN
	1    6200 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C22
U 1 1 5DE01F50
P 8200 4100
F 0 "C22" H 8085 4054 50  0000 R CNN
F 1 "1000u" H 8085 4145 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 8238 3950 50  0001 C CNN
F 3 "~" H 8200 4100 50  0001 C CNN
	1    8200 4100
	-1   0    0    1   
$EndComp
$Comp
L Device:L L2
U 1 1 5DE03C89
P 7700 3950
F 0 "L2" V 7890 3950 50  0000 C CNN
F 1 "100u" V 7799 3950 50  0000 C CNN
F 2 "Inductor_THT:L_Toroid_Vertical_L24.6mm_W15.5mm_P11.44mm_Pulse_KM-4" H 7700 3950 50  0001 C CNN
F 3 "~" H 7700 3950 50  0001 C CNN
	1    7700 3950
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Schottky D2
U 1 1 5DE065A7
P 7200 4100
F 0 "D2" V 7154 4179 50  0000 L CNN
F 1 "D_Schottky" V 7245 4179 50  0000 L CNN
F 2 "Diode_THT:D_DO-27_P12.70mm_Horizontal" H 7200 4100 50  0001 C CNN
F 3 "~" H 7200 4100 50  0001 C CNN
	1    7200 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 3950 7200 3950
Connection ~ 7200 3950
Wire Wire Line
	7200 3950 6700 3950
Wire Wire Line
	7850 3950 8200 3950
$Comp
L power:GND #PWR0101
U 1 1 5DE09AC4
P 7200 4350
F 0 "#PWR0101" H 7200 4100 50  0001 C CNN
F 1 "GND" H 7205 4177 50  0000 C CNN
F 2 "" H 7200 4350 50  0001 C CNN
F 3 "" H 7200 4350 50  0001 C CNN
	1    7200 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5DE0A319
P 8200 4350
F 0 "#PWR0102" H 8200 4100 50  0001 C CNN
F 1 "GND" H 8205 4177 50  0000 C CNN
F 2 "" H 8200 4350 50  0001 C CNN
F 3 "" H 8200 4350 50  0001 C CNN
	1    8200 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4350 8200 4250
Wire Wire Line
	7200 4350 7200 4250
$Comp
L power:GND #PWR0103
U 1 1 5DE0AD54
P 6200 4350
F 0 "#PWR0103" H 6200 4100 50  0001 C CNN
F 1 "GND" H 6205 4177 50  0000 C CNN
F 2 "" H 6200 4350 50  0001 C CNN
F 3 "" H 6200 4350 50  0001 C CNN
	1    6200 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4150 6200 4350
$Comp
L power:GND #PWR0104
U 1 1 5DE0B4A6
P 5700 4350
F 0 "#PWR0104" H 5700 4100 50  0001 C CNN
F 1 "GND" H 5705 4177 50  0000 C CNN
F 2 "" H 5700 4350 50  0001 C CNN
F 3 "" H 5700 4350 50  0001 C CNN
	1    5700 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3750 8200 3750
Wire Wire Line
	8200 3750 8200 3950
Connection ~ 8200 3950
Wire Wire Line
	5700 3750 5200 3750
Wire Wire Line
	5200 3750 5200 3950
Wire Wire Line
	5200 3750 4700 3750
Connection ~ 5200 3750
$Comp
L Device:C C21
U 1 1 5DE0DA4F
P 5200 4100
F 0 "C21" H 5315 4146 50  0000 L CNN
F 1 "100u" H 5315 4055 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 5238 3950 50  0001 C CNN
F 3 "~" H 5200 4100 50  0001 C CNN
	1    5200 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5DE0F4AF
P 5200 4350
F 0 "#PWR0105" H 5200 4100 50  0001 C CNN
F 1 "GND" H 5205 4177 50  0000 C CNN
F 2 "" H 5200 4350 50  0001 C CNN
F 3 "" H 5200 4350 50  0001 C CNN
	1    5200 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3950 5700 4350
Wire Wire Line
	5200 4250 5200 4350
$Comp
L Regulator_Switching:LM2576T-5 U1
U 1 1 5DE22997
P 6200 2100
F 0 "U1" H 6200 2467 50  0000 C CNN
F 1 "LM2576T-5" H 6200 2376 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220F-5_P3.4x2.06mm_StaggerEven_Lead1.86mm_Vertical" H 6200 1850 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2576.pdf" H 6200 2100 50  0001 C CNN
	1    6200 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5DE2299D
P 8200 2350
F 0 "C12" H 8085 2304 50  0000 R CNN
F 1 "1000u" H 8085 2395 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 8238 2200 50  0001 C CNN
F 3 "~" H 8200 2350 50  0001 C CNN
	1    8200 2350
	-1   0    0    1   
$EndComp
$Comp
L Device:L L1
U 1 1 5DE229A3
P 7700 2200
F 0 "L1" V 7890 2200 50  0000 C CNN
F 1 "100u" V 7799 2200 50  0000 C CNN
F 2 "Inductor_THT:L_Toroid_Vertical_L24.6mm_W15.5mm_P11.44mm_Pulse_KM-4" H 7700 2200 50  0001 C CNN
F 3 "~" H 7700 2200 50  0001 C CNN
	1    7700 2200
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Schottky D1
U 1 1 5DE229A9
P 7200 2350
F 0 "D1" V 7154 2429 50  0000 L CNN
F 1 "D_Schottky" V 7245 2429 50  0000 L CNN
F 2 "Diode_THT:D_DO-27_P12.70mm_Horizontal" H 7200 2350 50  0001 C CNN
F 3 "~" H 7200 2350 50  0001 C CNN
	1    7200 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 2200 7200 2200
Connection ~ 7200 2200
Wire Wire Line
	7200 2200 6700 2200
Wire Wire Line
	7850 2200 8200 2200
$Comp
L power:GND #PWR0106
U 1 1 5DE229B3
P 7200 2600
F 0 "#PWR0106" H 7200 2350 50  0001 C CNN
F 1 "GND" H 7205 2427 50  0000 C CNN
F 2 "" H 7200 2600 50  0001 C CNN
F 3 "" H 7200 2600 50  0001 C CNN
	1    7200 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5DE229B9
P 8200 2600
F 0 "#PWR0107" H 8200 2350 50  0001 C CNN
F 1 "GND" H 8205 2427 50  0000 C CNN
F 2 "" H 8200 2600 50  0001 C CNN
F 3 "" H 8200 2600 50  0001 C CNN
	1    8200 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 2600 8200 2500
Wire Wire Line
	7200 2600 7200 2500
$Comp
L power:GND #PWR0108
U 1 1 5DE229C1
P 6200 2600
F 0 "#PWR0108" H 6200 2350 50  0001 C CNN
F 1 "GND" H 6205 2427 50  0000 C CNN
F 2 "" H 6200 2600 50  0001 C CNN
F 3 "" H 6200 2600 50  0001 C CNN
	1    6200 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2400 6200 2600
$Comp
L power:GND #PWR0109
U 1 1 5DE229C8
P 5700 2600
F 0 "#PWR0109" H 5700 2350 50  0001 C CNN
F 1 "GND" H 5705 2427 50  0000 C CNN
F 2 "" H 5700 2600 50  0001 C CNN
F 3 "" H 5700 2600 50  0001 C CNN
	1    5700 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2000 7050 2000
Wire Wire Line
	8200 2000 8200 2200
Connection ~ 8200 2200
Wire Wire Line
	5700 2000 5200 2000
Wire Wire Line
	5200 2000 5200 2200
Connection ~ 5200 2000
$Comp
L Device:C C11
U 1 1 5DE229D6
P 5200 2350
F 0 "C11" H 5315 2396 50  0000 L CNN
F 1 "100u" H 5315 2305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 5238 2200 50  0001 C CNN
F 3 "~" H 5200 2350 50  0001 C CNN
	1    5200 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5DE229DC
P 5200 2600
F 0 "#PWR0110" H 5200 2350 50  0001 C CNN
F 1 "GND" H 5205 2427 50  0000 C CNN
F 2 "" H 5200 2600 50  0001 C CNN
F 3 "" H 5200 2600 50  0001 C CNN
	1    5200 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2200 5700 2600
Wire Wire Line
	5200 2500 5200 2600
$Comp
L Regulator_Switching:LM2576T-5 U3
U 1 1 5DE26275
P 5500 5600
F 0 "U3" H 5500 5967 50  0000 C CNN
F 1 "LM2576T-5" H 5500 5876 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220F-5_P3.4x2.06mm_StaggerEven_Lead1.86mm_Vertical" H 5500 5350 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2576.pdf" H 5500 5600 50  0001 C CNN
	1    5500 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C32
U 1 1 5DE2627B
P 7500 5850
F 0 "C32" H 7385 5804 50  0000 R CNN
F 1 "1000u" H 7385 5895 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 7538 5700 50  0001 C CNN
F 3 "~" H 7500 5850 50  0001 C CNN
	1    7500 5850
	-1   0    0    1   
$EndComp
$Comp
L Device:L L3
U 1 1 5DE26281
P 7000 5700
F 0 "L3" V 7190 5700 50  0000 C CNN
F 1 "100u" V 7099 5700 50  0000 C CNN
F 2 "Inductor_THT:L_Toroid_Vertical_L24.6mm_W15.5mm_P11.44mm_Pulse_KM-4" H 7000 5700 50  0001 C CNN
F 3 "~" H 7000 5700 50  0001 C CNN
	1    7000 5700
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Schottky D3
U 1 1 5DE26287
P 6500 5850
F 0 "D3" V 6454 5929 50  0000 L CNN
F 1 "D_Schottky" V 6545 5929 50  0000 L CNN
F 2 "Diode_THT:D_DO-27_P12.70mm_Horizontal" H 6500 5850 50  0001 C CNN
F 3 "~" H 6500 5850 50  0001 C CNN
	1    6500 5850
	0    1    1    0   
$EndComp
Wire Wire Line
	6850 5700 6500 5700
Connection ~ 6500 5700
Wire Wire Line
	6500 5700 6000 5700
Wire Wire Line
	7150 5700 7500 5700
$Comp
L power:GND #PWR0111
U 1 1 5DE26291
P 6500 6100
F 0 "#PWR0111" H 6500 5850 50  0001 C CNN
F 1 "GND" H 6505 5927 50  0000 C CNN
F 2 "" H 6500 6100 50  0001 C CNN
F 3 "" H 6500 6100 50  0001 C CNN
	1    6500 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5DE26297
P 7500 6100
F 0 "#PWR0112" H 7500 5850 50  0001 C CNN
F 1 "GND" H 7505 5927 50  0000 C CNN
F 2 "" H 7500 6100 50  0001 C CNN
F 3 "" H 7500 6100 50  0001 C CNN
	1    7500 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 6100 7500 6000
Wire Wire Line
	6500 6100 6500 6000
$Comp
L power:GND #PWR0113
U 1 1 5DE2629F
P 5500 6100
F 0 "#PWR0113" H 5500 5850 50  0001 C CNN
F 1 "GND" H 5505 5927 50  0000 C CNN
F 2 "" H 5500 6100 50  0001 C CNN
F 3 "" H 5500 6100 50  0001 C CNN
	1    5500 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5900 5500 6100
$Comp
L power:GND #PWR0114
U 1 1 5DE262A6
P 5000 6100
F 0 "#PWR0114" H 5000 5850 50  0001 C CNN
F 1 "GND" H 5005 5927 50  0000 C CNN
F 2 "" H 5000 6100 50  0001 C CNN
F 3 "" H 5000 6100 50  0001 C CNN
	1    5000 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 5500 7500 5500
Wire Wire Line
	7500 5500 7500 5700
Connection ~ 7500 5700
Wire Wire Line
	5000 5500 4500 5500
Wire Wire Line
	4500 5500 4500 5700
Connection ~ 4500 5500
$Comp
L Device:C C31
U 1 1 5DE262B4
P 4500 5850
F 0 "C31" H 4615 5896 50  0000 L CNN
F 1 "100u" H 4615 5805 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 4538 5700 50  0001 C CNN
F 3 "~" H 4500 5850 50  0001 C CNN
	1    4500 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5DE262BA
P 4500 6100
F 0 "#PWR0115" H 4500 5850 50  0001 C CNN
F 1 "GND" H 4505 5927 50  0000 C CNN
F 2 "" H 4500 6100 50  0001 C CNN
F 3 "" H 4500 6100 50  0001 C CNN
	1    4500 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5700 5000 6100
Wire Wire Line
	4500 6000 4500 6100
Text Notes 9350 5700 0    50   ~ 0
5V logique
Text Notes 10150 4000 0    50   ~ 0
5V puissance
Text Notes 10000 2300 0    50   ~ 0
12V puissance
Text Notes 850  1700 0    50   ~ 0
BAT\n
$Comp
L power:GND #PWR0119
U 1 1 5DE0F4B5
P 2100 1200
F 0 "#PWR0119" H 2100 950 50  0001 C CNN
F 1 "GND" H 2105 1027 50  0000 C CNN
F 2 "" H 2100 1200 50  0001 C CNN
F 3 "" H 2100 1200 50  0001 C CNN
	1    2100 1200
	1    0    0    -1  
$EndComp
Text Notes 2950 1700 0    50   ~ 0
arret urgence NC\n
Wire Wire Line
	1500 2000 1500 1700
Wire Wire Line
	2450 5500 2450 2000
Wire Wire Line
	2450 5500 4500 5500
$Comp
L Connector:Conn_01x02_Male J40
U 1 1 5DE0DFE5
P 1300 1600
F 0 "J40" H 1408 1781 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1408 1690 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1300 1600 50  0001 C CNN
F 3 "~" H 1300 1600 50  0001 C CNN
	1    1300 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1200 2100 950 
Wire Wire Line
	2100 950  1500 950 
Wire Wire Line
	1500 950  1500 1600
Text Notes 1750 2200 0    50   ~ 0
arret general
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DE53A18
P 2100 950
F 0 "#FLG0101" H 2100 1025 50  0001 C CNN
F 1 "PWR_FLAG" H 2100 1123 50  0000 C CNN
F 2 "" H 2100 950 50  0001 C CNN
F 3 "~" H 2100 950 50  0001 C CNN
	1    2100 950 
	1    0    0    -1  
$EndComp
Connection ~ 2100 950 
$Comp
L Connector:Conn_01x02_Male J32
U 1 1 5DE5EE88
P 8350 5400
F 0 "J32" V 8458 5581 50  0000 C CNN
F 1 "Conn_01x02_Male" H 8458 5490 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 8350 5400 50  0001 C CNN
F 3 "~" H 8350 5400 50  0001 C CNN
	1    8350 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 5700 8250 5600
Wire Wire Line
	7500 5700 8250 5700
$Comp
L Connector:Conn_01x02_Male J31
U 1 1 5DE3B539
P 8750 5400
F 0 "J31" H 8858 5581 50  0000 C CNN
F 1 "Conn_01x02_Male" H 8858 5490 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 8750 5400 50  0001 C CNN
F 3 "~" H 8750 5400 50  0001 C CNN
	1    8750 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	8650 5600 8650 5700
Wire Wire Line
	8650 5700 8250 5700
Connection ~ 8250 5700
$Comp
L power:GND #PWR0116
U 1 1 5DE6D1FD
P 8350 5900
F 0 "#PWR0116" H 8350 5650 50  0001 C CNN
F 1 "GND" H 8355 5727 50  0000 C CNN
F 2 "" H 8350 5900 50  0001 C CNN
F 3 "" H 8350 5900 50  0001 C CNN
	1    8350 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5DE6D612
P 8750 5900
F 0 "#PWR0117" H 8750 5650 50  0001 C CNN
F 1 "GND" H 8755 5727 50  0000 C CNN
F 2 "" H 8750 5900 50  0001 C CNN
F 3 "" H 8750 5900 50  0001 C CNN
	1    8750 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 5900 8750 5600
Wire Wire Line
	8350 5600 8350 5900
$Comp
L Connector:Conn_01x02_Male J43
U 1 1 5DE73A34
P 4150 1350
F 0 "J43" V 4212 1394 50  0000 L CNN
F 1 "Conn_01x02_Male" V 4100 1000 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 4150 1350 50  0001 C CNN
F 3 "~" H 4150 1350 50  0001 C CNN
	1    4150 1350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5DE759C9
P 4150 1550
F 0 "#PWR0118" H 4150 1300 50  0001 C CNN
F 1 "GND" H 4155 1377 50  0000 C CNN
F 2 "" H 4150 1550 50  0001 C CNN
F 3 "" H 4150 1550 50  0001 C CNN
	1    4150 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F41
U 1 1 5DE79EE7
P 4050 1850
F 0 "F41" V 3853 1850 50  0000 C CNN
F 1 "Fuse" V 3944 1850 50  0000 C CNN
F 2 "fusible:fusible_alim" V 3980 1850 50  0001 C CNN
F 3 "~" H 4050 1850 50  0001 C CNN
	1    4050 1850
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J21
U 1 1 5DE9992D
P 9150 3650
F 0 "J21" V 9258 3831 50  0000 C CNN
F 1 "Conn_01x02_Male" H 9258 3740 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 9150 3650 50  0001 C CNN
F 3 "~" H 9150 3650 50  0001 C CNN
	1    9150 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	9050 3950 9050 3850
$Comp
L Connector:Conn_01x02_Male J22
U 1 1 5DE99935
P 9550 3650
F 0 "J22" H 9658 3831 50  0000 C CNN
F 1 "Conn_01x02_Male" H 9658 3740 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 9550 3650 50  0001 C CNN
F 3 "~" H 9550 3650 50  0001 C CNN
	1    9550 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 3850 9450 3950
Wire Wire Line
	9450 3950 9050 3950
Connection ~ 9050 3950
$Comp
L power:GND #PWR0120
U 1 1 5DE9993E
P 9150 4150
F 0 "#PWR0120" H 9150 3900 50  0001 C CNN
F 1 "GND" H 9155 3977 50  0000 C CNN
F 2 "" H 9150 4150 50  0001 C CNN
F 3 "" H 9150 4150 50  0001 C CNN
	1    9150 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5DE99944
P 9550 4150
F 0 "#PWR0121" H 9550 3900 50  0001 C CNN
F 1 "GND" H 9555 3977 50  0000 C CNN
F 2 "" H 9550 4150 50  0001 C CNN
F 3 "" H 9550 4150 50  0001 C CNN
	1    9550 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 4150 9550 3850
Wire Wire Line
	9150 3850 9150 4150
$Comp
L Connector:Conn_01x02_Male J11
U 1 1 5DEA04CC
P 9100 1900
F 0 "J11" V 9208 2081 50  0000 C CNN
F 1 "Conn_01x02_Male" H 9208 1990 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 9100 1900 50  0001 C CNN
F 3 "~" H 9100 1900 50  0001 C CNN
	1    9100 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	9000 2200 9000 2100
$Comp
L Connector:Conn_01x02_Male J12
U 1 1 5DEA04D4
P 9500 1900
F 0 "J12" H 9608 2081 50  0000 C CNN
F 1 "Conn_01x02_Male" H 9608 1990 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 9500 1900 50  0001 C CNN
F 3 "~" H 9500 1900 50  0001 C CNN
	1    9500 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	9400 2100 9400 2200
Wire Wire Line
	9400 2200 9000 2200
Connection ~ 9000 2200
$Comp
L power:GND #PWR0122
U 1 1 5DEA04DD
P 9100 2400
F 0 "#PWR0122" H 9100 2150 50  0001 C CNN
F 1 "GND" H 9105 2227 50  0000 C CNN
F 2 "" H 9100 2400 50  0001 C CNN
F 3 "" H 9100 2400 50  0001 C CNN
	1    9100 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5DEA04E3
P 9500 2400
F 0 "#PWR0123" H 9500 2150 50  0001 C CNN
F 1 "GND" H 9505 2227 50  0000 C CNN
F 2 "" H 9500 2400 50  0001 C CNN
F 3 "" H 9500 2400 50  0001 C CNN
	1    9500 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 2400 9500 2100
Wire Wire Line
	9100 2100 9100 2400
Wire Wire Line
	8200 2200 9000 2200
Wire Wire Line
	8200 3950 9050 3950
$Comp
L Connector:Conn_01x02_Male J42
U 1 1 5DE1629E
P 3150 1800
F 0 "J42" V 3212 1844 50  0000 L CNN
F 1 "Conn_01x02_Male" V 3303 1844 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 3150 1800 50  0001 C CNN
F 3 "~" H 3150 1800 50  0001 C CNN
	1    3150 1800
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J41
U 1 1 5DE5159F
P 2250 1800
F 0 "J41" V 2312 1844 50  0000 L CNN
F 1 "Conn_01x02_Male" V 2403 1844 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 2250 1800 50  0001 C CNN
F 3 "~" H 2250 1800 50  0001 C CNN
	1    2250 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 2000 2450 2000
Connection ~ 2450 2000
Text Notes 3950 1200 0    50   ~ 0
puissance moteurs\n
Wire Wire Line
	2450 2000 3050 2000
$Comp
L Device:Fuse F42
U 1 1 5DEE6FC7
P 4400 2000
F 0 "F42" V 4203 2000 50  0000 C CNN
F 1 "Fuse" V 4294 2000 50  0000 C CNN
F 2 "fusible:fusible_alim" V 4330 2000 50  0001 C CNN
F 3 "~" H 4400 2000 50  0001 C CNN
	1    4400 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 1700 4050 1600
Wire Wire Line
	3150 2000 4050 2000
Wire Wire Line
	1500 2000 2150 2000
Connection ~ 4050 2000
Wire Wire Line
	4050 2000 4250 2000
Wire Wire Line
	4550 2000 4700 2000
Wire Wire Line
	4700 3750 4700 2000
Connection ~ 4700 2000
Wire Wire Line
	4700 2000 5200 2000
$Comp
L Device:R R11
U 1 1 5DEED7D0
P 7200 2000
F 0 "R11" V 6993 2000 50  0000 C CNN
F 1 "4.7k" V 7084 2000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P12.70mm_Horizontal" V 7130 2000 50  0001 C CNN
F 3 "~" H 7200 2000 50  0001 C CNN
	1    7200 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 2000 7400 2000
$Comp
L Device:R R12
U 1 1 5DEEDB25
P 7550 2000
F 0 "R12" V 7343 2000 50  0000 C CNN
F 1 "1k" V 7434 2000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P12.70mm_Horizontal" V 7480 2000 50  0001 C CNN
F 3 "~" H 7550 2000 50  0001 C CNN
	1    7550 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 2000 8200 2000
$Comp
L Connector:Conn_01x02_Male J44
U 1 1 5DEFFDEA
P 3500 1300
F 0 "J44" V 3562 1344 50  0000 L CNN
F 1 "Conn_01x02_Male" V 3400 1100 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 3500 1300 50  0001 C CNN
F 3 "~" H 3500 1300 50  0001 C CNN
	1    3500 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1400 3900 1400
Wire Wire Line
	3900 1400 3900 1600
Wire Wire Line
	3900 1600 4050 1600
Connection ~ 4050 1600
Wire Wire Line
	4050 1600 4050 1550
$Comp
L power:GND #PWR0124
U 1 1 5DF0F3E5
P 3700 1300
F 0 "#PWR0124" H 3700 1050 50  0001 C CNN
F 1 "GND" H 3705 1127 50  0000 C CNN
F 2 "" H 3700 1300 50  0001 C CNN
F 3 "" H 3700 1300 50  0001 C CNN
	1    3700 1300
	-1   0    0    1   
$EndComp
$Comp
L Mechanical:Heatsink HS1
U 1 1 5DF31D2D
P 6200 1600
F 0 "HS1" H 6342 1721 50  0000 L CNN
F 1 "Heatsink" H 6342 1630 50  0000 L CNN
F 2 "" H 6212 1600 50  0001 C CNN
F 3 "~" H 6212 1600 50  0001 C CNN
	1    6200 1600
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Heatsink HS2
U 1 1 5DF33999
P 6150 3400
F 0 "HS2" H 6292 3521 50  0000 L CNN
F 1 "Heatsink" H 6292 3430 50  0000 L CNN
F 2 "" H 6162 3400 50  0001 C CNN
F 3 "~" H 6162 3400 50  0001 C CNN
	1    6150 3400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Heatsink HS3
U 1 1 5DF33D93
P 5700 5150
F 0 "HS3" H 5842 5271 50  0000 L CNN
F 1 "Heatsink" H 5842 5180 50  0000 L CNN
F 2 "" H 5712 5150 50  0001 C CNN
F 3 "~" H 5712 5150 50  0001 C CNN
	1    5700 5150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
