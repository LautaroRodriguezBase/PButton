#ifndef PBUTTON_h
#define PBUTTON_h

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
#include <Arduino.h>

#define TIME_DEBOUNCE_DELAY 50

class PButton{
    private:
        // the current reading from the input pin
        uint8_t buttonState;
        // the previous reading from the input pin
        uint8_t lastButtonState;

        uint64_t lastDebounceTime; // the last time the output pin was toggled
        uint64_t debounceDelay;   // the debounce time; increase if the output flickers

        uint8_t state2Read;
        uint8_t pin;
    public:
        PButton(uint8_t pin, uint8_t state2Read, uint8_t debounceDelay = TIME_DEBOUNCE_DELAY);

        bool read();
        uint8_t getPin();
};

#endif