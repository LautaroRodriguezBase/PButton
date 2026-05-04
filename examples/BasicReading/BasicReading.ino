#include <PButton.h>

#define BTN_PIN 2

// You must pulldown the pin to GND(LOW) with a 10 KΩ (Ohm) resistor.
PButton b(BTN_PIN, HIGH);

void setup(){
    Serial.begin(9600);
    delay(1000);
}

void loop(){
    // if the pin changes from LOW to HIGH
    if(b.read()){
        Serial.println("Button pressed");
    }
}