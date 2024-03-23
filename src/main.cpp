#include <Arduino.h>
#include <TFT_eSPI.h>
#include "pinout.h"
#include "pushbutton/Pushbutton.h"

TFT_eSPI tft = TFT_eSPI();
PushButton pb = PushButton(PB_PIN);

void setup() {

  // init Serial
  Serial.begin(115200);
  while (!Serial) {};

  // init TFT display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLUE); //FIXME: TFT_BLACK

  // init pushbutton
  pb.registerFunction([]() {
    Serial.println("Pushbutto1234n pressed"); //FIXME: switch gui screen
  });

  // print successful init
  Serial.println("digital-dashboard INIT OK");
}

void loop() {
  pb.checkState();
}