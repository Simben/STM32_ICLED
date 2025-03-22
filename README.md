# STM32-IC LED

Crapy test code for the ICLED Featherwing demo board compatible with STM32 devices
(tested on Nucleo F411RE with default config)

Connect : 
Nucleo Gnd to board Gnd
Nucleo 3.3V to board 3.3V (needed for demo board level Shifters)
Nucleo PC3 to board Pin6

Press Nucleo user button to cycle through différent demo scene

WARNING : The HSV graph at Value == 0.5 or more need lot of current, will heat up the demo board Quickly and will burn your eyes --> use it carefully

## How it works : 

The code is based on the same logic as most of the WS2812 dialog protocol, we use SPI Half duplex (MoSi only) at a specific speed.
Each Data bit (8 for Green 8 for Red and 8 for Blue) are decomposed in a 4bits long word that represent the pattern needed to encode a 1 or a 0.

## Todo 
>> Check SPI speed (currently using the same as the one in Wurth demo code but these speed and patern does not seams to follow timing in data sheet) SPI speed around 2.66MHz and a 1 encoded as 0x0C should be more compliant.

>> Use DMA or at least It to send data to led and free some computational time

>> Add Large canvas with animation slide effect

>> Do better Code
