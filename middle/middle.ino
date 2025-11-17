/*
 * RC Car - MIDDLE ARDUINO (Lights Control & Pass-Through)
 * Board: Arduino UNO R4 WiFi
 * 
 * Wiring: 
 * - Front TX Pin 1 → Middle RX Pin 0
 * - Middle TX Pin 1 → Back RX Pin 0
 */

#include <SoftwareSerial.h>

// SoftwareSerial for receiving from front (pin 0) and sending to back (pin 1)
const int RX_PIN = 0;  // Receive from front
const int TX_PIN = 1;  // Send to back
SoftwareSerial serial01(RX_PIN, TX_PIN);

// Data structure
struct Data_Package {
  int xAxis;
  int yAxis;
  bool headlightBtn;
};

Data_Package data;

// LED pins
const int HEADLIGHT_PIN = 2;
const int BRAKE_PIN = 3;

bool headlightsOn = false;
bool lastHeadlightBtn = false;

void setup() {
  // Initialize SoftwareSerial on pins 0 and 1
  serial01.begin(9600);
  
  pinMode(HEADLIGHT_PIN, OUTPUT);
  pinMode(BRAKE_PIN, OUTPUT);
  
  digitalWrite(HEADLIGHT_PIN, LOW);
  digitalWrite(BRAKE_PIN, LOW);
  
  delay(100);
}

void loop() {
  if (serial01.available() >= sizeof(Data_Package)) {
    serial01.readBytes((byte*)&data, sizeof(Data_Package));
    
    // Control headlights
    if (data.headlightBtn && !lastHeadlightBtn) {
      headlightsOn = !headlightsOn;
      digitalWrite(HEADLIGHT_PIN, headlightsOn ? HIGH : LOW);
    }
    lastHeadlightBtn = data.headlightBtn;
    
    // Control brake lights
    if (data.yAxis >= 400 && data.yAxis <= 600) {
      digitalWrite(BRAKE_PIN, HIGH);
    } else if (data.yAxis < 400) {
      digitalWrite(BRAKE_PIN, HIGH);
    } else {
      digitalWrite(BRAKE_PIN, LOW);
    }
    
    // Forward to back Arduino
    serial01.write((byte*)&data, sizeof(Data_Package));
  }
}