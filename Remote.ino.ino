/*
 * RC Remote - BLE SENDER (Central)
 * Board: Arduino UNO R4 WiFi
 */

#include <ArduinoBLE.h>

struct JoystickData {
  int16_t x;
  int16_t y;
};

JoystickData data;

void setup() {
  Serial.begin(9600);
  
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  Serial.println("Remote Started. Scanning for Car...");
  BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214"); // Scan only for our car
}

void loop() {
  // Check if a peripheral (Car) is found
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.print("Found "); Serial.print(peripheral.localName());
    Serial.println(". Connecting...");

    BLE.stopScan(); // Stop scanning to save power and connect faster

    if (connectToCar(peripheral)) {
      Serial.println("Connected to Car!");
      
      while (peripheral.connected()) {
        controlCar(peripheral);
      }
      
      Serial.println("Disconnected from Car.");
    }
    
    // If we lost connection, start scanning again
    BLE.scanForUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
    Serial.println("Scanning again...");
  }
}

bool connectToCar(BLEDevice peripheral) {
  if (!peripheral.connect()) {
    return false;
  }
  if (!peripheral.discoverAttributes()) {
    peripheral.disconnect();
    return false;
  }
  return true;
}

void controlCar(BLEDevice peripheral) {
  // Read Analog Joysticks
  data.x = analogRead(A0);
  data.y = analogRead(A1);

  // Get the characteristic we want to write to
  BLECharacteristic commandChar = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");

  if (commandChar) {
    // Send the struct as raw bytes
    commandChar.writeValue((byte*)&data, sizeof(data));
    
    Serial.print("Sent X: "); Serial.print(data.x);
    Serial.print(" Y: "); Serial.println(data.y);
  }
  
  delay(50); // Do not flood the BLE connection; 50ms is safe
}