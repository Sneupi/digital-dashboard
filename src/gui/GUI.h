// GUI.h

/*
* Dashboard GUI
*/

#ifndef GUI_H 
#define GUI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../screen_settings.h"
#include "../screen/Screen1.h"
#include "../screen/Screen2.h"
#include "../screen/WidgetID.h"

#define SCREEN_COUNT 2

class GUI {
private:

    // TFT reference
    TFT_eSPI* tft;

    int curr_screen = 0;

    bool CEL = false;
    bool DC = false;
	
    Screen* screen[SCREEN_COUNT] = {
        new Screen1(*tft, 0, 0, SCREEN_WIDTH, (5 * SCREEN_HEIGHT) / 6),
        new Screen2(*tft, 0, 0, SCREEN_WIDTH, (5 * SCREEN_HEIGHT) / 6)
    };

	
public:

    GUI(TFT_eSPI* _tft) : tft(_tft) {}
	
    void nextScreen() {
	  
        // cycle screen
        curr_screen++;
        if (curr_screen >= SCREEN_COUNT) curr_screen = 0;
        // init next
        screen[curr_screen]->init();
        
    }

    void setCEL(bool state) {
        CEL = state;
        tft->setFreeFont(WIDGET_FONT);
        tft->setTextSize(WIDGET_FONT_SIZE);
        tft->setTextDatum(BL_DATUM);
        tft->setTextColor(CEL ? TFT_ORANGE : TFT_BLACK, TFT_BLACK);
        tft->drawString("Check Engine", 0, SCREEN_HEIGHT);
    }
    void setDC(bool state) {
        DC = state;
        tft->setFreeFont(WIDGET_FONT);
        tft->setTextSize(WIDGET_FONT_SIZE);
        tft->setTextDatum(BR_DATUM);
        tft->setTextColor(DC ? TFT_RED : TFT_BLACK, TFT_BLACK);
        tft->drawString("Disconnected", SCREEN_WIDTH, SCREEN_HEIGHT);
    }
  
  
    void clear() {
        screen[curr_screen]->clear();
    }
  
  
    int init(int s) {
        

        if (s >= 0 && s < SCREEN_COUNT) {
            tft->setRotation(1);
            tft->fillScreen(TFT_BLACK);

            setCEL(CEL);
            setDC(DC);

            curr_screen = s;
            screen[s]->init();
            return 0;
        }
        else {
            return -1;
        }

    }
  
    
    void update(WidgetID id, uint16_t i) {
        screen[curr_screen]->update(id, i);
    }

    void update(WidgetID id, float f) {
        screen[curr_screen]->update(id, f);
    }

    void update(WidgetID id, char* s) {
        screen[curr_screen]->update(id, s);
    }

};


#endif // GUI_H