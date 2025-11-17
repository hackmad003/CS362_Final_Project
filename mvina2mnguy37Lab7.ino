/*
Lab 7 - Communication Between Adruinos

Name: Mike Vinanzaca & Michael Nguyen
UIN: 663224774, 653928047
netID: mvina2, mnguy37

Description: The functionality of this code is that my button when pressed it going to change the state of my partener led once its pressed and vice verse. While using the LCD screen to debug.

Assumptions: An assumption We made is that once ground got connected to both arduinos, it would create a complete circuit

References:
• https://www.arduino.cc/reference/en/libraries/liquidcrystal/
• https://www.arduino.cc/reference/en/language/functions/commun
ication/serial/
• https://www.arduino.cc/reference/en/language/functions/commun
ication/serial/available/
• https://www.arduino.cc/reference/en/language/functions/commun
ication/serial/read/
- https://robotic-controls.com/learn/arduino/arduino-arduino-serial-
communication
- https://www.instructables.com/Arduino-Serial-Communication/
- https://docs.arduino.cc/learn/built-in-libraries/software-serial/
*/

#include <LiquidCrystal.h>

// ----- LCD and I/O pins -----
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int LED_PIN    = 10;   // external LED
const int BUTTON_PIN = 8;    // button to GND (INPUT_PULLUP)
const int BUZZER_PIN = 7;    // buzzer pin

// ----- Use same D0/D1 pins on both boards -----
#if defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_UNOR4_MINIMA)
  // UNO R4 WiFi / Minima have Serial1 on D0/D1
  #define LINK_SERIAL Serial1
#else
  // UNO R3 uses its only hardware Serial on D0/D1
  #define LINK_SERIAL Serial
#endif

// ----- Timing -----
unsigned long previousMillis = 0;
const unsigned long interval = 300;

// ----- Button / LED / buzzer state -----
bool lastBtn = HIGH;                // INPUT_PULLUP logic
unsigned long lastBounceMs = 0;
const unsigned long debounceMs = 25;

bool ledState = LOW;
unsigned long sentCount = 0;
unsigned long recvCount = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);   // buzzer off initially

  // Start serial link on pins 0 (RX) and 1 (TX)
  LINK_SERIAL.begin(9600);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Lab7 Link 9600");
  lcd.setCursor(0, 1); lcd.print("LED:OFF S:0 R:0");
}

void loop() {
  // --- Send one 'T' on button press (edge) ---
  bool now = digitalRead(BUTTON_PIN);
  if (now != lastBtn && (millis() - lastBounceMs) > debounceMs) {
    lastBounceMs = millis();
    if (lastBtn == HIGH && now == LOW) {     // pressed
      LINK_SERIAL.write('T'); //Sends from my Arduinos TX to partners RX.
      sentCount++;
    }
    lastBtn = now;
  }

  // --- Receive 'T' -> toggle LED (and buzzer) ---
  while (LINK_SERIAL.available() > 0) {
    if (LINK_SERIAL.read() == 'T') {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      recvCount++;

      // When LED turns ON -> start buzzing
      // When LED turns OFF -> stop buzzing
      if (ledState) {
        digitalWrite(BUZZER_PIN, HIGH);
      } else {
        digitalWrite(BUZZER_PIN, LOW);
      }
    }
  }

  // --- LCD update every few ms ---
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LED:");
    lcd.print(ledState ? "ON " : "OFF");
    lcd.print(" S:");
    lcd.print(sentCount);

    lcd.setCursor(0, 1);
    lcd.print("R:");
    lcd.print(recvCount);
    lcd.print(" 9600");
  }
}
