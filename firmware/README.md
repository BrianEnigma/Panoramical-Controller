#Firmware For Arduino USB Serial Chip

This folder contains the firmware for the Arduino Uno R3 USB serial chip. This is not the main chip that holds your code, but the secondary chip (Atmega8U2) that sits near the USB port and handles the serial/USB protocol. 

This chip can only be programmed with an AVR programmer, such as the [Sparkfun Pocket AVR Programmer](https://www.sparkfun.com/products/9825) through the 6-pin header. It adds another level of difficulty, in that you can't upload code to the main Arduino chip when it is in MIDI mode. You need to ensure it holds the USB serial firmware (which it does by default), upload your code, then push the MIDI firmware. If you need to update your code, you have to temporarily switch back to USB serial to upload again.

The two firmware images found in this folder can be found at the following links:

- [USB Serial](https://github.com/arduino/Arduino/tree/1.6.9/hardware/arduino/avr/firmwares/atmegaxxu2)
- [Hiduino MIDI](https://github.com/ddiakopoulos/hiduino/tree/master/compiled_firmwares)

The `to_serial.sh` and `to_mini.sh` shell scripts package up the avrdude command you need to upload to that chip, assuming you have the Sparkfun programmer (or a similar one that identifies as `usbtiny`).

One thing to note: The 6-pin header for reprogramming the USB serial chip is the one closest to the USB port (not the one nearest the main chip). The Sparkfun programmer plugs in in a counterintuitive way. There is an alignment notch in the plug that typically isn't used for simple 6-pin headers. This notch bumps into the header for the digital inputs. My initial assumption was that I had the plug oriented incorrectly, so I plugged it in in the only way I thought it was supposed to fit. After a lot of trial and error, I realized I had it plugged in backwards. I had to wedge it in, putting a little extra stress on the 6-pin header in order to get the notch squeezed in between the 6-pin programming header and the header for the Arduino's digital input pins.

