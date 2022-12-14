/**********************************************************************
  Filename    : ButtonAndLed
  Description : Control led by button.
  Auther      : www.freenove.com
  Modification: 2020/07/11
**********************************************************************/
#define PIN_LED    23
#define PIN_LED2    22
#define PIN_LED3  21
#define PIN_LED4  14
#define PIN_LED5  12
#define PIN_LED6  32
#define PIN_LED7  33
#define PIN_LED8  25
#define PIN_LED9  26

int count = 0;

#define PIN_BUTTON 13
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin PIN_LED as an output.
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  pinMode(PIN_LED5, OUTPUT);
  pinMode(PIN_LED6, OUTPUT);
  pinMode(PIN_LED7, OUTPUT);
  pinMode(PIN_LED8, OUTPUT);
  pinMode(PIN_LED9, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    count++;
  }else{
    //digitalWrite(PIN_LED,LOW);
  }
  delay(250);

  if (count == 0){
    digitalWrite(PIN_LED,HIGH);
    //digitalWrite(PIN_LED2,HIGH);
    //digitalWrite(PIN_LED3,HIGH);
    //digitalWrite(PIN_LED4,HIGH);
    //digitalWrite(PIN_LED5,HIGH);
    //digitalWrite(PIN_LED6,HIGH);
    //digitalWrite(PIN_LED7,HIGH);
    //digitalWrite(PIN_LED8,HIGH);
    //digitalWrite(PIN_LED9,HIGH);
  }
  else if (count == 1){
    digitalWrite(PIN_LED2,HIGH);
  }
  else if (count == 2){
    digitalWrite(PIN_LED3,HIGH);
  }
  else if (count == 3){
    digitalWrite(PIN_LED4,HIGH);
  }
  else if (count == 4){
    digitalWrite(PIN_LED5,HIGH);
  }
  else if (count == 5){
    digitalWrite(PIN_LED6,HIGH);
  }
  else if (count == 6){
    digitalWrite(PIN_LED7,HIGH);
  }
  else if (count == 7){
    digitalWrite(PIN_LED8,HIGH);
  }
  else if (count == 8){
    digitalWrite(PIN_LED9,HIGH);
  }
}
