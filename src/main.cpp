#include <Arduino.h>
#include <TFT_eSPI.h>
#include "pinout.h"
#include "pushbutton/Pushbutton.h"
#include "gui/GUI.h"
#include "can/CAN.h"

#define REFRESH_INTERVAL 3000 //ms for force clear

CAN can = CAN();
TFT_eSPI tft = TFT_eSPI();
PushButton pb = PushButton(PB_PIN);
GUI gui = GUI(&tft);

twai_message_t can_frame;
bool flagDisconnect = false;
unsigned long last_forceclear = 0;

void setup() {

  // init Serial
  Serial.begin(115200);
  while (!Serial) {};

  // init TFT display
  tft.init();

  //init CAN
  can.init(18, 19, 500); //FIXME pinout

  // init pushbutton
  pb.registerFunction([]() {
    gui.nextScreen();
  });

  // init screen
  gui.init(0);

  // print successful init
  Serial.println("digital-dashboard INIT OK");
}


void EVENT_HEARTBEAT() {
  
  bool conn = can.isConnected();

  // If disconnected, but event never did, do event once.
  if (!flagDisconnect && !conn) {
    flagDisconnect = true;
    gui.setDC(true);
  }
  // If became connected reset flag, reset display
  else if (flagDisconnect && conn) {
    flagDisconnect = false;
    gui.setDC(false);
  }

}


void EVENT_CEL() {
  //FIXME add implementation for CEL. potentially as interrupt pin from external checker
}

void EVENT_FORCE_CLEAR() {

  if (millis() - last_forceclear >= REFRESH_INTERVAL) {
    gui.clear();
    last_forceclear = millis();
  }
}

void loop() {

  // Check pushbutton
  // if pressed, change screen
  pb.checkState();

  // Check CAN
  if (can.avaliable() && can.get(&can_frame)) {
    gui.update(can_frame);
  }

  //Check connnection
  EVENT_HEARTBEAT();

  //Check CEL
  EVENT_CEL();

  //Force clear readouts
  EVENT_FORCE_CLEAR();

}