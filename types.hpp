#ifndef TYPES_HPP
#define TYPES_HPP

#define CC_ON   127
#define CC_OFF  0

typedef enum { NOTE=0, CC, TOGGLE_CC }  command_t;
typedef enum { PRESSED=0, NOT_PRESSED } button_state_t;

#endif // TYPES_HPP
