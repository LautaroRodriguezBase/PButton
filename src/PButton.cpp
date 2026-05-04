/**
 * Copyright 2026 Lautaro Ezequiel Rodriguez Base
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/_stdint.h>
#include "esp32-hal-gpio.h"
#include "PButton.h"

PButton::PButton(uint8_t pin, uint8_t state2Read, uint8_t debounceDelay){
    this->pin = pin;
    this->state2Read = state2Read;
    this->debounceDelay = debounceDelay;
    this->lastButtonState = LOW;
    this->lastDebounceTime = 0;
    pinMode(pin, INPUT_PULLUP);
}

bool PButton::read(){
    bool res = false;
    uint8_t reading = digitalRead(this->pin);

    if (reading != this->lastButtonState) {
        this->lastDebounceTime = millis();
    }

    if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
        if (reading != this->buttonState) {
            this->buttonState = reading;
            if (this->buttonState == this->state2Read) {
                // Tal vez acá habría que agregar un código que
                // lea si se mantuvo presionado por X cantidad de tiempo
                res = true;
            }
        }
    }

    this->lastButtonState = reading;

    return res;
}

uint8_t PButton::getPin(){
    return this->pin;
}