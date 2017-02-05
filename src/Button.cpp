/*
  Button.cpp
  Class to handle a button on Arduino

  Copy Button.cpp and Button.h into your libraries Arduino folder.
  
  Please see https://idyl.io for complete tutorial on how this works.
  
  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 5th February 2017
  by Tony Pottier
  
*/

#include <stdint.h>
#include <arduino.h>
#include "Button.h"


/// \param pin arduino pin number used for this input
/// \param invert allows to reverse input. Useful when using INPUT_PULLUP but you don't want to work with inverted logic.
Button::Button(const uint8_t pin, const uint8_t invert){
  this->pinNumber = pin;
  this->invertMode = invert;
  init();
}

Button::Button(const uint8_t pin, const uint8_t pinModeValue, const uint8_t invert){
	pinMode(pin, pinModeValue);
	this->pinNumber = pin;
	this->invertMode = invert;
	init();
}


/// Initialize the button, this should be called in the "setup" Arduino function after defining the pin as INPUT or INPUT_PULLUP
void Button::init(){
  this->edge = UNKNOWN;
  this->lastDebounceTime = 0UL;
  this->state = this->invertMode?!digitalRead(this->pinNumber):digitalRead(this->pinNumber);
  this->lastReadState = this->state;
  functionRising = NULL;
  functionFalling = NULL;
}


void Button::attachFunction(void (*function)(), uint8_t edgeType){
  if(edgeType == RISING){
    this->functionRising = function;
  }
  else{
    this->functionFalling = function;
  }
}


void Button::poll(){
  this->poll(millis());
}

/// Read the input and debounce it. 
void Button::poll(const unsigned long milliseconds){
  
  // read the state of the switch into a local variable:
  // Pullup mode are active low so we negate the reading to make it active high
  int reading = this->invertMode ? !digitalRead(this->pinNumber):digitalRead(this->pinNumber);

  // If the switch changed, due to noise or pressing, reset debouncing timer
  if (reading != this->lastReadState) {
    this->lastDebounceTime = milliseconds;
  }

  //if timer exceeds last debounce time, we consider we have a valid
  //valud and therefore can update the state of the button
  //and write down the edge
  if (milliseconds - this->lastDebounceTime > DEBOUNCE_DELAY) {
    if (reading != this->state) {
      //button state has changed: update it
      this->state = reading;
      if(reading){
        if(functionRising){ functionRising();}
        else{this->edge = RISING;}
      }
      else{
        if(functionFalling){ functionFalling();}
        else{this->edge = FALLING;}
      }
    }
  }

  this->lastReadState = reading;  
}


/// Returns true if a rising edge is detected. Edge must be processed after a succesful call. calling this function reset the edge to unknown state.
uint8_t Button::rising(){
  if(edge == RISING){
    edge = UNKNOWN;
    return true;
  }
  return false;
}

/// Returns true if a falling edge is detected. Edge must be processed after a succesful call. calling this function reset the edge to unknown state.
uint8_t Button::falling(){
  if(edge == FALLING){
    edge = UNKNOWN;
    return true;
  }
  return false;
}

uint8_t Button::getState(){
	return this->state;
}
