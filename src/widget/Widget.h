#ifndef WIDGET_H
#define WIDGET_H

#include <TFT_eSPI.h>
#include "../screen_settings.h"

#define DEFAULT_VALUE "      "

struct WidgetPlacement {
    int x;
    int y;
    int w;
    int h;
};

class Widget {
public:
    Widget(TFT_eSPI& tft, const WidgetPlacement& p)
        : tft(tft), x(p.x), y(p.y), w(p.w), h(p.h), isErrorState(false) {}
    Widget(TFT_eSPI& tft, int x, int y, int w, int h)
        : tft(tft), x(x), y(y), w(w), h(h), isErrorState(false) {}

    virtual void init() = 0;
    virtual void clear() = 0;

    virtual void update(char* s) = 0;
    virtual void update(uint16_t i) = 0;
    virtual void update(float f) = 0;

    void setErrorState(bool error) {
        isErrorState = error;
    }

protected:
    TFT_eSPI& tft;
    int x;
    int y;
    int w;
    int h;
    bool isErrorState;
};

#endif // WIDGET_H