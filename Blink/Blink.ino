/* Blink.ino
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 10, 2019
 */

// Define "LED_PIN" as the number 13 to make the
// code easier to read. The text gets replaced by
// the complier so no variable is used at runtime.
#define LED_PIN              13

// Setup is a built in function that gets called once
// initially upon start-up or reset on the arduino.
void setup() {
    // tell the arduino to set the LED_PIN to be an output
    pinMode(LED_PIN, OUTPUT);
}

// Loop is a built in function that gets called repeatedly
// after the setup has completed. The main program should
// written here.
void loop() {
    // Write a digital signal to LED_PIN of HIGH (aka +5V).
    digitalWrite(LED_PIN, HIGH);
    // Have the arduino wait 1000 milliseconds before moving
    // to the next command.
    delay(1000);
    // Write a digital signal to LED_PIN of LOW (aka 0V or GND).
    digitalWrite(LED_PIN, LOW);
    // Have the arduino wait 1000 milliseconds before moving
    // to the next command.
    delay(1000);

}
