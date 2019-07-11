/* StoplightStateMachine.ino
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 10, 2019
 */

// Define pins
#define NS_LED_RED_PIN                6
#define NS_LED_YLW_PIN                5
#define NS_LED_GRN_PIN                4
#define NS_LED_BLU_PIN                3
#define NS_BTN_PIN                    2

#define EW_LED_RED_PIN               11
#define EW_LED_YLW_PIN               10
#define EW_LED_GRN_PIN                9
#define EW_LED_BLU_PIN                8
#define EW_BTN_PIN                    7

// Define states
#define S_NS_STOP                     0
#define S_NS_GO                       1
#define S_NS_CAUTION                  2
#define S_EW_STOP                     3
#define S_EW_GO                       4
#define S_EW_CAUTION                  5

// Global Variables
int LastState;
int CurrentState;
int NextState;
unsigned long nextStateChange = 0;

void setup() {
    pinMode(NS_LED_RED_PIN, OUTPUT);
    pinMode(NS_LED_YLW_PIN, OUTPUT);
    pinMode(NS_LED_GRN_PIN, OUTPUT);
    pinMode(NS_LED_BLU_PIN, OUTPUT);
    pinMode(NS_BTN_PIN, INPUT);

    pinMode(EW_LED_RED_PIN, OUTPUT);
    pinMode(EW_LED_YLW_PIN, OUTPUT);
    pinMode(EW_LED_GRN_PIN, OUTPUT);
    pinMode(EW_LED_BLU_PIN, OUTPUT);
    pinMode(EW_BTN_PIN, INPUT);

    LastState = -1;
    CurrentState = S_NS_STOP;
    NextState = -1;
}

void loop() {
    switch (CurrentState) {
        case S_NS_STOP:
            NS_Stop();
            break;

        case S_NS_GO:
            NS_Go();
            break;

        case S_NS_CAUTION:
            NS_Caution();
            break;

        case S_EW_STOP:
            EW_Stop();
            break;

        case S_EW_GO:
            EW_Go();
            break;

        case S_EW_CAUTION:
            EW_Caution();
            break;
    }

    LastState = CurrentState;
    CurrentState = NextState;
}

void NS_Stop() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 3000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, HIGH);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, HIGH);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_NS_GO;
    } else {
        NextState = S_NS_STOP;
    }
}

void NS_Go() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 15000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, LOW);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, HIGH);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, HIGH);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_NS_CAUTION;
    } else {
        NextState = S_NS_GO;
    }
}

void NS_Caution() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 3000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, LOW);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, HIGH);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, HIGH);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_EW_STOP;
    } else {
        NextState = S_NS_CAUTION;
    }
}

void EW_Stop() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 3000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, HIGH);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, HIGH);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_EW_GO;
    } else {
        NextState = S_EW_STOP;
    }
}

void EW_Go() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 15000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, HIGH);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, LOW);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, HIGH);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_EW_CAUTION;
    } else {
        NextState = S_EW_GO;
    }
}

void EW_Caution() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 3000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, HIGH);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, LOW);
    digitalWrite(EW_LED_YLW_PIN, HIGH);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_NS_STOP;
    } else {
        NextState = S_EW_CAUTION;
    }
}