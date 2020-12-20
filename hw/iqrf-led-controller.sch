EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "LED Controller"
Date "2020-12-20"
Rev "2.0"
Comp "Roman Ondráček"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Analog_ADC:INA219AxD U1
U 1 1 5FD2C4B0
P 2700 2550
F 0 "U1" H 2700 3131 50  0000 C CNN
F 1 "INA219AxD" H 2700 3040 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3500 2200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina219.pdf" H 3050 2450 50  0001 C CNN
	1    2700 2550
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32D U4
U 1 1 5FD2D175
P 7000 4100
F 0 "U4" H 7000 5681 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 7000 5590 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 7000 2600 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 6700 4150 50  0001 C CNN
	1    7000 4100
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:TR-72DAT U2
U 1 1 5FD2DC48
P 3300 4250
F 0 "U2" H 3300 4931 50  0000 C CNN
F 1 "TR-72DAT" H 3300 4840 50  0000 C CNN
F 2 "RF_Module:IQRF_TRx2DA_KON-SIM-01" H 2300 3800 50  0001 L CNN
F 3 "https://iqrf.org/weben/downloads.php?id=337" H 4300 3700 50  0001 R CNN
	1    3300 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:D_TVS D1
U 1 1 5FD31495
P 1800 1400
F 0 "D1" V 1750 1550 50  0000 C CNN
F 1 "SMAJ12CA-E3/61" V 1850 1850 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 1800 1400 50  0001 C CNN
F 3 "~" H 1800 1400 50  0001 C CNN
	1    1800 1400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5FD6C7DE
P 10000 1150
F 0 "#PWR030" H 10000 900 50  0001 C CNN
F 1 "GND" V 10005 1022 50  0000 R CNN
F 2 "" H 10000 1150 50  0001 C CNN
F 3 "" H 10000 1150 50  0001 C CNN
	1    10000 1150
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR029
U 1 1 5FD6CE48
P 10000 750
F 0 "#PWR029" H 10000 600 50  0001 C CNN
F 1 "+3.3V" V 10015 878 50  0000 L CNN
F 2 "" H 10000 750 50  0001 C CNN
F 3 "" H 10000 750 50  0001 C CNN
	1    10000 750 
	0    -1   -1   0   
$EndComp
Text GLabel 10000 1050 0    50   Output ~ 0
UART0_TX
Text GLabel 10000 950  0    50   Input ~ 0
UART0_RX
Text GLabel 7700 3000 2    50   Output ~ 0
UART0_TX
Text GLabel 7700 3200 2    50   Input ~ 0
UART0_RX
Wire Wire Line
	7600 3000 7700 3000
Wire Wire Line
	7600 3200 7700 3200
$Comp
L Device:C C9
U 1 1 5FD721EA
P 7550 2500
F 0 "C9" H 7665 2546 50  0000 L CNN
F 1 "22u" H 7665 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 7588 2350 50  0001 C CNN
F 3 "~" H 7550 2500 50  0001 C CNN
	1    7550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 2300 7750 2250
Wire Wire Line
	7750 2300 7950 2300
Connection ~ 7750 2300
$Comp
L Connector_Generic:Conn_01x06 J4
U 1 1 5FD77148
P 10300 950
F 0 "J4" H 10380 942 50  0000 L CNN
F 1 "Conn_01x06" H 10380 851 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 10300 950 50  0001 C CNN
F 3 "~" H 10300 950 50  0001 C CNN
	1    10300 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 850  10100 850 
Wire Wire Line
	10000 750  10100 750 
Wire Wire Line
	10000 950  10100 950 
Wire Wire Line
	10000 1050 10100 1050
Text GLabel 10000 850  0    50   BiDi ~ 0
GPIO0
Wire Wire Line
	10000 1150 10100 1150
Text GLabel 7700 2900 2    50   BiDi ~ 0
GPIO0
Wire Wire Line
	7700 2900 7600 2900
Text GLabel 10000 1250 0    50   Input ~ 0
ESP32_EN
Wire Wire Line
	10000 1250 10100 1250
Text GLabel 5750 2900 0    50   Input ~ 0
ESP32_EN
$Comp
L Device:C C8
U 1 1 5FD8144D
P 5950 2750
F 0 "C8" V 5698 2750 50  0000 C CNN
F 1 "100n" V 5789 2750 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5988 2600 50  0001 C CNN
F 3 "~" H 5950 2750 50  0001 C CNN
	1    5950 2750
	0    1    1    0   
$EndComp
$Comp
L Device:R R14
U 1 1 5FD82B13
P 5950 3050
F 0 "R14" V 6050 3050 50  0000 C CNN
F 1 "10k" V 6150 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5880 3050 50  0001 C CNN
F 3 "~" H 5950 3050 50  0001 C CNN
	1    5950 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 2900 6200 2900
Wire Wire Line
	6100 2750 6200 2750
Wire Wire Line
	6200 2750 6200 2900
Connection ~ 6200 2900
Wire Wire Line
	6200 2900 6400 2900
Wire Wire Line
	6100 3050 6200 3050
Wire Wire Line
	6200 3050 6200 2900
$Comp
L power:+3.3V #PWR023
U 1 1 5FD8B676
P 5700 3050
F 0 "#PWR023" H 5700 2900 50  0001 C CNN
F 1 "+3.3V" V 5715 3178 50  0000 L CNN
F 2 "" H 5700 3050 50  0001 C CNN
F 3 "" H 5700 3050 50  0001 C CNN
	1    5700 3050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5FD8C0B9
