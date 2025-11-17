/*
 * RC Car - BACK ARDUINO (Rear Motor Control)
 * Board: ELEGOO UNO R3
 * 
 * Wiring: Middle TX Pin 1 → Back RX Pin 0
 */

#include <cstddef>
#include <cstdint>
#include <ctime>

#include <SoftwareSerial.h>

#include <Pin.hpp>

// SoftwareSerial on pin 0 (RX) and pin 1 (TX - not used)
constexpr int RX_PIN = 0;
constexpr int TX_PIN = 1;  // Not used but required for constructor
SoftwareSerial middleSerial(RX_PIN, TX_PIN);

// Data structure
struct Data_Package {
  std::int32_t xAxis;
  std::int32_t yAxis;
  bool headlightBtn;
};

Data_Package data;

// L298N pins
#define ENA 5
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 6
#define ENB 9

std::time_t lastReceiveTime = 0;
constexpr std::time_t TIMEOUT = 500;

void setup(void) {
  // Initialize SoftwareSerial
  middleSerial.begin(9600);
  
  pinMode(ENA, OUTPUT); // Back Left wheel
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT); // Back Right wheel
  
  data.xAxis = 512;
  data.yAxis = 512;
  data.headlightBtn = false;
  
  stopMotors();
  
  delay(100);
}

void loop(void) {
  if (middleSerial.available() >= sizeof(Data_Package)) {
    middleSerial.readBytes((byte*)&data, sizeof(Data_Package));
    
    lastReceiveTime = millis();
    
    controlRearMotors(data.xAxis, data.yAxis);
  }
  
  if (millis() - lastReceiveTime > TIMEOUT) {
    stopMotors();
  }
}

void controlRearMotors(std::int32_t x, std::int32_t y) noexcept {
  if (y > 600) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 150); // Back Left wheel
    
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 150);
  }
  else if (y < 400) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);

  }
  else if (x < 400) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
  }
  else if (x > 600) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
  }
  else {
    stopMotors();
  }
}

void stopMotors(void) noexcept {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}