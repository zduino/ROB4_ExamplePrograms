/* ButtonObjectMadness.ino
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 23, 2019
 */

// Include definition of PushButton type
#include "PushButton.h"

// define the button pin
#define BTN_BLUE_PIN            2

// Create an instance of the PushButton type called "btnBlue".
PushButton btnBlue(BTN_BLUE_PIN);

// Setup routine
void setup() {
    // Setup the serial link
    Serial.begin(115200);

    // Set the function "onPress" as the function to be run during
    // an on press event for the button.
    btnBlue.setOnPress(onPress);
}

// Loop routine
void loop() {
    // Update the button frequently.
    btnBlue.update();
}

void onPress() {
    // Print to the serial monitor when the button is pressed.
    Serial.println("Hello World! I be sad.");
}