P 5700 2750
F 0 "#PWR022" H 5700 2500 50  0001 C CNN
F 1 "GND" V 5705 2622 50  0000 R CNN
F 2 "" H 5700 2750 50  0001 C CNN
F 3 "" H 5700 2750 50  0001 C CNN
	1    5700 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 2750 5800 2750
Wire Wire Line
	5700 3050 5800 3050
Wire Wire Line
	1350 1250 1400 1250
Wire Wire Line
	1700 1250 1800 1250
$Comp
L power:GND #PWR019
U 1 1 5FD9C238
P 5200 1550
F 0 "#PWR019" H 5200 1300 50  0001 C CNN
F 1 "GND" V 5205 1422 50  0000 R CNN
F 2 "" H 5200 1550 50  0001 C CNN
F 3 "" H 5200 1550 50  0001 C CNN
	1    5200 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1800 1550 1350 1550
Wire Wire Line
	1350 1450 1350 1550
$Comp
L Device:Fuse F1
U 1 1 5FD344F3
P 1550 1250
F 0 "F1" V 1650 1200 50  0000 L CNN
F 1 "2A" V 1750 1200 50  0000 L CNN
F 2 "Fuse:Fuse_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 1480 1250 50  0001 C CNN
F 3 "~" H 1550 1250 50  0001 C CNN
	1    1550 1250
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5FDAE6EC
P 3200 1250
F 0 "R7" V 2993 1250 50  0000 C CNN
F 1 "R100" V 3084 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.40x3.35mm_HandSolder" V 3130 1250 50  0001 C CNN
F 3 "~" H 3200 1250 50  0001 C CNN
	1    3200 1250
	0    1    1    0   
$EndComp
Text GLabel 2950 1200 1    50   Output ~ 0
SHUNT+
Text GLabel 3450 1200 1    50   Output ~ 0
SHUNT-
Wire Wire Line
	3350 1250 3450 1250
Wire Wire Line
	3450 1250 3450 1200
Wire Wire Line
	2950 1250 2950 1200
Wire Wire Line
	2950 1250 3050 1250
Text GLabel 1400 2400 0    50   Output ~ 0
SHUNT+
Text GLabel 1400 2700 0    50   Output ~ 0
SHUNT-
$Comp
L Device:R R2
U 1 1 5FDD7980
P 1650 2400
F 0 "R2" V 1443 2400 50  0000 C CNN
F 1 "10R" V 1534 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1580 2400 50  0001 C CNN
F 3 "~" H 1650 2400 50  0001 C CNN
	1    1650 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 2400 1500 2400
$Comp
L Device:C C2
U 1 1 5FDDE08B
P 1950 2550
F 0 "C2" H 2065 2596 50  0000 L CNN
F 1 "100n" H 2065 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 1988 2400 50  0001 C CNN
F 3 "~" H 1950 2550 50  0001 C CNN
	1    1950 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5FDE0E52
P 1650 2700
F 0 "R3" V 1443 2700 50  0000 C CNN
F 1 "10R" V 1534 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1580 2700 50  0001 C CNN
F 3 "~" H 1650 2700 50  0001 C CNN
	1    1650 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 2700 1500 2700
Wire Wire Line
	1800 2700 1950 2700
Wire Wire Line
	1800 2400 1950 2400
Wire Wire Line
	1950 2700 2300 2700
Wire Wire Line
	2300 2700 2300 2650
Connection ~ 1950 2700
Wire Wire Line
	1950 2400 2300 2400
Wire Wire Line
	2300 2400 2300 2450
Connection ~ 1950 2400
$Comp
L power:GND #PWR05
U 1 1 5FDE4C40
P 2700 3050
F 0 "#PWR05" H 2700 2800 50  0001 C CNN
F 1 "GND" H 2705 2877 50  0000 C CNN
F 2 "" H 2700 3050 50  0001 C CNN
F 3 "" H 2700 3050 50  0001 C CNN
	1    2700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3050 2700 2950
$Comp
L Device:C C3
U 1 1 5FDE656F
P 3200 2150
F 0 "C3" V 2948 2150 50  0000 C CNN
F 1 "100n" V 3039 2150 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3238 2000 50  0001 C CNN
F 3 "~" H 3200 2150 50  0001 C CNN
	1    3200 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 2150 2950 2150
$Comp
L power:GND #PWR011
U 1 1 5FDEB574
P 3450 2150
F 0 "#PWR011" H 3450 1900 50  0001 C CNN
F 1 "GND" V 3455 2022 50  0000 R CNN
F 2 "" H 3450 2150 50  0001 C CNN
F 3 "" H 3450 2150 50  0001 C CNN
	1    3450 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3450 2150 3350 2150
$Comp
L power:+3.3V #PWR06
U 1 1 5FDECCEA
P 2950 2050
F 0 "#PWR06" H 2950 1900 50  0001 C CNN
F 1 "+3.3V" H 2965 2223 50  0000 C CNN
F 2 "" H 2950 2050 50  0001 C CNN
F 3 "" H 2950 2050 50  0001 C CNN
	1    2950 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 2050 2950 2150
Connection ~ 2950 2150
Wire Wire Line
	2950 2150 2700 2150
Wire Wire Line
	7550 2300 7750 2300
Wire Wire Line
	7550 2350 7550 2300
Wire Wire Line
	7950 2300 7950 2350
