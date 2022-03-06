#include <Wire.h>

#define BUTTON_UP 5
#define BUTTON_RIGHT 2
#define BUTTON_DOWN 3
#define BUTTON_LEFT 4//up: 5, down: 3, right:2, left, 4
#define BUTTON_E 6
#define BUTTON_F 7
#define BUTTON_K 8
#define PIN_ANALOG_X 0
#define PIN_ANALOG_Y 1

#define MOTOR_9 9
#define MOTOR_10 10
#define LINOUT11 11
#define LINOUT12 12

#define DELAY 100
const uint8_t   OFF     = HIGH;
const uint8_t   ON      = LOW;

void setup() {

 Serial.begin(9600);
 // to enable pull up resistors first write pin mode
 // and then make that pin HIGH
 pinMode(BUTTON_UP, INPUT);
 digitalWrite(BUTTON_UP, HIGH);
 
 pinMode(BUTTON_RIGHT, INPUT);
 digitalWrite(BUTTON_RIGHT, HIGH);

 pinMode(BUTTON_DOWN, INPUT);
 digitalWrite(BUTTON_DOWN, HIGH);

 pinMode(BUTTON_LEFT, INPUT);
 digitalWrite(BUTTON_LEFT, HIGH);

 pinMode(BUTTON_E, INPUT);
 digitalWrite(BUTTON_E, HIGH);

 pinMode(BUTTON_F, INPUT);
 digitalWrite(BUTTON_F, HIGH);

  pinMode(BUTTON_K, INPUT);
 digitalWrite(BUTTON_K, HIGH);


pinMode(MOTOR_9, OUTPUT);
pinMode(MOTOR_10, OUTPUT);

 pinMode(LINOUT11, OUTPUT);
 pinMode(LINOUT12, OUTPUT);
 

}
//Reverses a buttons reading, to make it more readable
int rBtn(int btn){
return (btn==0)?1:0;
}

int motorControlX(int val){
  if(val>=506) return 0;//only move when moving joystick in negative direction
  val = val-505;//505 to 0 AND to 0-505
  val = abs(val);
  //map 0 - 506 to 0-255
  return map(val, 0, 505,0,190);  //0-255 total

}

void loop() {
  int btnLinActUp = digitalRead(BUTTON_UP);
  int btnRight = digitalRead(BUTTON_RIGHT);
  int btnLinActDown = digitalRead(BUTTON_DOWN);
  int btnStopLin = digitalRead(BUTTON_LEFT);
  int btnEVal = digitalRead(BUTTON_E);
  int btnFVal = digitalRead(BUTTON_F);
  int btnKVal = digitalRead(BUTTON_K);
  int joyXVal = analogRead(PIN_ANALOG_X);
  int joyXVal2 = map(joyXVal,0, 1023, -100, 100);
  int joyYVal = analogRead(PIN_ANALOG_Y);
  int joyYVal2 = map(joyYVal,0, 1023, -100, 100);
  
  Serial.print("LinActUp = "), Serial.print(rBtn(btnLinActUp)),Serial.print("\t");
  Serial.print("btnRight = "), Serial.print(btnRight),Serial.print("\t");
  Serial.print("btnStopLin = "), Serial.print(rBtn(btnStopLin)),Serial.print("\t");
  Serial.print("LinActDown = "), Serial.print(btnLinActDown),Serial.print("\t");
  Serial.print("E = "), Serial.print(rBtn(btnEVal)),Serial.print("\t");
  Serial.print("F = "), Serial.print(rBtn(btnFVal)),Serial.print("\t");
  Serial.print("K = "), Serial.print(rBtn(btnKVal)),Serial.print("\t");
  Serial.print("X = "), Serial.print(joyXVal),Serial.print("\t");
  Serial.print("Y = "), Serial.print(joyYVal),Serial.print("\t");
  //dac ranges from 0 to 4095
  //x axis for right motor
  //Read joystick value y axis for left motor

  int motorValX = motorControlX(joyXVal);
  analogWrite(MOTOR_9,motorValX);
  analogWrite(MOTOR_10,motorValX);
  Serial.print("motor = "), Serial.println(motorValX);
  //send speed control analog signal to motor controller


  
  //Extend linear actuator
  if(btnLinActUp==0){
   digitalWrite(LINOUT11, HIGH);
    digitalWrite(LINOUT12, LOW);
      Serial.println("linact up");
  }
  //Retract linear actuator
  if(btnLinActDown==0){
   digitalWrite(LINOUT11, LOW);
    digitalWrite(LINOUT12, HIGH);
    Serial.println("linact down");
  }
  //stop linear actuator
  if(btnStopLin==0){
   digitalWrite(LINOUT11, LOW);
    digitalWrite(LINOUT12, LOW);
    Serial.println("linact stop");
  }

//btn right, execute sequence of actions
if(btnRight==0){
  //extend linear actuator
  digitalWrite(LINOUT11, HIGH);
    digitalWrite(LINOUT12, LOW);
      Serial.println("linact up 10s");
      delay(10000);
  //Forward for 6 seconds
   analogWrite(MOTOR_9,190);
  analogWrite(MOTOR_10,190);
  Serial.println("forward 6s");
  delay(6000);
  //Retract linear actuator
     digitalWrite(LINOUT11, LOW);
    digitalWrite(LINOUT12, HIGH);
    Serial.println("linact down 10s");
    delay(10000);
}
  
  delay(DELAY);
}
