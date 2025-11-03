/*
This code was uploaded to Ahmads Arduino UNO R4 Wi-FI
*/

// C/C++ includes
#include <cstddef>
#include <cstdint>
#include <array>

// 3rd party includes
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Local includes
#include "DigitalPin.hpp"
#include "AnalogPin.hpp"

RF24 radio(7, 8);
constexpr std::uint64_t pipeIn = 0xE9E8F0F0E1LL;

struct Data_Package {
  int xAxis;
  int yAxis;
};

Data_Package data;

//#define ENA 5 // analog
//#define IN1 2 // digital
//#define IN2 3 // digital
//#define IN3 4 // digital
//#define IN4 6 // digital
//#define ENB 9 // analog

arduino::AnalogPin ENA(5, OUTPUT);
arduino::AnalogPin ENB(9, OUTPUT);

std::array<arduino::DigitalPin, 4> IN = {
  arduino::DigitalPin(2, OUTPUT),
  arduino::DigitalPin(3, OUTPUT),
  arduino::DigitalPin(4, OUTPUT),
  arduino::DigitalPin(6, OUTPUT)
};

unsigned long lastReceiveTime = 0;
bool validSignalReceived = false;

void setup(void) noexcept {
  Serial.begin(9600);

  //pinMode(ENA, OUTPUT);
  //pinMode(IN1, OUTPUT);
  //pinMode(IN2, OUTPUT);
  //pinMode(IN3, OUTPUT);
  //pinMode(IN4, OUTPUT);
  //pinMode(ENB, OUTPUT);

  // Initialize to safe center values
  data.xAxis = 512;
  data.yAxis = 512;

  // FORCE STOP on startup
  stopMotors();

  radio.begin();
  radio.openReadingPipe(1, pipeIn);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  
  Serial.println("Car ready - waiting for valid signal...");
}

void loop(void) noexcept {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis();

    int x = data.xAxis;
    int y = data.yAxis;

    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" | Y: ");
    Serial.println(y);

    // Check if we're receiving valid joystick data (not 0,0 garbage)
    if (x > 50 && x < 1000 && y > 50 && y < 1000) {
      validSignalReceived = true;
    }

    // Only respond to commands if we've received valid signal
    if (validSignalReceived) {
      // Forward
      if (y > 600) {
        Serial.println("FORWARD");

        IN[0].write(HIGH);
        IN[1].write(LOW);
        IN[2].write(HIGH);
        IN[3].write(LOW);

        ENA.write(150);
        ENB.write(150);

        //digitalWrite(IN1, HIGH);
        //digitalWrite(IN2, LOW);
        //digitalWrite(IN3, HIGH);
        //digitalWrite(IN4, LOW);
        //analogWrite(ENA, 150);
        //analogWrite(ENB, 150);
      }
      // Backward
      else if (y < 400) {
        Serial.println("BACKWARD");
        //digitalWrite(IN1, LOW);
        //digitalWrite(IN2, HIGH);
        //digitalWrite(IN3, LOW);
        //digitalWrite(IN4, HIGH);
        //analogWrite(ENA, 150);
        //analogWrite(ENB, 150);

        IN[0].write(LOW);
        IN[1].write(HIGH);
        IN[2].write(LOW);
        IN[3].write(HIGH);

        ENA.write(150);
        ENB.write(150);
      }
      // Left
      else if (x < 400) {
        Serial.println("LEFT");
        //digitalWrite(IN1, LOW);
        //digitalWrite(IN2, HIGH);
        //digitalWrite(IN3, HIGH);
        //digitalWrite(IN4, LOW);
        //analogWrite(ENA, 150);
        //analogWrite(ENB, 150);

        IN[0].write(LOW);
        IN[1].write(HIGH);
        IN[2].write(HIGH);
        IN[3].write(LOW);

        ENA.write(150);
        ENB.write(150);
      }
      // Right
      else if (x > 600) {
        Serial.println("RIGHT");

        IN[0].write(HIGH);
        IN[1].write(LOW);
        IN[2].write(LOW);
        IN[3].write(HIGH);

        ENA.write(150);
        ENB.write(150);

        //digitalWrite(IN1, HIGH);
        //digitalWrite(IN2, LOW);
        //digitalWrite(IN3, LOW);
        //digitalWrite(IN4, HIGH);
        //analogWrite(ENA, 150);
        //analogWrite(ENB, 150);
      }
      // Stop (centered)
      else {
        stopMotors();
      }
    } else {
      Serial.println("Ignoring invalid data");
      stopMotors();
    }
  }
  
  // Stop if no signal for 500ms
  if (millis() - lastReceiveTime > 500) {
    validSignalReceived = false;
    stopMotors();
  }
}

void stopMotors() {
  for (std::size_t i = 0; i < 4; i++) {
    IN[i].write(LOW);
  }

  ENA.write(0);
  ENB.write(0);

  //digitalWrite(IN1, LOW);
  //digitalWrite(IN2, LOW);
  //digitalWrite(IN3, LOW);
  //digitalWrite(IN4, LOW);
  //analogWrite(ENA, 0);
  //analogWrite(ENB, 0);
}