$Comp
L Device:C C10
U 1 1 5FD74204
P 7950 2500
F 0 "C10" H 8065 2546 50  0000 L CNN
F 1 "100n" H 8065 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 7988 2350 50  0001 C CNN
F 3 "~" H 7950 2500 50  0001 C CNN
	1    7950 2500
	1    0    0    -1  
$EndComp
Text GLabel 9800 1900 0    50   BiDi ~ 0
GPIO0
Wire Wire Line
	9800 1900 9950 1900
$Comp
L Device:C C11
U 1 1 5FE1FD0D
P 10200 2200
F 0 "C11" V 9948 2200 50  0000 C CNN
F 1 "100n" V 10039 2200 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 10238 2050 50  0001 C CNN
F 3 "~" H 10200 2200 50  0001 C CNN
	1    10200 2200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR031
U 1 1 5FE2313A
P 10650 1900
F 0 "#PWR031" H 10650 1650 50  0001 C CNN
F 1 "GND" V 10655 1772 50  0000 R CNN
F 2 "" H 10650 1900 50  0001 C CNN
F 3 "" H 10650 1900 50  0001 C CNN
	1    10650 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10650 1900 10450 1900
Wire Wire Line
	10350 2200 10450 2200
Wire Wire Line
	10450 2200 10450 1900
Connection ~ 10450 1900
Wire Wire Line
	10450 1900 10400 1900
Wire Wire Line
	9950 1900 9950 2200
Wire Wire Line
	9950 2200 10050 2200
Connection ~ 9950 1900
Wire Wire Line
	9950 1900 10000 1900
Wire Wire Line
	9800 3350 9950 3350
$Comp
L Device:C C12
U 1 1 5FE2E067
P 10200 3650
F 0 "C12" V 9948 3650 50  0000 C CNN
F 1 "100n" V 10039 3650 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 10238 3500 50  0001 C CNN
F 3 "~" H 10200 3650 50  0001 C CNN
	1    10200 3650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5FE2E06D
P 10650 3350
F 0 "#PWR032" H 10650 3100 50  0001 C CNN
F 1 "GND" V 10655 3222 50  0000 R CNN
F 2 "" H 10650 3350 50  0001 C CNN
F 3 "" H 10650 3350 50  0001 C CNN
	1    10650 3350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10650 3350 10450 3350
Wire Wire Line
	10350 3650 10450 3650
Wire Wire Line
	10450 3650 10450 3350
Connection ~ 10450 3350
Wire Wire Line
	10450 3350 10400 3350
Wire Wire Line
	9950 3350 9950 3650
Wire Wire Line
	9950 3650 10050 3650
Connection ~ 9950 3350
Wire Wire Line
	9950 3350 10000 3350
Text GLabel 9800 3350 0    50   Input ~ 0
ESP32_EN
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U3
U 1 1 5FE31EB0
P 4600 1250
F 0 "U3" H 4600 1492 50  0000 C CNN
F 1 "LDL1117S33R_SOT223" H 4600 1401 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4600 1450 50  0001 C CNN
F 3 "https://www.st.com/resource/en/datasheet/ldl1117.pdf" H 4700 1000 50  0001 C CNN
	1    4600 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5FE39546
P 4050 1400
F 0 "C6" H 4165 1446 50  0000 L CNN
F 1 "1u" H 4165 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 4088 1250 50  0001 C CNN
F 3 "~" H 4050 1400 50  0001 C CNN
	1    4050 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5FE39C6A
P 5050 1400
F 0 "C7" H 5165 1446 50  0000 L CNN
F 1 "4.7u" H 5165 1355 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5088 1250 50  0001 C CNN
F 3 "~" H 5050 1400 50  0001 C CNN
	1    5050 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1550 4600 1550
Connection ~ 4600 1550
Wire Wire Line
	4600 1550 5050 1550
Wire Wire Line
	4900 1250 5050 1250
Wire Wire Line
	4050 1250 4300 1250
$Comp
L power:+3.3V #PWR017
U 1 1 5FE4677B
P 5150 1250
F 0 "#PWR017" H 5150 1100 50  0001 C CNN
F 1 "+3.3V" V 5165 1378 50  0000 L CNN
F 2 "" H 5150 1250 50  0001 C CNN
F 3 "" H 5150 1250 50  0001 C CNN
	1    5150 1250
	0    1    1    0   
$EndComp
Connection ~ 4050 1250
Wire Wire Line
	5050 1250 5150 1250
Connection ~ 5050 1250
$Comp
L Device:Q_PMOS_GDS Q3
U 1 1 5FE5AD79
P 2600 1350
F 0 "Q3" V 2942 1350 50  0000 C CNN
F 1 "FDD4243" V 2851 1350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 2800 1450 50  0001 C CNN
F 3 "~" H 2600 1350 50  0001 C CNN
	1    2600 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2400 1250 1800 1250
Connection ~ 1800 1250
Wire Wire Line
	1800 1550 2600 1550
Connection ~ 1800 1550
Wire Wire Line
	2800 1250 2950 1250
Connection ~ 2950 1250
$Comp
L power:+12V #PWR014
U 1 1 5FE943F2
P 3900 1200
F 0 "#PWR014" H 3900 1050 50  0001 C CNN
F 1 "+12V" H 3915 1373 50  0000 C CNN
F 2 "" H 3900 1200 50  0001 C CNN
F 3 "" H 3900 1200 50  0001 C CNN
	1    3900 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1250 3450 1250
