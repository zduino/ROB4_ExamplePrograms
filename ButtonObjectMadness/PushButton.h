/* PushButton.h
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 23, 2019
 */

#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

class PushButton {
public:
    PushButton(int pinNum);
    PushButton(int pinNum, bool pullDown);
    void setOnPress(void (*f)());
    void setWhilePressed(void (*f)());
    void setOnRelease(void (*f)());
    void setWhileReleased(void (*f)());
    void update();
private:
    int _DebounceTime;
    int _PinNum;
    bool _PullDown;
    bool _State;
    bool _StateLast;
    unsigned long _LastStateChange;
    void (*_OnPress)();
    void (*_WhilePressed)();
    void (*_OnRelease)();
    void (*_WhileReleased)();
};

#endif // PUSH_BUTTON_H
