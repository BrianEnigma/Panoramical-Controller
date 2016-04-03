#Panoramical MIDI Controller

**NOTE: At this time, this project is still a work-in-progress.**

##Overview

This project is a fork of a project by the same name at <https://github.com/brendan-byrne/Panoramical-Controller>. It is an Open Source MIDI controller for the videogame-like interactive experience [Panoramical](http://panoramic.al/) by [Fernando Ramallo](http://www.byfernando.com/) and [David Kanaga](https://davidkanaga.bandcamp.com/). The controller consists of eighteen rotary potentiometers sending MIDI data via a microcontroller.

##Electronic Parts

More details about the electronic build are in the [Hardware folder](Hardware/).

- [Teensy 2.0](https://www.pjrc.com/store/teensy.html) — $16.00
    - You can also use an Arduino as the microcontroller.
- [Mux](https://www.sparkfun.com/products/9056) — $4.95
- [Potentiometers](https://www.sparkfun.com/products/9939) (x18) — $17.10
- [knobs](https://www.sparkfun.com/products/10002) (x18) — $27.00
- [USB panel-mount cable, B-Female to micro-B male](https://www.adafruit.com/products/937) - $3.95
- arcade button (TBD)

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

There are two sets of code folders, one for testing the hardware and one actual MIDI use.

- [Hardware_Test](Hardware_Test/Hardware_Test.ino) — This program reads the values of the potentiometers and writes them to the serial port.
- MidiController — This is the final program that sends MIDI commands over USB.

##License

TODO: figure out license of the original project, echo that license here.