Connection ~ 3450 1250
$Comp
L power:GND #PWR09
U 1 1 5FEA70BE
P 3200 2700
F 0 "#PWR09" H 3200 2450 50  0001 C CNN
F 1 "GND" V 3205 2572 50  0000 R CNN
F 2 "" H 3200 2700 50  0001 C CNN
F 3 "" H 3200 2700 50  0001 C CNN
	1    3200 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 2650 3150 2650
Wire Wire Line
	3150 2650 3150 2700
Wire Wire Line
	3150 2700 3200 2700
Wire Wire Line
	7000 5600 7000 5500
$Comp
L power:GND #PWR027
U 1 1 5FD702A8
P 7000 5600
F 0 "#PWR027" H 7000 5350 50  0001 C CNN
F 1 "GND" H 7005 5427 50  0000 C CNN
F 2 "" H 7000 5600 50  0001 C CNN
F 3 "" H 7000 5600 50  0001 C CNN
	1    7000 5600
	1    0    0    -1  
$EndComp
NoConn ~ 6400 4100
NoConn ~ 6400 4200
NoConn ~ 6400 4500
NoConn ~ 6400 4600
$Comp
L power:GND #PWR010
U 1 1 5FECAE5A
P 3300 4850
F 0 "#PWR010" H 3300 4600 50  0001 C CNN
F 1 "GND" H 3305 4677 50  0000 C CNN
F 2 "" H 3300 4850 50  0001 C CNN
F 3 "" H 3300 4850 50  0001 C CNN
	1    3300 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 4850 3300 4750
$Comp
L power:+3.3V #PWR012
U 1 1 5FED2CE2
P 3750 3750
F 0 "#PWR012" H 3750 3600 50  0001 C CNN
F 1 "+3.3V" V 3765 3878 50  0000 L CNN
F 2 "" H 3750 3750 50  0001 C CNN
F 3 "" H 3750 3750 50  0001 C CNN
	1    3750 3750
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 5FED2CED
P 3600 3600
F 0 "C4" H 3715 3646 50  0000 L CNN
F 1 "100n" H 3715 3555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3638 3450 50  0001 C CNN
F 3 "~" H 3600 3600 50  0001 C CNN
	1    3600 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3750 3600 3750
Wire Wire Line
	3600 3750 3300 3750
Connection ~ 3600 3750
$Comp
L power:GND #PWR013
U 1 1 5FEDE1A8
P 3800 3450
F 0 "#PWR013" H 3800 3200 50  0001 C CNN
F 1 "GND" V 3805 3322 50  0000 R CNN
F 2 "" H 3800 3450 50  0001 C CNN
F 3 "" H 3800 3450 50  0001 C CNN
	1    3800 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 3450 3600 3450
Text GLabel 3200 2350 2    50   3State ~ 0
SDA
Wire Wire Line
	3200 2350 3100 2350
Text GLabel 3200 2450 2    50   3State ~ 0
SCL
Wire Wire Line
	3200 2450 3100 2450
Wire Wire Line
	3100 2750 3150 2750
Wire Wire Line
	3150 2750 3150 2700
Connection ~ 3150 2700
Text GLabel 8150 4400 2    50   3State ~ 0
SCL
Text GLabel 8150 4300 2    50   3State ~ 0
SDA
$Comp
L Device:R R16
U 1 1 5FF108BF
P 8250 4500
F 0 "R16" V 8150 4500 50  0000 C CNN
F 1 "3.3k" V 8050 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8180 4500 50  0001 C CNN
F 3 "~" H 8250 4500 50  0001 C CNN
	1    8250 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 4300 8050 4300
Wire Wire Line
	7600 4400 8050 4400
Wire Wire Line
	8100 4500 8050 4500
Wire Wire Line
	8050 4500 8050 4400
Wire Wire Line
	8050 4400 8150 4400
Wire Wire Line
	8050 4300 8050 4200
Wire Wire Line
	8050 4300 8150 4300
Wire Wire Line
	8050 4200 8100 4200
$Comp
L Device:R R15
U 1 1 5FF0B626
P 8250 4200
F 0 "R15" V 8450 4200 50  0000 C CNN
F 1 "3.3k" V 8350 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8180 4200 50  0001 C CNN
F 3 "~" H 8250 4200 50  0001 C CNN
	1    8250 4200
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR028
U 1 1 5FF4B3A7
P 8500 4350
F 0 "#PWR028" H 8500 4200 50  0001 C CNN
F 1 "+3.3V" V 8515 4478 50  0000 L CNN
F 2 "" H 8500 4350 50  0001 C CNN
F 3 "" H 8500 4350 50  0001 C CNN
	1    8500 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	8400 4200 8450 4200
Wire Wire Line
	8450 4200 8450 4350
Wire Wire Line
	8450 4350 8500 4350
Wire Wire Line
	8400 4500 8450 4500
Wire Wire Line
	8450 4500 8450 4350
Connection ~ 8450 4350
Wire Wire Line
	3900 1200 3900 1250
Wire Wire Line
	3900 1250 4050 1250
$Comp
L Device:C C5
U 1 1 5FF8B1B8
P 3650 1400
F 0 "C5" H 3765 1446 50  0000 L CNN
F 1 "470u" H 3765 1355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 3688 1250 50  0001 C CNN
F 3 "~" H 3650 1400 50  0001 C CNN
	1    3650 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1550 4050 1550
Connection ~ 4050 1550
Wire Wire Line
	3650 1250 3900 1250
Connection ~ 3900 1250
Connection ~ 3650 1250
Wire Wire Line
	3650 1550 2600 1550
