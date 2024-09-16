#include <Arduino.h>
#include <NewPing.h>
#include <Ultrasonic.h>

// put function declarations here:
int PIRpin = D2; // PIR Digital input pin
int LDRDigi = D6; // LDR Digital input pin
int LDRAnalog = A0; // LDR Analog input pin
int BUZZpin = D3; // Buzzer Digital output pin
const float gama = 0.7; // LDR gamma value
const float rl10 = 50; // LDR Resistance when lux value is 10
#define MAX_DISTANCE 200
int trig = D4;
int echo = D5;
Ultrasonic ultrasonic(trig, echo);
int sonarcm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Serial initialization
  pinMode(LDRDigi, INPUT); // Declare LDRDigi as input
  pinMode(LDRAnalog, INPUT); // Declare LDRAnalog as input
  pinMode(BUZZpin, OUTPUT); // Declare BUZZpin as output


}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000); // 1000 ms delay before each sensor read

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

  if (LDRdigital == 1 && pirState == HIGH)
  {
    digitalWrite(BUZZpin, LOW);
    Serial.println("Buzz");
  }
  else {
    digitalWrite(BUZZpin, HIGH);
  }
  
  int sonarcm = ultrasonic.read();
  Serial.print(sonarcm);
  Serial.println(" cm");

  


  
}


