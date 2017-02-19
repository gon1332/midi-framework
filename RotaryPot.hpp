#ifndef ROTARYPOT_HPP
#define ROTARYPOT_HPP

class RotaryPot
{
  public:
    RotaryPot(byte pin, byte command, byte control, byte channel);

    inline byte getCompValue(); 
    inline byte getCommand();
    inline byte getControl();
    inline byte getChannel();

  private:
    byte _pin;
    byte _muxpin;
    byte _numMuxPins;
    byte _control;
    byte _command;
    byte _channel;
    int _value;
    int _oldValue;
    bool _changed;
    byte _enablepin;
};

RotaryPot::RotaryPot(byte pin, byte command, byte control, byte channel):
    _pin(pin),
    _control(control),
    _command(command),
    _channel(channel)
{
    _value = analogRead(_pin);
    _value = _value >> 3;
    _oldValue = _value << 3;
    _value = _value << 3;
}

byte RotaryPot::getCompValue()
{
    _value = analogRead(_pin);
    int tmp = (_oldValue - _value);
    if (tmp >= 8 || tmp <= -8) {
        _oldValue = _value >> 3;
        _oldValue = _oldValue << 3;
        return _value >> 3;
    }
    return 255;
}

inline byte RotaryPot::getCommand()
{
    return _command;
}

inline byte RotaryPot::getControl()
{
    return _control;
}

inline byte RotaryPot::getChannel()
{
    return _channel;
}

#endif // ROTARYPOT_HPP
