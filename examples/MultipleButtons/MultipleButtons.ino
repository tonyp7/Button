#include <Button.h>

unsigned long milliseconds = 0UL;

Button* btn1;
Button* btn2;

void setup() {
  Serial.begin(9600);

  //create buttons on pin 12 and 11
  btn1 = new Button(12, INPUT_PULLUP, true);
  btn2 = new Button(11, INPUT_PULLUP, true);

}

void loop() {
  //When using multiple button, it's better to make a global call
  //to millis() and store the value. millis() is needed for the 
  //software debouncer.
  milliseconds = millis();

  btn1->poll(milliseconds);
  btn2->poll(milliseconds);

  if(btn1->getState() == HIGH){
    Serial.println("Button on pin 12 is ON!");
  }
  if(btn2->getState() == HIGH){
    Serial.println("Button on pin 11 is ON!");
  }

  delay(100);

}
