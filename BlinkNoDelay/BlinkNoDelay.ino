/* BlinkNoDelay.ino
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 10, 2019
 */

// Define "LED_PIN" as the number 13 to make the
// code easier to read. The text gets replaced by
// the complier so no variable is used at runtime.
#define LED_PIN              13
// Define "BLINK_DURATION" as the number 1000 to make the
// code easier to read. The text gets replaced by
// the complier so no variable is used at runtime.
#define BLINK_DURATION     1000

// Declare and initialize a global variable to keep
// track of the previous light change. The variable
// has no negative sign (must be positive) and is a 
// type long (really big integer).
unsigned long LastBlink = 0;

// Declare and initialize a global variable to keep
// track of the previous light state. It is a type
// "bool" or boolean meaning it is true or false. In
// this case true will mean the light is on, and false
// will mean it is off.
bool LED_State = false;

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
    // Check the time and see if it ready to change the LED
    // the current time is compared to the time of the last 
    // blink plus the duration of the blink
    if (millis() > LastBlink + BLINK_DURATION) {
        // Set the LED state to the opposite of its current 
        // state.
        LED_State = not LED_State;
        // Set the LastBlink time to the current time to 
        // restart the blink timer
        LastBlink = millis();
    }

    // Write a digital signal to the value of LED_State
    // (true or false -> on or off).
    digitalWrite(LED_PIN, LED_State);
}
