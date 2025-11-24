/*
 * RC Remote - SENDER (Central)
 * Matches the "Connection" method used in your Car.ino
 */
#include <ArduinoBLE.h>

struct JoystickData {
  int16_t x;
  int16_t y;
};
JoystickData data;

// These MUST match the UUIDs in your Car.ino
const char* deviceServiceUuid = "19B10000-E8F2-537E-4F6C-D104768A1214";
const char* deviceServiceCharUuid = "19B10001-E8F2-537E-4F6C-D104768A1214";

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); // Orange LED
  
  if (!BLE.begin()) {
    Serial.println("BLE Failed!");
    while (1); 
  }
  
  Serial.println("Remote Started. Scanning...");
  // Scan specifically for the Car's Service UUID
  BLE.scanForUuid(deviceServiceUuid);
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // Found a device with the right UUID!
    Serial.print("Found: "); Serial.println(peripheral.localName());
    BLE.stopScan(); 

    connectToCar(peripheral);
    
    // If we get here, we disconnected. Start scanning again.
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Scanning again...");
    BLE.scanForUuid(deviceServiceUuid);
  }
}

void connectToCar(BLEDevice peripheral) {
  Serial.println("Connecting...");

  if (peripheral.connect()) {
    Serial.println("Connected!");
    digitalWrite(LED_BUILTIN, HIGH); // LED ON = Connected
    
    if (peripheral.discoverAttributes()) {
      // Get the specific Characteristic we want to write to
      BLECharacteristic cmdChar = peripheral.characteristic(deviceServiceCharUuid);
      
      if (cmdChar) {
        while (peripheral.connected()) {
          // 1. Read Joystick
          data.x = analogRead(A0);
          data.y = analogRead(A1);

          // 2. Send Data
          cmdChar.writeValue((byte*)&data, sizeof(data));

          // 3. Debug Print
          Serial.print("Sent -> X: "); Serial.print(data.x);
          Serial.print(" Y: "); Serial.println(data.y);
          
          delay(50); // Don't flood the connection
        }
      } else {
        Serial.println("Error: Characteristic not found!");
      }
    } else {
      Serial.println("Error: Attributes not found!");
    }
  } else {
    Serial.println("Error: Could not connect!");
  }
}