Connection ~ 3650 1550
Connection ~ 2600 1550
Wire Wire Line
	5200 1550 5050 1550
Connection ~ 5050 1550
Text GLabel 6250 4300 0    50   Input ~ 0
UART1_RX
Wire Wire Line
	6250 4300 6400 4300
Text GLabel 6250 4400 0    50   Output ~ 0
UART1_TX
Wire Wire Line
	6250 4400 6400 4400
NoConn ~ 7600 4800
NoConn ~ 7600 4500
NoConn ~ 7600 4200
NoConn ~ 7600 4100
NoConn ~ 7600 4000
NoConn ~ 7600 3900
NoConn ~ 7600 3800
NoConn ~ 7600 3700
NoConn ~ 7600 3600
NoConn ~ 7600 3500
NoConn ~ 7600 3400
NoConn ~ 7600 3300
NoConn ~ 7600 3100
Text GLabel 10500 4400 2    50   Input ~ 0
UART1_RX
Text GLabel 10500 4100 2    50   Output ~ 0
UART1_TX
Text GLabel 4500 4050 2    50   Input ~ 0
IQRF_RX
Text GLabel 4500 4350 2    50   Output ~ 0
IQRF_TX
Wire Wire Line
	4500 4350 4400 4350
Wire Wire Line
	4500 4050 4400 4050
$Comp
L power:GND #PWR018
U 1 1 60038259
P 5150 4200
F 0 "#PWR018" H 5150 3950 50  0001 C CNN
F 1 "GND" H 5400 4150 50  0000 R CNN
F 2 "" H 5150 4200 50  0001 C CNN
F 3 "" H 5150 4200 50  0001 C CNN
	1    5150 4200
	1    0    0    -1  
$EndComp
NoConn ~ 4400 4250
NoConn ~ 2200 4250
$Comp
L Device:C C1
U 1 1 6004EE1E
P 1600 4500
F 0 "C1" V 1348 4500 50  0000 C CNN
F 1 "100n" V 1439 4500 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 1638 4350 50  0001 C CNN
F 3 "~" H 1600 4500 50  0001 C CNN
	1    1600 4500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 600513C9
P 1100 4150
F 0 "#PWR01" H 1100 3900 50  0001 C CNN
F 1 "GND" V 1105 4022 50  0000 R CNN
F 2 "" H 1100 4150 50  0001 C CNN
F 3 "" H 1100 4150 50  0001 C CNN
	1    1100 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 4150 1300 4150
Wire Wire Line
	1300 4150 1300 4500
Wire Wire Line
	1300 4500 1450 4500
Connection ~ 1300 4150
Wire Wire Line
	1800 4150 1900 4150
Wire Wire Line
	1900 4150 1900 4500
Wire Wire Line
	1900 4500 1750 4500
Connection ~ 1900 4150
Wire Wire Line
	1900 4150 2000 4150
$Comp
L Device:R R4
U 1 1 6006FA39
P 2000 3900
F 0 "R4" H 1930 3854 50  0000 R CNN
F 1 "10k" H 1930 3945 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1930 3900 50  0001 C CNN
F 3 "~" H 2000 3900 50  0001 C CNN
	1    2000 3900
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 60070AC5
P 2000 3650
F 0 "#PWR03" H 2000 3500 50  0001 C CNN
F 1 "+3.3V" H 2015 3823 50  0000 C CNN
F 2 "" H 2000 3650 50  0001 C CNN
F 3 "" H 2000 3650 50  0001 C CNN
	1    2000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3650 2000 3750
Wire Wire Line
	2000 4150 2000 4050
$Comp
L Jumper:Jumper_2_Bridged JP1
U 1 1 6007CAB8
P 10200 4100
F 0 "JP1" H 10200 4295 50  0000 C CNN
F 1 "Jumper_2_Bridged" H 10200 4204 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 10200 4100 50  0001 C CNN
F 3 "~" H 10200 4100 50  0001 C CNN
	1    10200 4100
	1    0    0    -1  
$EndComp
$Comp
L Jumper:Jumper_2_Bridged JP2
U 1 1 6007D2A6
P 10200 4400
F 0 "JP2" H 10200 4595 50  0000 C CNN
F 1 "Jumper_2_Bridged" H 10200 4504 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" H 10200 4400 50  0001 C CNN
F 3 "~" H 10200 4400 50  0001 C CNN
	1    10200 4400
	1    0    0    -1  
$EndComp
Text GLabel 9900 4400 0    50   Output ~ 0
IQRF_TX
Text GLabel 9900 4100 0    50   Input ~ 0
IQRF_RX
Wire Wire Line
	10500 4400 10400 4400
Wire Wire Line
	10000 4400 9900 4400
Wire Wire Line
	9900 4100 10000 4100
Wire Wire Line
	10400 4100 10500 4100
$Comp
L Device:R R12
U 1 1 600BADBB
P 5650 3550
F 0 "R12" H 5720 3596 50  0000 L CNN
F 1 "10k" H 5720 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5580 3550 50  0001 C CNN
F 3 "~" H 5650 3550 50  0001 C CNN
	1    5650 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 600BBBCE
P 5650 3950
F 0 "R13" H 5720 3996 50  0000 L CNN
F 1 "2.7k" H 5720 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5580 3950 50  0001 C CNN
F 3 "~" H 5650 3950 50  0001 C CNN
	1    5650 3950
	1    0    0    -1  
