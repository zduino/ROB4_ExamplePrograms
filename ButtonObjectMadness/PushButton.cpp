#include "PushButton.h"
#include "Arduino.h"

extern pinMode();

PushButton::PushButton(int pinNum) {
    this->_PinNum = pinNum;
    this->_PullDown = true;
    this->_DebounceTime = 100;
    _LastStateChange = 0;
    pinMode(this->_PinNum, INPUT);
}

PushButton::PushButton(int pinNum, bool pullDown) {
    this->_PinNum = pinNum;
    this->_PullDown = pullDown;
    this->_DebounceTime = 100;
    this->_LastStateChange = 0;
}

void PushButton::setOnPress(void (*f)()) {
    this->_OnPress = f;
}

void PushButton::setWhilePressed(void (*f)()) {
    this->_WhilePressed = f;
}

void PushButton::setOnRelease(void (*f)()) {
    this->_OnRelease = f;
}

void PushButton::setWhileReleased(void (*f)()) {
    this->_WhileReleased = f;
}

void PushButton::update() {
    if (millis() > _LastStateChange + _DebounceTime) {
        
        _State = digitalRead(_PinNum);

        if (_State == _PullDown) {
            if (_State != _StateLast) {
                if (_OnPress != NULL) {
                    _OnPress();
                }
                _LastStateChange = millis();
            }

            if (_WhilePressed != NULL) {
                _WhilePressed();
            }
        }
        
        else {
            if (_State != _StateLast) {
                if (_OnRelease != NULL) {
                    _OnRelease();
                }
                _LastStateChange = millis();
            }
        
            if (_WhileReleased != NULL) {
                _WhileReleased();
            }
        }
        _StateLast = _State;
    }
}
