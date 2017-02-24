#ifndef SLIDEPOT_HPP
#define SLIDEPOT_HPP

class SlidePot
{
  public:
    SlidePot(byte pin, byte command, byte control, byte channel);

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

SlidePot::SlidePot(byte pin, byte command, byte control, byte channel):
    _pin(pin),
    _control(control),
    _command(command),
    _channel(channel)
{
    _value = analogRead(_pin);
    _oldValue = _value;
    _value = _value >> 3;
}

byte SlidePot::getCompValue()
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

inline byte SlidePot::getCommand()
{
    return _command;
}

inline byte SlidePot::getControl()
{
    return _control;
}

inline byte SlidePot::getChannel()
{
    return _channel;
}

#endif // SLIDEPOT_HPP
