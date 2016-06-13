#Panoramical MIDI Controller

##Overview

This project is a fork of a project by the same name at <https://github.com/brendan-byrne/Panoramical-Controller>. It is an Open Source MIDI controller for the videogame-like interactive experience [Panoramical](http://panoramic.al/) by [Fernando Ramallo](http://www.byfernando.com/) and [David Kanaga](https://davidkanaga.bandcamp.com/). The controller consists of eighteen rotary potentiometers sending MIDI data via a microcontroller.

The project files themselves live here on Github: <https://github.com/BrianEnigma/Panoramical-Controller>

A blog post detailing the build is on my personal website: <https://netninja.com/2016/06/12/building-an-unusual-video-game-controller/>

##Electronic Parts

More details about the electronic build are in the [Hardware folder](Hardware/).

- [Arduino Uno R3](https://www.arduino.cc/en/Main/ArduinoBoardUno) - $25.00
    - I initially tried this with a Teensy 2.0, and was successful in all but the final step of getting the MIDI to output over USB.
- [Mux](https://www.sparkfun.com/products/9056) — $4.95
- [Potentiometers](https://www.sparkfun.com/products/9939) (x18) — $17.10
- [knobs](https://www.sparkfun.com/products/10002) (x18) — $27.00
- [USB panel-mount cable, B-Female to micro-B male](https://www.adafruit.com/products/937) - $3.95
- arcade button (TBD)
- AVR ISP, such as the [Sparkfun Pocket AVR Programmer](https://www.sparkfun.com/products/9825) - $15

Additionally: hookup wire, solder, heatshrink tubing, and so on.

##Enclosure

[TODO: enclosure photo]

The [Enclosure](Enclosure/) folder includes the files required to manufacture the enclosure as well as some build photos.

[TODO: build photos]

Each laser-cut enclosure file is based on the [24"x12" walnut sheet](http://www.ponoko.com/make-and-sell/show-material/598-premium-veneer-mdf-walnut) @ 3.5mm thickness at [Ponoko](http://ponoko.com/).

- 3mm Acrylic front panel
- 3.5mm wood side panels and inner supports

For assembly, you will need the following hardware from [McMaster-Carr](http://www.mcmaster.com/):

- [16M3 screws, #91290A120](http://www.mcmaster.com/#91290A120) (x8)
- [M3 nuts, #98676A100](http://www.mcmaster.com/#98676A100) (x8)

You will also need some wood glue to attach the inner supports.

##Code

Prerequisites:

- [Arduino MIDI library](https://github.com/FortySevenEffects/arduino_midi_library/)
- Arduino Debounce library (Bounce.h)
- [HIDUINO](https://github.com/ddiakopoulos/hiduino) provides the USB-serial firmware for getting the Arduino to masquerade as a USB MIDI device.

There are two sets of code folders, one for testing the hardware and one actual MIDI use.

- [Hardware_Test](Hardware_Test/Hardware_Test.ino) — This program reads the values of the potentiometers and writes them to the serial port at 9600 baud as human-readable text.
- [Software](Software/Software.ino) — This is the final program that sends MIDI commands over USB. It requires the HIDUINO MIDI firmware to be installed on the serial chip after loading. See the [firmware](firmware/) folder for more detail.

##Debugging

Using the `Hardware_Test` program, it was easy to validate that all the knobs and buttons were working by opening the Serial Monitor in the Arduino IDE software.

Once that was working, I loaded the true MIDI `Software` program and loaded the MIDI serial port firmware. I used the Mac application [MIDI Monitor(https://www.snoize.com/MIDIMonitor/) to verify MIDI commands were getting across correctly to the desktop computer.

##License

TODO: figure out license of the original project, echo that license here.

