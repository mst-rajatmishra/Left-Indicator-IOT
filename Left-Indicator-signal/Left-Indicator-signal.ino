#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// FOR Pin OF LED AND SWITCH
const int ledPin = NA;        
const int switchPin = NA;      
// display pin
#define TFT_CS     NA  //for chip select
#define TFT_RST    NA  // for Reset
#define TFT_DC     NA  //for Data Command

// TFT display(Adafruit_ILI9341 is easy to use interface to interact with it).
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Variables to manage the switch state
bool lastStateSwitch = LOW;   // using bool to make it use like true or false on or off and kept it low so we can know the Last state of switch it was pressed or no.
bool ledState = LOW;          // using it so we can know the update of the led light it is on or off on last stage and it should match with the switch state of the board.
unsigned long lastDebounceTime = 0;  // it is used to store positive number 32bits and debounce is used to count the time we press the button 
unsigned long debounceDelay = 50;    // delay part is used that it should take time to show the new signal if pressed time is in millisecond so it is 50 ms.

void setup() {
  // serial communication
  Serial.begin(9600); //  for debugging
  
  // input
  pinMode(switchPin, INPUT);  // Arduino will read the state of the switch it is pressed or not.
  
  //LED pin as output
  pinMode(ledPin, OUTPUT);   //The LED will be controlled by this pin. Arduino will send either ON or OFF to the pin based on the led State variable.
  
  // TFT display
  tft.begin();
  tft.setRotation(0);   // we have to Adjust rotation as needed 
  tft.fillScreen(ILI9341_BLACK); // black background
  tft.setTextColor(ILI9341_WHITE);  //  text color
  tft.setTextSize(2);    //  text size

  // Initial message on TFT
  tft.setCursor(10, 50);  //gui in screen place 
  tft.print("Left Indicator: OFF");  //starting showing its off
  
  // Start with the LED off
  digitalWrite(ledPin, LOW); // led to off at starting
}

void loop() {
  // Reading the current state of the switch
  int switchReading = digitalRead(switchPin);

  // Check if the switch state has changed state it updates the debounce timer 
  if (switchReading != lastSwitchState) {
    lastDebounceTime = millis();  // Reset debounce timer
  }

  
  if ((millis() - lastDebounceTime) > debounceDelay) {   // If enough time has Happend since the last change
    
    if (switchReading == LOW && lastSwitchState == HIGH) {     // If the switch is pressed (LOW means the button is pressed)
      
      ledState = !ledState;     // Toggle the LED state

      
      digitalWrite(ledPin, ledState);     // Sets the physical ledPin to either HIGH or LOW, based on the value of ledState.

    
      tft.fillScreen(ILI9341_BLACK);   // Clear screen
      tft.setCursor(10, 50);           // Set position for text
      if (ledState) {
        tft.print("Left Indicator: ON");
      } else {
        tft.print("Left Indicator: OFF");
      }
      
    
      Serial.println(ledState ? "Left Indicator ON" : "Left Indicator OFF");  // Debugging output via serial monitor
    }
  }

  lastSwitchState = switchReading;     // Save the current switch state for the next loop
}
