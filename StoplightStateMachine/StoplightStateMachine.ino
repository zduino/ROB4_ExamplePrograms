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

#define PHOTO_RESISTOR               A0

// Define states
#define S_NS_STOP                     0
#define S_NS_GO                       1
#define S_NS_CAUTION                  2
#define S_EW_STOP                     3
#define S_EW_GO                       4
#define S_EW_CAUTION                  5

#define S_NS_GO_CROSS                 6
#define S_NS_GO_YIELD                 7
#define S_EW_GO_CROSS                 8
#define S_EW_GO_YIELD                 9

#define S_NS_NIGHT_MODE              10
#define S_EW_NIGHT_MODE              11
// Global Variables
int LastState;
int CurrentState;
int NextState;
unsigned long nextStateChange = 0;

bool NS_Crosswalk_Requested = false;
bool EW_Crosswalk_Requested = false;

bool Night_Mode_Requested = false;

unsigned long CrosswalkFlashStart;

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

    pinMode(PHOTO_RESISTOR, INPUT);

    LastState = -1;
    CurrentState = S_NS_STOP;
    NextState = -1;
}

void loop() {
    // Collect sensor data
    if (digitalRead(NS_BTN_PIN)) {
        NS_Crosswalk_Requested = true;
    }
    if (digitalRead(EW_BTN_PIN)) {
        EW_Crosswalk_Requested = true;
    }

    if (analogRead(PHOTO_RESISTOR) < 350) {
        Night_Mode_Requested = true;
    }
    else if (analogRead(PHOTO_RESISTOR) > 400) {
        Night_Mode_Requested = false;
    }

    // Run state machine
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

        case S_NS_GO_CROSS:
            NS_Go_Cross();
            break;

        case S_NS_GO_YIELD:
            NS_Go_Yield();
            break;

        case S_EW_GO_CROSS:
            EW_Go_Cross();
            break;

        case S_EW_GO_YIELD:
            EW_Go_Yield();
            break;

        case S_NS_NIGHT_MODE:
            NS_Night_Mode();
            break;

        case S_EW_NIGHT_MODE:
            EW_Night_Mode();
            break;
    }

    // Updates state changes
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
        if (NS_Crosswalk_Requested) {
            NextState = S_NS_GO_CROSS;
            NS_Crosswalk_Requested = false;
        } else if (Night_Mode_Requested) {
            NextState = S_NS_NIGHT_MODE;
        } else {
            NextState = S_NS_GO;
        }
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
    digitalWrite(NS_LED_YLW_PIN, HIGH);
    digitalWrite(NS_LED_GRN_PIN, LOW);
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
        if (EW_Crosswalk_Requested) {
            NextState = S_EW_GO_CROSS;
            EW_Crosswalk_Requested = false;
        } else if (Night_Mode_Requested) {
            NextState = S_EW_NIGHT_MODE;
        } else {
            NextState = S_EW_GO;
        }
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

void NS_Go_Cross() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 10000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, LOW);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, HIGH);
    digitalWrite(NS_LED_BLU_PIN, HIGH);

    digitalWrite(EW_LED_RED_PIN, HIGH);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_NS_GO_YIELD;
    } else {
        NextState = S_NS_GO_CROSS;
    }
}

void NS_Go_Yield() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 5000;
        CrosswalkFlashStart = millis();
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, LOW);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, HIGH);
    digitalWrite(NS_LED_BLU_PIN, ((millis() - CrosswalkFlashStart) / 500 % 2 == 0));

    digitalWrite(EW_LED_RED_PIN, HIGH);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_NS_CAUTION;
    } else {
        NextState = S_NS_GO_YIELD;
    }
}

void EW_Go_Cross() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 5000;
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, HIGH);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, LOW);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, HIGH);
    digitalWrite(EW_LED_BLU_PIN, HIGH);

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_EW_GO_YIELD;
    } else {
        NextState = S_EW_GO_CROSS;
    }
}

void EW_Go_Yield() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        nextStateChange = millis() + 5000;
        CrosswalkFlashStart = millis();
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, HIGH);
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, LOW);
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, HIGH);
    digitalWrite(EW_LED_BLU_PIN, ((millis() - CrosswalkFlashStart) / 500 % 2 == 0));

    // Set next state here:
    if (nextStateChange <= millis()) {
        NextState = S_EW_CAUTION;
    } else {
        NextState = S_EW_GO_YIELD;
    }
}

void NS_Night_Mode() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        CrosswalkFlashStart = millis();
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, ((millis() - CrosswalkFlashStart) / 750 % 2 == 0));
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, ((millis() - CrosswalkFlashStart) / 750 % 2 == 0));
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (not Night_Mode_Requested) {
        NextState = S_NS_STOP;
    } else {
        NextState = S_NS_NIGHT_MODE;
    }
}

void EW_Night_Mode() {
    // Do initial state task here:
    if (CurrentState != LastState) {
        CrosswalkFlashStart = millis();
    }

    // Do state task here:
    digitalWrite(NS_LED_RED_PIN, ((millis() - CrosswalkFlashStart) / 750 % 2 == 0));
    digitalWrite(NS_LED_YLW_PIN, LOW);
    digitalWrite(NS_LED_GRN_PIN, LOW);
    digitalWrite(NS_LED_BLU_PIN, LOW);

    digitalWrite(EW_LED_RED_PIN, ((millis() - CrosswalkFlashStart) / 750 % 2 == 0));
    digitalWrite(EW_LED_YLW_PIN, LOW);
    digitalWrite(EW_LED_GRN_PIN, LOW);
    digitalWrite(EW_LED_BLU_PIN, LOW);

    // Set next state here:
    if (not Night_Mode_Requested) {
        NextState = S_EW_STOP;
    } else {
        NextState = S_EW_NIGHT_MODE;
    }
}
