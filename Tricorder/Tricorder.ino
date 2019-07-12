/* Tricorder.ino
 * Board: Sparkfun RedBoard
 * Author: Neko'z
 * Date: July 10, 2019
 */

/* Scotie: "Why is the tricorder not working."
 * Kirt: "I was playing with the code!"
 * Scotie: "NOOOOO! WHY YOU DO THIS TO ME!"
 * Kirt: *smiles*
 * Scotie: "I guess I'll clean up your mess captain..."
 * Scotie emails the code to iD CE Academy...
 * Students fix code and email it back...
 * Everyone is unhappy :(
 * A bear eats a fish.
 */

// Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

#include <Wire.h>
#include "SparkFun_MMA8452Q.h"
#include<LiquidCrystal.h>

#define TEMP_PIN      A0
#define LIGHT_PIN     A1
#define BTN_PIN       A2

LiquidCrystal LCD(13,12,11,10,9);
MMA8452Q Accel;

#define S_DISP_TEMP    0
#define S_DISP_LIGHT   1
#define S_DISP_ACCEL   2

void setup() {
    Serial.begin(9600);
    LCD.begin(16,2);
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("Setup...");
    Serial.println("Setup...");

    pinMode(TEMP_PIN, INPUT);
    pinMode(LIGHT_PIN, INPUT);
    pinMode(BTN_PIN, INPUT);

    Wire.begin();
    Accel.begin();

    LCD.print(" Complete!");
    Serial.println("Complete!");
}

void loop() {
    switch (displayState) {
        case S_DISP_ACCEL:
            displayAccel();
            break;
    }
}

void displaySummary() {

}

void displayTemp() {
    float t = ((float)analogRead(TEMP_PIN)/1023*5-.5)*100;
}

void displayLight() {
    float l = ((float)analogRead(LIGHT_PIN)/1023*100);
}

void displayAccel() {
    float x = Accel.getCalculatedX();
    float y = Accel.getCalculatedY();
    float z = Accel.getCalculatedZ();
}