/* SerialFormating.ino
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 10, 2019
 */

// Setup is a built in function that gets called once
// initially upon start-up or reset on the arduino.
void setup() {
    // Start the Serial interface (uses digital pins 0 
    // and 1) at a baud rate (bits per second) of 9600
    Serial.begin(9600);
}

// Loop is a built in function that gets called repeatedly
// after the setup has completed. The main program should
// written here.
void loop() {
    // Print a single string and add a newline character
    // at the end of the string.
    Serial.println("Hello iD Tech Academies!");

    // Wait a second before moving to next command.
    delay(1000);
    // Print a new line character
    Serial.println();

    // Print a string with out a new line character
    Serial.print("This is how to put a number, ");
    // Print a number with out a new line character
    Serial.print(7);
    // Print a string with a new line character
    Serial.print(", mid line.");

    // Wait a second before moving to next command.
    delay(1000);
    // Print a new line character
    Serial.println();

    // Here is examples of special characters
    /// Tab
    Serial.println("\tTabbed line.");
    /// New Line
    Serial.println("New\n   Line");
    /// quotation mark
    Serial.println("Arduio: \"There are quotes?!\"");
    /// back slash
    Serial.println("¯\\_(..)_/¯");
    
    // Wait a second before moving to next command.
    delay(1000);
    // Print a new line character
    Serial.println();
}
