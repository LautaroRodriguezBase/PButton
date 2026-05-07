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

#include "PButton.h"

PButton::PButton(uint8_t pin, uint8_t state2Read, uint8_t debounceDelay){
    this->pin = pin;
    this->state2Read = state2Read;

    this->readData.debounceDelay = debounceDelay;
    this->readData.lastButtonState = !state2Read;
    this->readData.lastDebounceTime = 0;

    pinMode(pin, INPUT);
}

// Class
uint64_t PButton::startTimes = 0;
PButton::HeldStatus PButton::heldStatus = PButton::HeldStatus::IDLE;

bool PButton::areHeld(bool arePressed){
    if(arePressed && (PButton::stateOfPressed == PButton::HeldStatus::IDLE) ){
        PButton::stateOfPressed == PButton::HeldStatus::START;
        dataBtn->lastHold = millis();

    }else if(arePressed && PButton::stateOfPressed == PButton::HeldStatus::START){
        if(PButton::stateOfPressed != PButton::HeldStatus::COMPLETE && millis() - PButton::startTimes >= PButton::timeAreHeld){
            PButton::stateOfPressed = PButton::HeldStatus::COMPLETE;
        }
    }else if( !arePressed && PButton::stateOfPressed == PButton::HeldStatus::START){
        PButton::stateOfPressed == PButton::HeldStatus::IDLE;
    }

    return (PButton::stateOfPressed == PButton::HeldStatus::COMPLETE);
}


// Object
bool PButton::isPressed(){
    bool res = false;
    uint8_t reading = digitalRead(this->pin);

    if (reading != this->readData.lastButtonState) {
        this->readData.lastDebounceTime = millis();
    }

    if ((millis() - this->readData.lastDebounceTime) > this->readData.debounceDelay) {
        if (reading != this->buttonState) {
            this->buttonState = reading;
            if (this->buttonState == this->state2Read) {
                res = true;
            }
        }
    }

    this->readData.lastButtonState = reading;

    return res;
}

bool PButton::isHeld(){
    bool state = false;
    if(isPress && !dataBtn->holdStart ){
        dataBtn->holdStart = true;
        dataBtn->lastHold = millis();
    }else if(isPress && dataBtn->holdStart){
        funcPtr();
        if(!dataBtn->holdComplete && millis() - dataBtn->lastHold >= timeTo){
            dataBtn->holdComplete = true;
            state = true;
        }
    }else if( !isPress && dataBtn->holdStart){
        dataBtn->holdStart = false;
        dataBtn->holdComplete = false;
    }

    return state;
}

uint8_t PButton::getPin(){
    return this->pin;
}