$EndComp
NoConn ~ 6400 3200
$Comp
L power:+12V #PWR020
U 1 1 600F58FC
P 5650 3350
F 0 "#PWR020" H 5650 3200 50  0001 C CNN
F 1 "+12V" H 5665 3523 50  0000 C CNN
F 2 "" H 5650 3350 50  0001 C CNN
F 3 "" H 5650 3350 50  0001 C CNN
	1    5650 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 600F5E54
P 5650 4150
F 0 "#PWR021" H 5650 3900 50  0001 C CNN
F 1 "GND" H 5655 3977 50  0000 C CNN
F 2 "" H 5650 4150 50  0001 C CNN
F 3 "" H 5650 4150 50  0001 C CNN
	1    5650 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 4150 5650 4100
Wire Wire Line
	5150 4200 5150 4150
Wire Wire Line
	4850 4150 4400 4150
$Comp
L Device:R R10
U 1 1 600375C5
P 5000 4150
F 0 "R10" V 5200 4150 50  0000 C CNN
F 1 "4.7k" V 5100 4150 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4930 4150 50  0001 C CNN
F 3 "~" H 5000 4150 50  0001 C CNN
	1    5000 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 3400 5650 3350
Wire Wire Line
	3050 5550 3050 5650
Wire Wire Line
	3150 5550 3050 5550
Wire Wire Line
	2200 5450 2200 5500
Wire Wire Line
	3150 5450 2200 5450
Wire Wire Line
	1350 5350 3150 5350
$Comp
L Device:Q_NMOS_GDS Q1
U 1 1 602B4B7D
P 1250 5550
F 0 "Q1" H 1500 5600 50  0000 C CNN
F 1 "BUK98150-55A" H 1750 5500 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 1450 5650 50  0001 C CNN
F 3 "~" H 1250 5550 50  0001 C CNN
	1    1250 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 602B4B77
P 1200 5900
F 0 "R1" H 1130 5854 50  0000 R CNN
F 1 "10k" H 1130 5945 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1130 5900 50  0001 C CNN
F 3 "~" H 1200 5900 50  0001 C CNN
	1    1200 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 5900 1350 5750
Wire Wire Line
	1350 6000 1350 5900
Connection ~ 1350 5900
$Comp
L power:GND #PWR02
U 1 1 602B4B6E
P 1350 6000
F 0 "#PWR02" H 1350 5750 50  0001 C CNN
F 1 "GND" V 1355 5872 50  0000 R CNN
F 2 "" H 1350 6000 50  0001 C CNN
F 3 "" H 1350 6000 50  0001 C CNN
	1    1350 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 5900 1050 5550
$Comp
L Device:Q_NMOS_GDS Q2
U 1 1 602AE355
P 2100 5700
F 0 "Q2" H 2350 5750 50  0000 C CNN
F 1 "BUK98150-55A" H 2600 5650 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 2300 5800 50  0001 C CNN
F 3 "~" H 2100 5700 50  0001 C CNN
	1    2100 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 602AE34F
P 2050 6050
F 0 "R5" H 1980 6004 50  0000 R CNN
F 1 "10k" H 1980 6095 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1980 6050 50  0001 C CNN
F 3 "~" H 2050 6050 50  0001 C CNN
	1    2050 6050
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 6050 2200 5900
Wire Wire Line
	2200 6150 2200 6050
Connection ~ 2200 6050
$Comp
L power:GND #PWR04
U 1 1 602AE346
P 2200 6150
F 0 "#PWR04" H 2200 5900 50  0001 C CNN
F 1 "GND" V 2205 6022 50  0000 R CNN
F 2 "" H 2200 6150 50  0001 C CNN
F 3 "" H 2200 6150 50  0001 C CNN
	1    2200 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 6050 1900 5700
$Comp
L Device:Q_NMOS_GDS Q4
U 1 1 6021CD59
P 2950 5850
F 0 "Q4" H 3200 5900 50  0000 C CNN
F 1 "BUK98150-55A" H 3450 5800 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 3150 5950 50  0001 C CNN
F 3 "~" H 2950 5850 50  0001 C CNN
	1    2950 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 6021F0E1
P 2900 6200
F 0 "R6" H 2830 6154 50  0000 R CNN
F 1 "10k" H 2830 6245 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 2830 6200 50  0001 C CNN
F 3 "~" H 2900 6200 50  0001 C CNN
	1    2900 6200
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 6200 3050 6050
Wire Wire Line
	3050 6300 3050 6200
Connection ~ 3050 6200
$Comp
L power:GND #PWR07
U 1 1 6023CB78
P 3050 6300
F 0 "#PWR07" H 3050 6050 50  0001 C CNN
F 1 "GND" V 3055 6172 50  0000 R CNN
F 2 "" H 3050 6300 50  0001 C CNN
F 3 "" H 3050 6300 50  0001 C CNN
	1    3050 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 6200 2750 5850
Wire Wire Line
	3100 5250 3150 5250
$Comp
L power:+12V #PWR08
U 1 1 6021448B
P 3100 5250
F 0 "#PWR08" H 3100 5100 50  0001 C CNN
F 1 "+12V" V 3115 5378 50  0000 L CNN
F 2 "" H 3100 5250 50  0001 C CNN
F 3 "" H 3100 5250 50  0001 C CNN
	1    3100 5250
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x04 J2
U 1 1 6020D8FE
P 3350 5350
F 0 "J2" H 3430 5342 50  0000 L CNN
F 1 "DG300-5.0" H 3430 5251 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-4_1x04_P5.00mm_Horizontal" H 3350 5350 50  0001 C CNN
F 3 "~" H 3350 5350 50  0001 C CNN
	1    3350 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 6250 5750 6350
