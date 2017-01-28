#include "Controller.hpp"

// === NUMBER OF CONTROLS USED
byte NUMBER_BUTTONS = 4;
byte NUMBER_ROTPOTS = 0;
byte NUMBER_SLDPOTS = 0;
byte NUMBER_NCODERS = 0;


// === DEFINE DIRECTLY CONNECTED BUTTONS
// - Button (Pin Number, Command, Note Number, Channel, Debounce Time)
// --> Command parameter 0=NOTE, 1=CC, 2=Toggle CC
Button BU0(0, CC, 50, 1, 5);
Button BU1(1, CC, 51, 1, 5);
Button BU2(2, CC, 52, 1, 5);
Button BU3(3, CC, 53, 1, 5);

// Array of pointers to buttons used
Button *BUTTONS[] { &BU0, &BU1, &BU2, &BU3  };


static void updateButtons();


void setup()
{
    /* Serial.begin(9600); */
    pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
    if (NUMBER_BUTTONS != 0) updateButtons();
    /* if (NUMBER_ROTPOTS != 0) updateRotPots(); */
    /* if (NUMBER_SLDPOTS != 0) updateSldPots(); */
    /* if (NUMBER_NCODERS != 0) updateNcoders(); */
}

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
