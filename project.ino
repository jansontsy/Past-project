#include <SoftwareSerial.h>
#include <Servo.h>
using namespace std;

Servo lock_servo;

SoftwareSerial Bluetooth(11,12);
int message;
int power;

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  lock_servo.attach(13);
  power = 0;
}
void loop() {
  while (Bluetooth.available() > 0) {
    int c =  Bluetooth.read();
    message = c-48;
    Serial.println(message);
  if (message < 4 && message > 0) {
     power = message ;
    if (power == 3) {
      digitalWrite(8,LOW );
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
    }
    if (power == 2) {
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
    }
    if (power == 1) {
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
    }
  }
  if (message == 4) {
    lock_servo.write(180);
    delay (power*500);
    lock_servo.write(60);
    message = 0;
  }
  if (message > 4) {
    lock_servo.write(180);
    delay (power*500);
    lock_servo.write(60);
    delay (message*3600000);
  }
 }
}
///    if (message > 4) {
      
    
