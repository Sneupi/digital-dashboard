
#ifndef SCREEN1_H
#define SCREEN1_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Screen.h"
#include "../widget/ValueWidget.h"

/**
 * First screen of the dashboard.
*/

// TODO: add tachometer bar widget

class Screen1 : public Screen {
public:
    Screen1(TFT_eSPI& tft, const ScreenPlacement& p)
        : Screen(tft, p) { 
            createWidgets(); 
        }
    Screen1(TFT_eSPI& tft, int x, int y, int w, int h)
        : Screen(tft, x, y, w, h) {
            createWidgets();
        }

    void init() override {

        tft.fillRect(x, y, w, h, TFT_BLACK);

        // Initialize widgets
        fuelPercent->init();
        gear->init();
        coolantTemp->init();
        speed->init();
    }

    int update(WidgetID id, uint16_t i) override {
        // Check which widget to update based on id
        if (id == WidgetID::GEAR) {
            gear->update(i);
            return 1;
        }
        else if (id == WidgetID::SPEED) {
            speed->update(i);
            return 1;
        }
        else if (id == WidgetID::FUELPERCENT) {
            fuelPercent->update(i);
            return 1;
        }
        else if (id == WidgetID::COOLANTTEMP) {
            coolantTemp->update(i);
            return 1;
        }
        
        return 0;
    }

    int update(WidgetID id, float f) override {
        // Check which widget to update based on id
        if (id == WidgetID::GEAR) {
            gear->update(f);
            return 1;
        }
        else if (id == WidgetID::SPEED) {
            speed->update(f);
            return 1;
        }
        else if (id == WidgetID::FUELPERCENT) {
            fuelPercent->update(f);
            return 1;
        }
        else if (id == WidgetID::COOLANTTEMP) {
            coolantTemp->update(f);
            return 1;
        }
        
        return 0;
    }

    int update(WidgetID id, char* s) override {
        // Check which widget to update based on id
        if (id == WidgetID::GEAR) {
            gear->update(s);
            return 1;
        }
        else if (id == WidgetID::SPEED) {
            speed->update(s);
            return 1;
        }
        else if (id == WidgetID::FUELPERCENT) {
            fuelPercent->update(s);
            return 1;
        }
        else if (id == WidgetID::COOLANTTEMP) {
            coolantTemp->update(s);
            return 1;
        }
        
        return 0;
    }

    void clear() override {
        fuelPercent->clear();
        gear->clear();
        coolantTemp->clear();
        speed->clear();
    }

private:
    ValueWidget* fuelPercent;
    ValueWidget* gear;
    ValueWidget* coolantTemp;
    ValueWidget* speed;

    void createWidgets() {
        
        // Calculate widget dimensions
        int widgetHeight = h / 3;
        int widgetWidth = w / 3;

        WidgetPlacement fuelPercentPlacement = { x + ((0 * w) / 3), (y + ((1 * h) / 3)), widgetWidth, widgetHeight };
        WidgetPlacement gearPlacement        = { x + ((1 * w) / 3), (y + ((1 * h) / 3)), widgetWidth, widgetHeight };
        WidgetPlacement coolantTempPlacement = { x + ((2 * w) / 3), (y + ((1 * h) / 3)), widgetWidth, widgetHeight };
        WidgetPlacement speedPlacement       = { x + ((1 * w) / 3), (y + ((2 * h) / 3)), widgetWidth, widgetHeight };

        fuelPercent = new ValueWidget(tft, fuelPercentPlacement, "Fuel %");
        gear = new ValueWidget(tft, gearPlacement, "Gear");
        coolantTemp = new ValueWidget(tft, coolantTempPlacement, "Coolant Temp");
        speed = new ValueWidget(tft, speedPlacement, "Speed");
    }
};

#endif // SCREEN1_H