// Example code for using the 2-pin encoder

#include <encoder.h>

#define ENCODER_PIN_A = 15
#define ENCODER_PIN_B = 22

ENCODER encoder(ENCODER_PIN_A, ENCODER_PIN_B);

void setup() {

  Serial.begin(115200);
  Serial.print("Starting 2-pin Encoder Example Demo Program\n");

  // start encoder
  encoder.init();

}


void loop() {

  // Things happen as interrupts, so we simply need to call get_pulses()
  Serial.println(encoder.get_pulses());
  delay(20);
  
}