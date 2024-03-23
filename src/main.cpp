#include <Arduino.h>
#include <TFT_eSPI.h>
#include "pinout.h"
#include "pushbutton/Pushbutton.h"
#include "gui/GUI.h"

TFT_eSPI tft = TFT_eSPI();
PushButton pb = PushButton(PB_PIN);
GUI gui = GUI(&tft);

void setup() {

  // init Serial
  Serial.begin(115200);
  while (!Serial) {};

  // init TFT display
  tft.init();

  // init pushbutton
  pb.registerFunction([]() {
    gui.nextScreen();
  });

  // init screen
  gui.init(0);

  // print successful init
  Serial.println("digital-dashboard INIT OK");
}


void loop() {
  pb.checkState();

}