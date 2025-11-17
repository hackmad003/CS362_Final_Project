/*
 * RC Car - FRONT ARDUINO (Master Receiver + Front Motor Control)
 * Board: Arduino UNO R4 WiFi
 * 
 * Wiring: TX Pin 1 → Middle RX Pin 0
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>

// NRF24L01 setup
RF24 radio(7, 8); // CE, CSN
const uint64_t pipeIn = 0xE9E8F0F0E1LL;

// SoftwareSerial using pins 0 (RX) and 1 (TX)
const int RX_PIN = 0;  // Not used for receiving in this case
const int TX_PIN = 1;  // Transmit to middle Arduino
SoftwareSerial middleSerial(RX_PIN, TX_PIN);

// Data structure
struct Data_Package {
  int xAxis;
  int yAxis;
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

unsigned long lastReceiveTime = 0;
bool validSignalReceived = false;
const unsigned long TIMEOUT = 500;

void setup() {
  // Initialize SoftwareSerial for middle Arduino
  middleSerial.begin(9600);
  
  // Configure motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  data.xAxis = 512;
  data.yAxis = 512;
  data.headlightBtn = false;
  
  stopMotors();
  
  // Initialize NRF
  radio.begin();
  radio.openReadingPipe(1, pipeIn);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
  delay(100);
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis();
    
    if (data.xAxis > 50 && data.xAxis < 1000 && data.yAxis > 50 && data.yAxis < 1000) {
      validSignalReceived = true;
    }
    
    if (validSignalReceived) {
      controlFrontMotors(data.xAxis, data.yAxis);
    } else {
      stopMotors();
    }
    
    // Send to middle via SoftwareSerial on pin 1
    middleSerial.write((byte*)&data, sizeof(Data_Package));
  }
  
  if (millis() - lastReceiveTime > TIMEOUT) {
    validSignalReceived = false;
    stopMotors();
  }
}

void controlFrontMotors(int x, int y) {
  if (y > 600) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);
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

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}