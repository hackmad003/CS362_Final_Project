/*
 * RC Remote - Dual BLE Connection
 * Connects to BOTH Front and Back cars via Bluetooth
 */
#include <ArduinoBLE.h>

struct JoystickData {
  int16_t x;
  int16_t y;
};
JoystickData data;

// FRONT CAR UUIDs
const char* frontServiceUuid = "19B10000-E8F2-537E-4F6C-D104768A1214";
const char* frontCharUuid = "19B10001-E8F2-537E-4F6C-D104768A1214";

// BACK CAR UUIDs
const char* backServiceUuid = "19B10000-E8F2-537E-4F6C-D104768A1215";
const char* backCharUuid = "19B10001-E8F2-537E-4F6C-D104768A1216";

BLEDevice frontCar;
BLEDevice backCar;
BLECharacteristic frontChar;
BLECharacteristic backChar;

bool frontConnected = false;
bool backConnected = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  if (!BLE.begin()) {
    Serial.println("❌ BLE Failed!");
    while (1);
  }
  
  Serial.println("🚗 Remote Started - Scanning for cars...");
  BLE.scan();
}

void loop() {
  // Try to connect to front car if not connected
  if (!frontConnected) {
    BLEDevice peripheral = BLE.available();
    if (peripheral && peripheral.localName() == "R4_RC_Car") {
      Serial.println("🔵 Found Front Car!");
      if (connectToFrontCar(peripheral)) {
        Serial.println("✅ Front Car Connected!");
        frontConnected = true;
      }
      delay(100);
      BLE.scan(); // Resume scanning for back car
    }
  }
  
  // Try to connect to back car if not connected
  if (!backConnected) {
    BLEDevice peripheral = BLE.available();
    if (peripheral && peripheral.localName() == "BACK_CAR_R4") {
      Serial.println("🟢 Found Back Car!");
      if (connectToBackCar(peripheral)) {
        Serial.println("✅ Back Car Connected!");
        backConnected = true;
      }
      delay(100);
      BLE.scan(); // Keep scanning if needed
    }
  }
  
  // Check if connections are still alive
  if (frontConnected && !frontCar.connected()) {
    Serial.println("⚠️ Front Car disconnected");
    frontConnected = false;
    BLE.scan();
  }
  
  if (backConnected && !backCar.connected()) {
    Serial.println("⚠️ Back Car disconnected");
    backConnected = false;
    BLE.scan();
  }
  
  // If BOTH connected, send joystick data
  if (frontConnected && backConnected) {
    digitalWrite(LED_BUILTIN, HIGH);
    
    // Read joystick once
    data.x = analogRead(A0);
    data.y = analogRead(A1);
    
    // Send to BOTH cars
    if (frontChar) {
      frontChar.writeValue((byte*)&data, sizeof(data));
    }
    
    if (backChar) {
      backChar.writeValue((byte*)&data, sizeof(data));
    }
    
    Serial.print("📤 X: "); Serial.print(data.x);
    Serial.print(" Y: "); Serial.println(data.y);
    
    delay(50);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

bool connectToFrontCar(BLEDevice peripheral) {
  BLE.stopScan();
  
  if (peripheral.connect()) {
    if (peripheral.discoverAttributes()) {
      frontChar = peripheral.characteristic(frontCharUuid);
      
      if (frontChar) {
        frontCar = peripheral;
        return true;
      } else {
        Serial.println("❌ Front characteristic not found");
        peripheral.disconnect();
      }
    } else {
      Serial.println("❌ Front attributes discovery failed");
      peripheral.disconnect();
    }
  } else {
    Serial.println("❌ Front connection failed");
  }
  
  return false;
}

bool connectToBackCar(BLEDevice peripheral) {
  BLE.stopScan();
  
  if (peripheral.connect()) {
    if (peripheral.discoverAttributes()) {
      backChar = peripheral.characteristic(backCharUuid);
      
      if (backChar) {
        backCar = peripheral;
        return true;
      } else {
        Serial.println("❌ Back characteristic not found");
        peripheral.disconnect();
      }
    } else {
      Serial.println("❌ Back attributes discovery failed");
      peripheral.disconnect();
    }
  } else {
    Serial.println("❌ Back connection failed");
  }
  
  return false;
}