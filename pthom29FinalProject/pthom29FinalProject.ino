/*


This code was uploaded to Ahmads Arduino UNO R4 Wi-FI






*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const uint64_t pipeIn = 0xE9E8F0F0E1LL;

struct Data_Package {
  int xAxis;
  int yAxis;
};

Data_Package data;

#define ENA 5
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 6
#define ENB 9

unsigned long lastReceiveTime = 0;
bool validSignalReceived = false;

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

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

void loop() {
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
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
      // Backward
      else if (y < 400) {
        Serial.println("BACKWARD");
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
      // Left
      else if (x < 400) {
        Serial.println("LEFT");
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
      // Right
      else if (x > 600) {
        Serial.println("RIGHT");
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
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
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}