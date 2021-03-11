#include <Keypad.h>
#include <Mouse.h>
#include <Keyboard.h>
// #include "HID-Project.h"

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = { 
  {'1', '2', '3', '4'}, 
  {'5', '6', '7', '8'}, 
  {'9', '0', 'a', 'b'}, 
  {'c', 'd', 'e', 'f'}
}; 


#define COL_0_PIN 5 
#define COL_1_PIN 6
#define COL_2_PIN 7 
#define COL_3_PIN 8 

#define ROW_0_PIN 9
#define ROW_1_PIN 10
#define ROW_2_PIN 11
#define ROW_3_PIN 12

#define TOGGLE_PIN_1 2
#define TOGGLE_PIN_2 3


byte rowPins[ROWS] = {ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN}; 
byte colPins[COLS] = {COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN}; 

Keypad customKeypad = Keypad (makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
const long debounceInterval = 100;

unsigned long lastDebounceTimeT1 = 0;
unsigned long lastDebounceTimeT2 = 0;

int lastT1State = HIGH;
int lastT2State = HIGH;

int buttonT1State = 1;
int buttonT2State = 1;


int leftClickMode = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TOGGLE_PIN_1, INPUT_PULLUP);
  pinMode(TOGGLE_PIN_2, INPUT_PULLUP);

  digitalWrite(LED_BUILTIN, LOW);
  customKeypad.setDebounceTime(debounceInterval);
  Keyboard.begin();
  Mouse.begin();

  
}

void loop() {
  char customKey = customKeypad.getKey(); 
  if (customKey) { 
    switch(customKey) { 
      case '1':
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.write(KEY_F13);
        Keyboard.releaseAll();
        break; 
      case '2': 
        Keyboard.press(KEY_LEFT_ALT); 
        Keyboard.write(KEY_F14); 
        Keyboard.releaseAll();
        break; 
      case '3':
        Keyboard.press(KEY_LEFT_ALT); 
        Keyboard.write(KEY_F15);
        Keyboard.releaseAll();
        break; 
      case '4':
        Keyboard.press(KEY_LEFT_ALT); 
        Keyboard.write(KEY_F16);
        Keyboard.releaseAll();
        break; 
      case '5': 
        Keyboard.press(KEY_LEFT_ALT); 
        Keyboard.write(KEY_F17);
        Keyboard.releaseAll();
        break; 
      case '6': 
        Keyboard.write(KEY_F13);
        break; 
      case '7': 
        Keyboard.write(KEY_F14);
        break; 
      case '8': 
        Keyboard.write(KEY_F15);
        break; 
      case '9': 
        Keyboard.write(KEY_F16);
        break; 
      case '0': 
        Keyboard.write(KEY_F17);
        break; 
      case 'a': 
        Keyboard.write(KEY_F18);
        break; 
      case 'b': 
        Keyboard.write(KEY_F19);
        break;
      case 'c':
        if (leftClickMode == 0) {
          leftClickMode = 1;
          digitalWrite(LED_BUILTIN, HIGH);
          Mouse.press(); 
        }  else {
          leftClickMode = 0;
          digitalWrite(LED_BUILTIN, LOW);
          Mouse.release(); 
        } 
        // Keyboard.write(KEY_F20);
        break;
      case 'd': 
        Keyboard.write(KEY_F21);
        break;
      case 'e': 
        Keyboard.write(KEY_F22);
        break;
      case 'f': 
        Keyboard.write(KEY_F23);
        break;                 
      default:
        break;
    }
  }

  // First Toggle Button 
  int reading = digitalRead(TOGGLE_PIN_1);

  if (reading != lastT1State) {
    lastDebounceTimeT1 = millis(); 
  }

  if ((millis() - lastDebounceTimeT1) > debounceInterval) {

    if (reading != buttonT1State) {
      buttonT1State = reading;

      Serial.print("Toggle 1 : ");
      Serial.println(reading);

      if (reading == 0) {
        digitalWrite(LED_BUILTIN, HIGH);
        Mouse.press();
      } else {
        digitalWrite(LED_BUILTIN, LOW);
        Mouse.release(); 
      } 

    } 
  }

  lastT1State = reading;


  // Second Toggle Button 
  reading = digitalRead(TOGGLE_PIN_2);

  if (reading != lastT2State) {
    lastDebounceTimeT2 = millis(); 
  }

  if ((millis() - lastDebounceTimeT2) > debounceInterval) {

    if (reading != buttonT2State) {
      buttonT2State = reading;

      Serial.print("Toggle 2 : ");
      Serial.println(reading);

      if (reading == 1) {
        digitalWrite(LED_BUILTIN, HIGH);
        Keyboard.press(KEY_LEFT_ALT);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
        Keyboard.release(KEY_LEFT_ALT);
      } 
    } 
  }

  lastT2State = reading;
}

