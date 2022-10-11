#pragma once

#include <Arduino.h>   // required before wiring_private.h

#ifndef SERIAL_DEBUG
#define SERIAL_DEBUG Serial
#endif

// Globals
// Due to the way Arduino works, everything for the interrupts has to be global
// This could be dangerous...

// Global Variables
extern volatile int32_t _encoder_pulses;
extern volatile bool _state_encoderA, _state_encoderB;
    
extern int _pinA, _pinB;
    
// Global Functions
void ISR_encoderA();
void ISR_encoderB();

class ENCODER {
    public :
    ENCODER(int pinA, int pinB);
    
    void init();
    void reset();
    
    int32_t get_pulses();
    float get_turns();
    
    void set_pulses_per_turn(uint32_t encoder_pulses_per_rev);
    bool enabled();
    
    uint8_t _debug = 0;
    
    private :
    
    // Constants
    int32_t _encoder_pulses_per_rev = 1550;

    int _pinA_set, _pinB_set;
    
    bool _zero_known = 0;
    bool _enabled = 0;
  
};
