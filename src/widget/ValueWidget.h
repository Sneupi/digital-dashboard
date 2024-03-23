#ifndef VALUEWIDGET_H
#define VALUEWIDGET_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "widget/widget.h"

class ValueWidget : public Widget {
public:
    ValueWidget(TFT_eSPI& tft, const WidgetPlacement& p, const char* label)
        : Widget(tft, p), value(DEFAULT_VALUE), label(label) {}
    ValueWidget(TFT_eSPI& tft, int x, int y, int w, int h, const char* label)
        : Widget(tft, x, y, w, h), value(DEFAULT_VALUE), label(label) {}

    void init() override {
        tft.fillRect(x, y, w, h, TFT_BLACK);
        drawLabel();
        clear();
    }

    void clear() override {
        snprintf(value, sizeof(value), "%s", DEFAULT_VALUE);
        updateText();
    }

    void update(char* s) override {
        snprintf(value, sizeof(value), "%s", s);
        updateText();
    }

    void update(uint16_t i) override {
        snprintf(value, sizeof(value), "%u", i);
        updateText();
    }

    void update(float f) override {
        snprintf(value, sizeof(value), "%.2f", f);
        updateText();
    }

private:
    char value[10];
    const char* label;

    void updateText() {
        tft.setFreeFont(WIDGET_FONT);
        tft.setTextSize(WIDGET_FONT_SIZE);
        tft.setTextDatum(MC_DATUM);
        tft.setTextColor(isErrorState ? TFT_RED : TFT_WHITE, TFT_BLACK);
        tft.drawString(value, x + w / 2, y + h / 2);
    }

    void drawLabel() {
        tft.setFreeFont(WIDGET_FONT);
        tft.setTextSize(WIDGET_FONT_SIZE - 1);
        tft.setTextDatum(BC_DATUM);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString(label, x + w / 2, y + h);
    }
};

#endif // VALUEWIDGET_H