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

#define UNKNOWN B10101010

class Button{
  private:
    uint8_t state;
    uint8_t pinNumber;
    uint8_t lastReadState;
    uint8_t edge;
    uint8_t invertMode;
    unsigned long lastDebounceTime;
    const static unsigned int DEBOUNCE_DELAY = 100;
	void (*functionRising)();
	void (*functionFalling)();
	void init();
  public: 
    void poll();
    void poll(const unsigned long milliseconds);
    uint8_t rising();
    uint8_t falling();
    Button(const uint8_t pin, const uint8_t invert);
	Button(const uint8_t pin, const uint8_t pinModeValue, const uint8_t invert);
	void attachFunction(void (*function)(), uint8_t edgeType);
	uint8_t getState();
};
