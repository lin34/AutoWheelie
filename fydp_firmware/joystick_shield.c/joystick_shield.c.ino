#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_E 6
#define BUTTON_F 7
#define BUTTON_K 8
#define PIN_ANALOG_X 0
#define PIN_ANALOG_Y 1

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

}
//Reverses a buttons reading, to make it more readable
int rBtn(int btn){
return (btn==0)?1:0;
}

void loop() {
  int btnUpVal = digitalRead(BUTTON_UP);
  int btnRightVal = digitalRead(BUTTON_RIGHT);
  int btnDownVal = digitalRead(BUTTON_DOWN);
  int btnLeftVal = digitalRead(BUTTON_LEFT);
  int btnEVal = digitalRead(BUTTON_E);
  int btnFVal = digitalRead(BUTTON_F);
  int btnKVal = digitalRead(BUTTON_K);
  int joyXVal = map(analogRead(PIN_ANALOG_X),0, 1000, -100, 100);
  int joyYVal = map(analogRead(PIN_ANALOG_Y),0, 1000, -100, 100);
  
  Serial.print("UP = "), Serial.print(rBtn(btnUpVal)),Serial.print("\t");
  Serial.print("RIGHT = "), Serial.print(rBtn(btnRightVal)),Serial.print("\t");
  Serial.print("DOWN = "), Serial.print(rBtn(btnDownVal)),Serial.print("\t");
  Serial.print("LEFT = "), Serial.print(rBtn(btnLeftVal)),Serial.print("\t");
  Serial.print("E = "), Serial.print(rBtn(btnEVal)),Serial.print("\t");
  Serial.print("F = "), Serial.print(rBtn(btnFVal)),Serial.print("\t");
  Serial.print("K = "), Serial.print(rBtn(btnKVal)),Serial.print("\t");
  Serial.print("X = "), Serial.print(joyXVal),Serial.print("\t");
  Serial.print("Y = "), Serial.println(joyYVal);
  
  delay(DELAY);
}
