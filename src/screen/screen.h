
#ifndef SCREEN_H
#define SCREEN_H

#include <TFT_eSPI.h>
#include "WidgetID.h"

struct ScreenPlacement {
    int x;
    int y;
    int w;
    int h;
};

class Screen {
public:
    Screen(TFT_eSPI& tft, const ScreenPlacement& p)
        : tft(tft), x(p.x), y(p.y), w(p.w), h(p.h) {}
    Screen(TFT_eSPI& tft, int x, int y, int w, int h)
        : tft(tft), x(x), y(y), w(w), h(h) {}

    virtual void init() = 0; 

	virtual int update(WidgetID id, uint16_t i) = 0; 
    virtual int update(WidgetID id, float f) = 0;
    virtual int update(WidgetID id, char* s) = 0;
	
	virtual void clear() = 0; 

protected:

    /**
     * children classes should define their widgets themselves, 
     * as well as the IDs associated with each widget 
     * to be used in the update method
     */

    TFT_eSPI& tft;
    int x;
    int y;
    int w;
    int h;
};

#endif // SCREEN_H