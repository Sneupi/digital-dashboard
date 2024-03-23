#include <Arduino.h>
#include <TFT_eSPI.h>
#include "pinout.h"
#include "pushbutton/Pushbutton.h"
#include "screen/Screen1.h"
#include "screen/Screen2.h"
#include "screen_settings.h"

TFT_eSPI tft = TFT_eSPI();
PushButton pb = PushButton(PB_PIN);
Screen1 screen1 = Screen1(tft, 0,0,SCREEN_WIDTH, (5 * SCREEN_HEIGHT) / 6);
Screen2 screen2 = Screen2(tft, 0,0,SCREEN_WIDTH, (5 * SCREEN_HEIGHT) / 6);

void toggleScreen() {
  static bool screen1Active = true;
  if (screen1Active) {
    screen1.init();
  } else {
    screen2.init();
  }
  screen1Active = !screen1Active;
}

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
    toggleScreen(); //FIXME: switch gui screen
  });

  // init screen
  screen2.init();

  // print successful init
  Serial.println("digital-dashboard INIT OK");
}

void loop() {
  pb.checkState();
}