#include <RoxMux.h>

// MUX_TOTAL is the number of 74HC595s that you have chained together
// if you have more than 1 then change it to that number.
#define MUX_TOTAL 1
Rox74HC595 <MUX_TOTAL> mux;

// which pin of the mux chain to read
#define MUX_PIN 0

// pins for 74HC595
#define PIN_DATA    23 // pin 14 on 74HC595 (DATA)
#define PIN_LATCH   22 // pin 12 on 74HC595 (LATCH)
#define PIN_CLK     21 // pin 11 on 74HC595 (CLK)
// PIN_PWM MUST BE A PWM CAPABLE PIN
// set it's value to -1 if you do not wish to control the brightness
// if you don't need to control the brightness you must wire
// pin 13 on the 74HC595 to ground.
#define PIN_PWM     -1  // pin 13 on 74HC595

// Wire pin 11 to VCC

unsigned long prevTime = 0;
uint8_t counter = 0;
bool state = true;
const uint16_t totalPins = 8 * MUX_TOTAL;

// if you use a PWM pin you can set the brightness for all LEDs.
uint8_t brightness = 255;

void setup(){
  Serial.begin(115200);
  mux.begin(PIN_DATA, PIN_LATCH, PIN_CLK, PIN_PWM);
  prevTime = millis();

  // set the brightness, only works if you set and wired a PWM pin
  // 0 will turn them off, 255 will do a digitalWrite HIGH
  mux.setBrightness(255);
}

void loop(){
  // the update() method will only write to the 74HC595 whenever a pin value
  // has changed from it's buffer.
  mux.update();
  // turn each led on then off every 500 milliseconds
  if((millis()-prevTime) > 500){
    // change the brightness every
    mux.writePin(counter, state);
    counter++;
    if(counter>=totalPins){
      counter = 0;
      state = !state;
    }
    prevTime = millis();
  }
}