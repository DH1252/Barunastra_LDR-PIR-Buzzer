#include <Arduino.h>

// put function declarations here:
int PIRpin = 4; // PIR Digital input pin
int LDRDigi = 16; // LDR Digital input pin
int LDRAnalog = 32; // LDR Analog input pin
int BUZZpin = 18; // Buzzer Digital output pin
const float gama = 0.7; // LDR gamma value
const float rl10 = 50; // LDR Resistance when lux value is 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Serial initialization
  pinMode(LDRDigi, INPUT); // Declare LDRDigi as input
  pinMode(LDRAnalog, INPUT); // Declare LDRAnalog as input
  pinMode(BUZZpin, OUTPUT); // Declare BUZZpin as output

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500); // 500 ms delay before each sensor read

  int LDRvalue = analogRead(LDRAnalog); // Read voltage values from LDRAnalog pin
  int pirState = digitalRead(PIRpin); // Read PIRpin state


  float LDRvolt = LDRvalue / 4095.0 * 5; // Use 5V as a reference

  

  float LDRResist = 2000 * LDRvolt / (1 - LDRvolt /5); // Divide by 2000 (Resistor Divider)

  float brightness = pow(rl10 * 1e3 * pow(10, gama) / LDRResist, (1 / gama));

  Serial.print("Brightness = ");
  Serial.println(brightness);

  int LDRdigital = digitalRead(LDRDigi);

  if (LDRdigital == 0)
  {
    Serial.println("Bright");
  }
  else 
  {
    Serial.println("Dark");
  }

  if (pirState == HIGH) {
    Serial.println("Motion Detected");
  }
  else {
    Serial.println("No Motion");
  }

  if (LDRdigital == 0 && pirState == HIGH)
  {
    digitalWrite(BUZZpin, HIGH);
    Serial.println("Buzz");
  }
  else {
    digitalWrite(BUZZpin, LOW);
  }
  
  
}


