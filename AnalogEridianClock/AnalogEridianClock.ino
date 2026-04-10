#include <TinyStepper.h>

// Pins for ATtiny85 -> ULN2003
const int IN1 = 2; 
const int IN2 = 1; 
const int IN3 = 0; 
const int IN4 = 3; 

// 1 Eridian Second = 2.366 Earth Seconds
const uint32_t ERIDIAN_SECOND_MS = 2366; 

// The 28BYJ-48 usually has 4096 half-steps per revolution with this library
const int HALFSTEPS_PER_REV = 4096; 

// Dial Logic: 360 degrees / 6 numbers = 60 degrees per "tick"
const float DEGREES_PER_TICK = 60.0;

// Initialize stepper
TinyStepper stepper(HALFSTEPS_PER_REV, IN1, IN2, IN3, IN4);

void setup() {
  // Ensure pins are set as outputs for the ATtiny85
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  uint32_t startTime = millis();

  // 1. Move the hand exactly one position (60 degrees)
  // This library moves at its maximum default speed unless AccelMove is used.
  stepper.Move(DEGREES_PER_TICK); 

  // 2. Turn off coils to save battery and prevent heat on the ATtiny/Driver
  stepper.Disable();

  // 3. Calculate how much real-world time the 60-degree move took
  uint32_t elapsedTime = millis() - startTime;

  // 4. Wait for the remainder of the Eridian second before the next tick
  if (elapsedTime < ERIDIAN_SECOND_MS) {
    delay(ERIDIAN_SECOND_MS - elapsedTime);
  }
}