Wire Wire Line
	5850 6250 5750 6250
Wire Wire Line
	4900 6150 4900 6200
Wire Wire Line
	5850 6150 4900 6150
Wire Wire Line
	4050 6050 5850 6050
$Comp
L Device:Q_NMOS_GDS Q5
U 1 1 60303F83
P 3950 6250
F 0 "Q5" H 4200 6300 50  0000 C CNN
F 1 "BUK98150-55A" H 4450 6200 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4150 6350 50  0001 C CNN
F 3 "~" H 3950 6250 50  0001 C CNN
	1    3950 6250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 60303F89
P 3900 6600
F 0 "R8" H 3830 6554 50  0000 R CNN
F 1 "10k" H 3830 6645 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 3830 6600 50  0001 C CNN
F 3 "~" H 3900 6600 50  0001 C CNN
	1    3900 6600
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 6600 4050 6450
Wire Wire Line
	4050 6700 4050 6600
Connection ~ 4050 6600
$Comp
L power:GND #PWR015
U 1 1 60303F92
P 4050 6700
F 0 "#PWR015" H 4050 6450 50  0001 C CNN
F 1 "GND" V 4055 6572 50  0000 R CNN
F 2 "" H 4050 6700 50  0001 C CNN
F 3 "" H 4050 6700 50  0001 C CNN
	1    4050 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 6600 3750 6250
$Comp
L Device:Q_NMOS_GDS Q6
U 1 1 60303F99
P 4800 6400
F 0 "Q6" H 5050 6450 50  0000 C CNN
F 1 "BUK98150-55A" H 5300 6350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 5000 6500 50  0001 C CNN
F 3 "~" H 4800 6400 50  0001 C CNN
	1    4800 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 60303F9F
P 4750 6750
F 0 "R9" H 4680 6704 50  0000 R CNN
F 1 "10k" H 4680 6795 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4680 6750 50  0001 C CNN
F 3 "~" H 4750 6750 50  0001 C CNN
	1    4750 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 6750 4900 6600
Wire Wire Line
	4900 6850 4900 6750
Connection ~ 4900 6750
$Comp
L power:GND #PWR016
U 1 1 60303FA8
P 4900 6850
F 0 "#PWR016" H 4900 6600 50  0001 C CNN
F 1 "GND" V 4905 6722 50  0000 R CNN
F 2 "" H 4900 6850 50  0001 C CNN
F 3 "" H 4900 6850 50  0001 C CNN
	1    4900 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 6750 4600 6400
$Comp
L Device:Q_NMOS_GDS Q7
U 1 1 60303FAF
P 5650 6550
F 0 "Q7" H 5900 6600 50  0000 C CNN
F 1 "BUK98150-55A" H 6150 6500 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 5850 6650 50  0001 C CNN
F 3 "~" H 5650 6550 50  0001 C CNN
	1    5650 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 60303FB5
P 5600 6900
F 0 "R11" H 5530 6854 50  0000 R CNN
F 1 "10k" H 5530 6945 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5530 6900 50  0001 C CNN
F 3 "~" H 5600 6900 50  0001 C CNN
	1    5600 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 6900 5750 6750
Wire Wire Line
	5750 7000 5750 6900
Connection ~ 5750 6900
$Comp
L power:GND #PWR024
U 1 1 60303FBE
P 5750 7000
F 0 "#PWR024" H 5750 6750 50  0001 C CNN
F 1 "GND" V 5755 6872 50  0000 R CNN
F 2 "" H 5750 7000 50  0001 C CNN
F 3 "" H 5750 7000 50  0001 C CNN
	1    5750 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 6900 5450 6550
Wire Wire Line
	5800 5950 5850 5950
$Comp
L power:+12V #PWR025
U 1 1 60303FC6
P 5800 5950
F 0 "#PWR025" H 5800 5800 50  0001 C CNN
F 1 "+12V" V 5815 6078 50  0000 L CNN
F 2 "" H 5800 5950 50  0001 C CNN
F 3 "" H 5800 5950 50  0001 C CNN
	1    5800 5950
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x04 J3
U 1 1 60303FCC
P 6050 6050
F 0 "J3" H 6130 6042 50  0000 L CNN
F 1 "DG300-5.0" H 6130 5951 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-4_1x04_P5.00mm_Horizontal" H 6050 6050 50  0001 C CNN
F 3 "~" H 6050 6050 50  0001 C CNN
	1    6050 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3700 5650 3750
Wire Wire Line
	6400 3100 6300 3100
Wire Wire Line
	6300 3100 6300 3750
Wire Wire Line
	6300 3750 5650 3750
Connection ~ 5650 3750
Wire Wire Line
	5650 3750 5650 3800
Text GLabel 1000 5900 0    50   Input ~ 0
PWM1
Text GLabel 1850 6050 0    50   Input ~ 0
PWM2
Text GLabel 2700 6200 0    50   Input ~ 0
PWM3
Text GLabel 3700 6600 0    50   Input ~ 0
PWM4
Text GLabel 4550 6750 0    50   Input ~ 0
PWM5
Text GLabel 5400 6900 0    50   Input ~ 0
PWM6
Wire Wire Line
	1000 5900 1050 5900
Connection ~ 1050 5900
Wire Wire Line
	1850 6050 1900 6050
