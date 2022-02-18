#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac1;
Adafruit_MCP4725 dac2;
#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_E 6
#define BUTTON_F 7
#define BUTTON_K 8
#define PIN_ANALOG_X 0
#define PIN_ANALOG_Y 1

#define LINOUT10 10
#define LINOUT11 11

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

 pinMode(LINOUT10, OUTPUT);


  pinMode(LINOUT11, OUTPUT);
 

   // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  bool found1 = dac1.begin(0x62);
  bool found2 = dac2.begin(0x63);
  if(found1){
    Serial.println("Found dac 1");
  }
  if(found2){
    Serial.println("Found dac 2");
  }

}
//Reverses a buttons reading, to make it more readable
int rBtn(int btn){
return (btn==0)?1:0;
}

//Maps the joystick reading to an analog out between 0 to 4095
//on the DAC X mid = 505 Y mid = 509
//the motor only goes from 1.2v to 4.2v, so the ranges should be restricted from 983 to 3439
int motorControlX(int val){
  if(val<506) return 0;//only move when moving joystick up
  val = val - 506;//1023 - 509 = 514
  //map 0 - 506
  return map(val, 0, 514,983,3439);  

}
int motorControlY(int val){
  if(val<509) return 0;//only move when moving joystick up
  val = val - 509;//1023 - 509 = 514
  //map 0 - 509 to 0 - 4095
  return map(val, 0, 514,983,3439);  

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
  Serial.print("Y = "), Serial.println(joyYVal);
  //dac ranges from 0 to 4095
  //x axis for right motor
  //Read joystick value y axis for left motor
  int motorValX = motorControlX(joyXVal);
  int motorValY = motorControlY(joyYVal);

  //send speed control analog signal to motor controller
  dac1.setVoltage(motorValX, false);
  dac2.setVoltage(motorValY, false);//vout connected to A0
  //Extend linear actuator
  if(btnLinActUp==0){
   digitalWrite(LINOUT10, HIGH);
    digitalWrite(LINOUT11, LOW);
  }
  //Retract linear actuator
  if(btnLinActDown==0){
   digitalWrite(LINOUT10, LOW);
    digitalWrite(LINOUT11, HIGH);
  }
  //stop linear actuator
  if(btnStopLin==0){
   digitalWrite(LINOUT10, LOW);
    digitalWrite(LINOUT11, LOW);
  }

  
  delay(DELAY);
}
