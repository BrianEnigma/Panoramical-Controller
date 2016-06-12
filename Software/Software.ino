#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

#include <Bounce.h>

MIDI_CREATE_DEFAULT_INSTANCE();

/// Hardware Test
///
/// This application is used to test the wiring of the knob board. When run, it will send 
/// the values of all 18 knob positions to the serial port for you to examine.

/// The muxer's address lines are wired up to these pins.
const int MUX_ADDR_PINS[] = {2, 3, 4, 5};

/// The muxer's analog output comes in to the microcontroller.
/// on this pin.
const int MUX_COMMON = A0;

/// For debugging, this pin has an LED. This is 11 on the Teensy, 13 on an Arduino.
const int LED_PIN = 13;

/// Which pin has the arcade pushbutton attached to it
const int PUSHBUTTON_PIN = 6;

/// This maps which physical knob location on the panel is mapped
/// to which mux address lines. The -1 values are knobs that are
/// not wired to the mux because it can only address 16 of the 18
/// knobs.
const int MUX_PHYSICAL_TO_LOGICAL_MAP[] = {
    -1, 14, 12, 10, 8, 6, 4, 2, 0,
    -1, 15, 13, 11, 9, 7, 5, 3, 1
};

/// This maps which physical knob location on the panel is
/// mapped directly to a pin. The -1 values are knobs that
/// are not wired to a pin directly because they go through
/// the mux.
const int MUX_PHYSICAL_MAP[] {
    A1, -1, -1, -1, -1, -1, -1, -1, -1,
    A2, -1, -1, -1, -1, -1, -1, -1, -1
};

int cachedMidiControlValues[18];
int cachedPushbuttonValue;

Bounce arcadeButton = Bounce(PUSHBUTTON_PIN, 5); 

void setup() 
{
    MIDI.begin();
    Serial.begin(31250);
    //Serial.begin(9600);
    // Set up arcade pushbutton's internal pullup resistor
    pinMode(PUSHBUTTON_PIN,INPUT_PULLUP);
    // Set up the muxer address lines
    for (int i = 0; i < 4; i++)
    {
        pinMode(MUX_ADDR_PINS[i], OUTPUT);
        digitalWrite(MUX_ADDR_PINS[i], 0);
    }
    // Debug LED
    pinMode(LED_PIN, OUTPUT);
    for (unsigned int i = 0; i < sizeof(cachedMidiControlValues) / sizeof(int); i++)
        cachedMidiControlValues[i] = -1;
    cachedPushbuttonValue = 0;
}

/// Get scaled analog pin value
unsigned char getScaledPinValue(int pinNumber)
{
    unsigned long analogValue = analogRead(pinNumber);
    analogValue *= 0xFF;
    //analogValue /= 1023; // Magic number for Teensy?
    analogValue /= 890; // Magic number for Arduino Uno R3?
    return max(0, min(analogValue, 0xFF)); // clamp to 0..255
}

/// Get a muxed pin value, scaled to the range of 0x00-0xFF
unsigned char getLogicalMuxedPinValue(int muxAddress)
{
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(MUX_ADDR_PINS[i], muxAddress & 0x01);
        muxAddress >>= 1;
    }
    return getScaledPinValue(MUX_COMMON);
}

/// Return whether or not the given knob (numbered 1..18)
/// is wired to the mux.
unsigned char isKnobWiredToMux(int knobNumber)
{
    return -1 != MUX_PHYSICAL_TO_LOGICAL_MAP[knobNumber - 1];
}

/// Get the current value of the knob from the mux.
/// Knob are numbered from 1..18, across two rows, with
/// 1 in the top-left and 18 in the bottom right.
unsigned char getPhysicalMuxedPinValue(int knobNumber)
{
    if (knobNumber >= 1 && knobNumber <= 18 && isKnobWiredToMux(knobNumber))
        return getLogicalMuxedPinValue(MUX_PHYSICAL_TO_LOGICAL_MAP[knobNumber - 1]);
    return 0;
}

/// Return the current value of the given knob (1..18)
unsigned char getKnobValue(int knobNumber)
{
    if (knobNumber >= 1 && knobNumber <= 18)
    {
        if (isKnobWiredToMux(knobNumber))
            return getPhysicalMuxedPinValue(knobNumber);
        if (-1 != MUX_PHYSICAL_MAP[knobNumber - 1])
            return getScaledPinValue(MUX_PHYSICAL_MAP[knobNumber - 1]);
    }
    return 0;
}

unsigned char getArcadeButtonValue()
{
    arcadeButton.update();
    return arcadeButton.read() ? 0x00 : 0xFF;
}

unsigned char ledValue = 1;
void toggleLED()
{
    digitalWrite(LED_PIN, ledValue);
    ledValue ^= 0x01;
}

void sendMidiUpdate(int channel, unsigned char value, unsigned char force)
{
    int diff = (int) ((int) value) - ((int) cachedMidiControlValues[channel]);
    if (abs(diff) >= 2 || force)
    {
        cachedMidiControlValues[channel] = value;
        MIDI.sendControlChange(channel, value / 2, 1);
    }
}

void sendMidiPushbuttonUpdate(unsigned char value)
{
    if (cachedPushbuttonValue != value)
    {
        cachedPushbuttonValue = value;
        if (value != 0)
        {
            MIDI.sendNoteOn(60, 127, 8);
        } else {
            MIDI.sendNoteOff(60, 0, 8);
        }
    }
}

unsigned char firstLoop = 1;
unsigned long timestamp = 0;

void loop() 
{
    // Force update every 3 seconds.
    if (millis() - timestamp >= 3000)
    {
        timestamp = millis();
        firstLoop = 1;
    }
    // Force update on first loop.
    if (firstLoop)
    {
        for (int knob = 1; knob <= 18; knob++)
        {
            sendMidiUpdate(knob - 1, getKnobValue(knob), true);
        }
        firstLoop = 0;
    }
    // Update upon knob value change.
    for (int knob = 1; knob <= 18; knob++)
    {
        sendMidiUpdate(knob - 1, getKnobValue(knob), false);
    }
    // Update for button change.
    sendMidiPushbuttonUpdate(getArcadeButtonValue());
}