Connection ~ 1900 6050
Wire Wire Line
	2700 6200 2750 6200
Connection ~ 2750 6200
Wire Wire Line
	3700 6600 3750 6600
Connection ~ 3750 6600
Wire Wire Line
	4550 6750 4600 6750
Connection ~ 4600 6750
Wire Wire Line
	5400 6900 5450 6900
Connection ~ 5450 6900
Text GLabel 7750 5100 2    50   Output ~ 0
PWM6
Text GLabel 7750 5200 2    50   Output ~ 0
PWM5
Text GLabel 7750 4900 2    50   Output ~ 0
PWM4
Text GLabel 7750 5000 2    50   Output ~ 0
PWM3
Wire Wire Line
	7600 4900 7750 4900
Wire Wire Line
	7600 5000 7750 5000
Wire Wire Line
	7600 5100 7750 5100
Wire Wire Line
	7600 5200 7750 5200
Connection ~ 8050 4300
Connection ~ 8050 4400
Text GLabel 7750 4600 2    50   Output ~ 0
PWM2
Text GLabel 7750 4700 2    50   Output ~ 0
PWM1
Wire Wire Line
	7600 4700 7750 4700
Wire Wire Line
	7600 4600 7750 4600
$Comp
L Connector:Barrel_Jack_Switch J1
U 1 1 6041D1FE
P 1050 1350
F 0 "J1" H 1107 1667 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 1107 1576 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 1100 1310 50  0001 C CNN
F 3 "~" H 1100 1310 50  0001 C CNN
	1    1050 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1350 1350 1450
Connection ~ 1350 1450
$Comp
L Mechanical:MountingHole H1
U 1 1 6058875E
P 9950 5850
F 0 "H1" H 10050 5896 50  0000 L CNN
F 1 "MountingHole" H 10050 5805 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 9950 5850 50  0001 C CNN
F 3 "~" H 9950 5850 50  0001 C CNN
	1    9950 5850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 6058D7F1
P 9950 6050
F 0 "H2" H 10050 6096 50  0000 L CNN
F 1 "MountingHole" H 10050 6005 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 9950 6050 50  0001 C CNN
F 3 "~" H 9950 6050 50  0001 C CNN
	1    9950 6050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 6058DD23
P 9950 6250
F 0 "H3" H 10050 6296 50  0000 L CNN
F 1 "MountingHole" H 10050 6205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 9950 6250 50  0001 C CNN
F 3 "~" H 9950 6250 50  0001 C CNN
	1    9950 6250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR026
U 1 1 5FD72AD2
P 8000 2700
F 0 "#PWR026" H 8000 2550 50  0001 C CNN
F 1 "+3.3V" V 8050 2900 50  0000 C CNN
F 2 "" H 8000 2700 50  0001 C CNN
F 3 "" H 8000 2700 50  0001 C CNN
	1    8000 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 2700 7550 2700
Wire Wire Line
	7550 2700 7550 2650
Wire Wire Line
	7550 2700 7950 2700
Connection ~ 7550 2700
Wire Wire Line
	7950 2650 7950 2700
Connection ~ 7950 2700
Wire Wire Line
	7950 2700 8000 2700
$Comp
L power:GND #PWR0101
U 1 1 5FE83E53
P 7750 2250
F 0 "#PWR0101" H 7750 2000 50  0001 C CNN
F 1 "GND" H 7750 2100 50  0000 R CNN
F 2 "" H 7750 2250 50  0001 C CNN
F 3 "" H 7750 2250 50  0001 C CNN
	1    7750 2250
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_Dual SW2
U 1 1 5FEF5F3E
P 10200 1700
F 0 "SW2" H 10200 1985 50  0000 C CNN
F 1 "SW_Push_Dual" H 10200 1894 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_Omron_B3FS-100xP" H 10200 1900 50  0001 C CNN
F 3 "~" H 10200 1900 50  0001 C CNN
	1    10200 1700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual SW3
U 1 1 5FEF77E7
P 10200 3150
F 0 "SW3" H 10200 3435 50  0000 C CNN
F 1 "SW_Push_Dual" H 10200 3344 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_Omron_B3FS-100xP" H 10200 3350 50  0001 C CNN
F 3 "~" H 10200 3350 50  0001 C CNN
	1    10200 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4150 1400 4150
$Comp
L Switch:SW_Push_Dual SW1
U 1 1 5FF0224C
P 1600 3950
F 0 "SW1" H 1600 4235 50  0000 C CNN
F 1 "SW_Push_Dual" H 1600 4144 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_Omron_B3FS-100xP" H 1600 4150 50  0001 C CNN
F 3 "~" H 1600 4150 50  0001 C CNN
	1    1600 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 3150 10450 3150
Wire Wire Line
	10450 3150 10450 3350
Wire Wire Line
	10000 3150 9950 3150
Wire Wire Line
	9950 3150 9950 3350
Wire Wire Line
	10400 1700 10450 1700
Wire Wire Line
	10450 1700 10450 1900
Wire Wire Line
	10000 1700 9950 1700
Wire Wire Line
	9950 1700 9950 1900
Wire Wire Line
	1400 3950 1300 3950
Wire Wire Line
	1300 3950 1300 4150
Wire Wire Line
	1800 3950 1900 3950
Wire Wire Line
	1900 3950 1900 4150
Connection ~ 2000 4150
Wire Wire Line
	2000 4150 2200 4150
$EndSCHEMATC
