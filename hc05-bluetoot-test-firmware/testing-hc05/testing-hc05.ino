// This program shown how to control arduino from PC Via Bluetooth
// Connect ...
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx
//Written By Mohannad Rawashdeh
//for http://www.genotronex.com/

// you will need arduino 1.0.1 or higher to run this sketch

//#include <SoftwareSerial.h>// import the serial library

//SoftwareSerial Genotronex(0, 1); // RX, TX
int ledpin = 13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin, OUTPUT);
}

void loop() {
//  Genotronex.println("Hey");
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    BluetoothData = Serial.read();
    if (BluetoothData == '1') { // if number 1 pressed ....
      digitalWrite(ledpin, 1);
      Serial.println("LED  On D13 ON ! ");
    }
    if (BluetoothData == '0') { // if number 0 pressed ....
      digitalWrite(ledpin, 0);
      Serial.println("LED  On D13 Off ! ");
    }
  }
}
