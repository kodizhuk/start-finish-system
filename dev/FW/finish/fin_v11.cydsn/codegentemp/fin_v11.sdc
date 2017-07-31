# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Cypress\system-start-finish\dev\FW\finish\fin_v11.cydsn\fin_v11.cyprj
# Date: Mon, 31 Jul 2017 10:51:33 GMT
#set_units -time ns
create_clock -name {ADC_intClock(FFB)} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {UART_XB_SCBCLK(FFB)} -period 34729.166666666664 -waveform {0 17364.5833333333} [list [get_pins {ClockBlock/ff_div_1}]]
create_clock -name {timer_clock(FFB)} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ff_div_7}]]
create_clock -name {I2C_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {Clock_3(FFB)} -period 30520.833333333332 -waveform {0 15260.4166666667} [list [get_pins {ClockBlock/ff_div_8}]]
create_clock -name {timer_clock_2(FFB)} -period 100000 -waveform {0 50000} [list [get_pins {ClockBlock/ff_div_9}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFCLK} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {ADC_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 33} [list]
create_generated_clock -name {UART_XB_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 1667 3335} -nominal_period 34729.166666666664 [list]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 48001 96001} [list]
create_generated_clock -name {I2C_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 31 61} [list]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/hfclk}] -edges {1 1465 2931} [list]
create_generated_clock -name {timer_clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 4801 9601} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 48001 96001} [list [get_pins {ClockBlock/udb_div_0}]]


# Component constraints for D:\Cypress\system-start-finish\dev\FW\finish\fin_v11.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Cypress\system-start-finish\dev\FW\finish\fin_v11.cydsn\fin_v11.cyprj
# Date: Mon, 31 Jul 2017 10:51:18 GMT
