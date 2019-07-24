/* ButtonObjectMadness.ino
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 23, 2019
 */
#include "PushButton.h"

#define BTN_BLUE_PIN            2

PushButton btnBlue(BTN_BLUE_PIN);

void setup() {
    Serial.begin(115200);
    btnBlue.setOnPress(onPress);
}

void loop() {
    btnBlue.update();
}

void onPress() {
    Serial.println("Hello World!");
}
