#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Bounce.h>

class Button
{
  public:
    Button(byte pin, command_t command, byte value, byte channel, byte debounce);

    button_state_t getCompValue();

    inline byte getCommand();
    inline byte getValue();
    inline byte getChannel();
    inline byte getToggle();

    inline void setToggle(byte toggle);

  private:
    byte _pin;
    byte _muxpin;
    byte _numMuxPins;
    command_t _command;
    byte _value;
    byte _channel;
    byte _debounce;
    byte _toggle;
    Bounce _button;
};

Button::Button(byte pin, command_t command, byte value, byte channel, byte debounce):
    _pin(pin),
    _command(command),
    _value(value),
    _channel(channel),
    _debounce(debounce),
    _button(Bounce(pin, debounce))
{
    pinMode(_pin, INPUT_PULLUP);
    _toggle = 0;
}

button_state_t Button::getCompValue()
{
    _button.update();
    if (_button.fallingEdge()) return PRESSED;
    if (_button.risingEdge())  return NOT_PRESSED;
}

inline byte Button::getCommand()
{
    return _command;
}

inline byte Button::getValue()
{
    return _value;
}

inline byte Button::getChannel()
{
    return _channel;
}

inline byte Button::getToggle()
{
    return _toggle;
}

inline void Button::setToggle(byte toggle)
{
    _toggle = toggle;
}

#endif // BUTTON_HPP
