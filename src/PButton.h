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

#include <Arduino.h>

#define TIME_DEBOUNCE_DELAY 50

class PButton{
    enum class HeldStatus{
        IDLE,
        START,
        COMPLETE,
        LOCKED
    };

    //Belongs to the class
    private:
        static uint64_t startTimes;
        static HeldStatus stateOfPressed;

    public:
        static bool areHeld(uint32_t timeAreHeld, bool arePressed);

    //Belongs to the object
    private:
        uint8_t pin;
        uint8_t state2Read;

        uint64_t startTime;//initial time for read if is pressed
        HeldStatus heldStatus;

        struct{
            // the current reading from the input pin
            uint8_t buttonState;
            // the previous reading from the input pin
            uint8_t lastButtonState;

            // the last time the output pin was toggled
            uint64_t lastDebounceTime;
            // the debounce time
            uint64_t debounceDelay;
        }readData;

    public:
        PButton(uint8_t pin, uint8_t state2Read, uint8_t debounceDelay = TIME_DEBOUNCE_DELAY);

        uint8_t getPin();

        bool isPressed();
        bool isHeld(uint32_t timeIsHeld);
};

#endif