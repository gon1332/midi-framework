#include "Controller.hpp"

// === NUMBER OF CONTROLS USED
byte NUMBER_BUTTONS = 0;
byte NUMBER_ROTPOTS = 0;
byte NUMBER_SLDPOTS = 1;
byte NUMBER_NCODERS = 0;


// === DEFINE DIRECTLY CONNECTED BUTTONS
// - Button (Pin Number, Command, Note Number, Channel, Debounce Time)
// --> Command parameter 0=NOTE, 1=CC, 2=Toggle CC
Button BU0(0, CC, 50, 1, 5);
Button BU1(1, CC, 51, 1, 5);
Button BU2(2, CC, 52, 1, 5);
Button BU3(3, CC, 53, 1, 5);

// Array of pointers to buttons used
Button *BUTTONS[] { &BU0, &BU1, &BU2, &BU3 };


// === DEFINE DIRECTLY CONNECTED ROTARY POTENTIOMETERS
// - RotaryPot (Pin Number, Command, CC Control, Channel)
RotaryPot RP0(A0, 0, 1, 1);

// Array of pointers to buttons used
RotaryPot *ROTPOTS[] { &RP0 };


// === DEFINE DIRECTLY CONNECTED SLIDE POTENTIOMETERS
// - SlidePot (Pin Number, Command, CC Control, Channel)
SlidePot SP0(A0, 0, 1, 1);

// Array of pointers to buttons used
SlidePot *SLDPOTS[] { &SP0 };


static void updateButtons();
static void updateRotPots();
static void updateSldPots();


void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
    if (NUMBER_BUTTONS != 0) updateButtons();
    if (NUMBER_ROTPOTS != 0) updateRotPots();
    if (NUMBER_SLDPOTS != 0) updateSldPots();
    /* if (NUMBER_NCODERS != 0) updateNcoders(); */
}


// === STATIC FUNCTIONS
// - Manipulating commponent values.

static void updateButtons()
{
    for (int i = 0; i < NUMBER_BUTTONS; i++) {
        button_state_t button_state = BUTTONS[i]->getCompValue();

        if (button_state == PRESSED) {
            switch (BUTTONS[i]->getCommand()) {
            case NOTE:
                break;
            case CC:
                digitalWrite(LED_BUILTIN, HIGH);
                usbMIDI.sendControlChange(
                    BUTTONS[i]->getValue(),
                    CC_ON,
                    BUTTONS[i]->getChannel());
                break;
            case TOGGLE_CC:
                break;
            }
        }

        if (button_state == NOT_PRESSED) {
            switch (BUTTONS[i]->getCommand()) {
            case NOTE:
                break;
            case CC:
                digitalWrite(LED_BUILTIN, LOW);
                usbMIDI.sendControlChange(
                    BUTTONS[i]->getValue(),
                    CC_OFF,
                    BUTTONS[i]->getChannel());
                break;
            }
        }
    }
}


static void updateRotPots()
{
    for (int i = 0; i < NUMBER_ROTPOTS; i++) {
        int pot_value = ROTPOTS[i]->getCompValue();
        if (pot_value != 255) {
            usbMIDI.sendControlChange(
                ROTPOTS[i]->getControl(),
                pot_value,
                ROTPOTS[i]->getChannel());
            Serial.println(pot_value);
        }
    }
}


static void updateSldPots()
{
    for (int i = 0; i < NUMBER_SLDPOTS; i++) {
        int pot_value = SLDPOTS[i]->getCompValue();
        if (pot_value != 255) {
            usbMIDI.sendControlChange(
                SLDPOTS[i]->getControl(),
                pot_value,
                SLDPOTS[i]->getChannel());
            Serial.println(pot_value);
        }
    }
}
