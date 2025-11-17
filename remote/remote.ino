#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Pin.hpp>

RF24 radio(7, 8); // CE, CSN
const uint64_t pipeOut = 0xE9E8F0F0E1LL;

struct Data_Package {
  int xAxis;
  int yAxis;
};

Data_Package data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipeOut);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  data.xAxis = analogRead(A0); // Horizontal (Left-Right)
  data.yAxis = analogRead(A1); // Vertical (Forward-Backward)

  radio.write(&data, sizeof(Data_Package));

  Serial.print("X: ");
  Serial.print(data.xAxis);
  Serial.print(" | Y: ");
  Serial.println(data.yAxis);

  delay(20); // smooth signal
}