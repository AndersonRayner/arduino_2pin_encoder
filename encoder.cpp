#include "encoder.h"

ENCODER::ENCODER(int pinA, int pinB) :
  _pinA_set(pinA),
  _pinB_set(pinB)
  {
      
  }
  
void ENCODER::init(void)
{
    // Set all the encoder pins and varialbles properly
    _pinA = _pinA_set;
    _pinB = _pinB_set;
    _encoder_pulses = 0;
    
    // Software pullups not required as all done in hardware
    pinMode(_pinA,INPUT); _state_encoderA = digitalRead(_pinA);
    pinMode(_pinB,INPUT); _state_encoderB = digitalRead(_pinB);

    // Attach interrupts to the encoders
    attachInterrupt(digitalPinToInterrupt(_pinA),ISR_encoderA  ,CHANGE);
    attachInterrupt(digitalPinToInterrupt(_pinB),ISR_encoderB  ,CHANGE);
    
    // Should be good to good
    _enabled = 1;
    return;
  
}
  
void ISR_encoderA()
{
    // Store what just happened on the encoder
    bool encoder_dir = 0;
    _state_encoderA = digitalRead(_pinA);
  
    // Work out which direction we are turning
    if (_state_encoderA == _state_encoderB)
    {
        encoder_dir = 1;
    } else {
        encoder_dir = 0;
    }

    // Increment / decrement the encoder
    if (encoder_dir == 0)
    {
        _encoder_pulses++;
    } else {
        _encoder_pulses--;
    }

    // All done
    return;
}

void ISR_encoderB()
{
    // We count pulses from encoder A so we only need to store the encoder state for encoder B
    _state_encoderB = digitalRead(_pinB);
  
    return;
}

int32_t ENCODER::get_pulses()
{
    // Returns the number of pulses from the encoder
    
    if (_debug)
    {
        SERIAL_DEBUG.print("ENCODER: Pulses "); SERIAL_DEBUG.print(_encoder_pulses); SERIAL_DEBUG.print(" [ - ]\n");
    }
    
    
    return (_encoder_pulses);
}

float ENCODER::get_turns()
{
    // Returns the number of turns
    float n_turns = (float) _encoder_pulses / (float) _encoder_pulses_per_rev;
    
    if (_debug)
    {
        SERIAL_DEBUG.print("ENCODER: "); SERIAL_DEBUG.print(n_turns); SERIAL_DEBUG.print(" [ turns ]\n");
    }        
    
    return (n_turns);
}

void ENCODER::set_pulses_per_turn(uint32_t encoder_pulses_per_rev)
{
    // Set the number of pulses per turn
    _encoder_pulses_per_rev = encoder_pulses_per_rev;

    return;
}    

void ENCODER::reset()
{
    // Resets the encoder counter
    _encoder_pulses = 0;
    _zero_known = 1;
    
    return;
}
