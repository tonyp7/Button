/*
  Button.cpp
  Class to handle a button on Arduino

  Copy Button.cpp and Button.h into your libraries Arduino folder.
  
  Please see https://idyl.io for complete tutorial on how this works.
  
  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 2nd February 2017
  by Tony Pottier
  
*/

#define UNKNOWN B10101010

class Button{
  private:
    int state;
    int pinNumber;
    int lastReadState;
    uint8_t edge;
    uint8_t invertMode;
    uint8_t lastDebounceTime;
    const static unsigned int DEBOUNCE_DELAY = 100;
	void (*functionRising)();
	void (*functionFalling)();
  public: 
    void init();
    void poll();
    void poll(unsigned long milliseconds);
    uint8_t rising();
    uint8_t falling();
    Button(const int pin, const uint8_t invert);
	void attachFunction(void (*function)(), uint8_t edgeType);
};
