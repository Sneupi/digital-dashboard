#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {

  // init Serial
  Serial.begin(115200);
  while (!Serial);

  // init TFT display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // print successful init
  Serial.println("digital-dashboard INIT OK");
}

void loop() {
  
}