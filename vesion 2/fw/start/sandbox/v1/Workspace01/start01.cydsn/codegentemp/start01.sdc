# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Cypress\system-start-finish\vesion 2\fw\start\sandbox\v1\Workspace01\start01.cydsn\start01.cyprj
# Date: Thu, 07 Jul 2016 20:07:42 GMT
#set_units -time ns
create_clock -name {UART_PC_SCBCLK(FFB)} -period 8666.6666666666661 -waveform {0 4333.33333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {UART_XB_SCBCLK(FFB)} -period 8666.6666666666661 -waveform {0 4333.33333333333} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {timer_clock(FFB)} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ff_div_8}]]
create_clock -name {clock_1(FFB)} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ff_div_9}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {UART_PC_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 209 417} -nominal_period 8666.6666666666661 [list]
create_generated_clock -name {UART_XB_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 209 417} -nominal_period 8666.6666666666661 [list]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 24001 48001} [list]
create_generated_clock -name {clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 24001 48001} [list]


# Component constraints for D:\Cypress\system-start-finish\vesion 2\fw\start\sandbox\v1\Workspace01\start01.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Cypress\system-start-finish\vesion 2\fw\start\sandbox\v1\Workspace01\start01.cydsn\start01.cyprj
# Date: Thu, 07 Jul 2016 20:07:40 GMT
