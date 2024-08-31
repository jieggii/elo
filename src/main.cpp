#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "SparkFun_SCD4x_Arduino_Library.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
SCD4x mySensor;

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    if (!mySensor.begin()) {
        Serial.println("Sensor not detected. Please check wiring. Freezing...");
        while (true) {}
    }
}

void loop() {
    lcd.clear();
    lcd.print("elo");

    delay(1000);

    if (mySensor.readMeasurement()) // readMeasurement will return true when fresh data is available
    {
        Serial.println();

        Serial.print("CO2(ppm):");
        Serial.print(mySensor.getCO2());

        Serial.print("\tTemperature(C):");
        Serial.print(mySensor.getTemperature(), 1);

        Serial.print("\tHumidity(%RH):");
        Serial.print(mySensor.getHumidity(), 1);

        Serial.println();
    }
    else {
        Serial.print(F("."));
    }

    delay(500);
}