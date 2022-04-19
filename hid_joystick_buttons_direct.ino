// // create a 16 button "joystick" with no other controls
//
// reads the buttons direct from digital inputs
//
// derived from an example by Matthew Heironimus from his Joystick library


#include <Joystick.h>

#define STATUS_LED_PIN  13


typedef struct {
  int   pin;
  int   button;
  int   lastState;
} BUTTONS;

BUTTONS Buttons[] = { { 2, 0, 0 },
                      { 3, 1, 0 },
                      { 4, 2, 0 },
                      { 5, 3, 0 },
                      { 6, 4, 0 },
                      { 7, 5, 0 },
                      { 8, 6, 0 },
                      { 9, 7, 0 },
                      { 10, 8, 0 },
                      { 11, 9, 0 },
                      { 12, 10, 0 },
                      { A0, 11, 0 },
                      { A1, 12, 0 },
                      { A2, 13, 0 },
                      { A3, 14, 0 },
                      { A4, 15, 0 } };

int NumOfButtons = (sizeof (Buttons) / sizeof(Buttons[0]));


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   NumOfButtons,          // number of buttons
                   0,                     // hat switch count
                   false, false, false,   // no x, y, or z axis
                   false, false,          // no rudder or throttle
                   false, false, false);  // no accel, brake, or steering


void setup() {

  // Initialize Button Pins
  for (int i = 0 ; i < NumOfButtons ; i++) {
    pinMode(Buttons[i].pin, INPUT_PULLUP);
  }

  pinMode(STATUS_LED_PIN, OUTPUT);

  // Initialize Joystick Library
  Joystick.begin();

  Serial.begin(9600);
}




void loop() {

  for (int i = 0; i < NumOfButtons; i++) {

    Serial.print(i);
    Serial.print(": Pin ");
    Serial.print(Buttons[i].pin);
    Serial.print(" ");

    int currentButtonState = ! digitalRead(Buttons[i].pin);

    Serial.println(currentButtonState);

    if (currentButtonState != Buttons[i].lastState) {
      Joystick.setButton(Buttons[i].button, currentButtonState);
      Buttons[i].lastState = currentButtonState;
    }
  }

  Serial.println("");

  digitalWrite(STATUS_LED_PIN, HIGH);

  delay(50);

  digitalWrite(STATUS_LED_PIN, LOW);
}
