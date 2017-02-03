#include <Button.h>


//each button needs to be declared
Button* simpleButton;

void setup() {

  Serial.begin(9600);
  
  //create a button on pin 12. We invert the logic (invert=true)
  //so that even we are in input pullup mode, a press to the button
  //will be detected as a "on" value and a rising edge.
  simpleButton = new Button(12, INPUT_PULLUP, true);

}

void loop() {

  //this update the status of the button and must be called at every loop
  simpleButton->poll();

  if(simpleButton->rising()){
    //detecting rising edge
    Serial.println("Button went from off to on!");
  }
  else if(simpleButton->falling()){
    //detecting falling edge
    Serial.println("Button went from on to off!");
  }

}
