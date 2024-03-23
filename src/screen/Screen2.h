
#ifndef SCREEN2_H
#define SCREEN2_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Screen.h"
#include "../widget/ValueWidget.h"

/**
 * Second screen of the dashboard.
 */

class Screen2 : public Screen {
public:
    Screen2(TFT_eSPI& tft, const ScreenPlacement& p)
        : Screen(tft, p) { 
            createWidgets(); 
        }
    Screen2(TFT_eSPI& tft, int x, int y, int w, int h)
        : Screen(tft, x, y, w, h) {
            createWidgets();
        }

    void init() override {

        tft.fillRect(x, y, w, h, TFT_BLACK);

        // Initialize widgets
        oilTemp->init();
        oilPressure->init();
        fuelPressure->init();
        batteryVolt->init();
        afr->init();
    }

    int update(WidgetID id, uint16_t i) override {
        // Check which widget to update based on id
        if (id == WidgetID::OILTEMP) {
            oilTemp->update(i);
            return 1;
        }
        else if (id == WidgetID::OILPRESSURE) {
            oilPressure->update(i);
            return 1;
        }
        else if (id == WidgetID::FUELPRESSURE) {
            fuelPressure->update(i);
            return 1;
        }
        else if (id == WidgetID::BATTERYVOLT) {
            batteryVolt->update(i);
            return 1;
        }
        else if (id == WidgetID::AFR) {
            afr->update(i);
            return 1;
        }
        
        return 0;
    }

    int update(WidgetID id, float f) override {
        // Check which widget to update based on id
        if (id == WidgetID::OILTEMP) {
            oilTemp->update(f);
            return 1;
        }
        else if (id == WidgetID::OILPRESSURE) {
            oilPressure->update(f);
            return 1;
        }
        else if (id == WidgetID::FUELPRESSURE) {
            fuelPressure->update(f);
            return 1;
        }
        else if (id == WidgetID::BATTERYVOLT) {
            batteryVolt->update(f);
            return 1;
        }
        else if (id == WidgetID::AFR) {
            afr->update(f);
            return 1;
        }
        
        return 0;
    }

    int update(WidgetID id, char* s) override {
        // Check which widget to update based on id
        if (id == WidgetID::OILTEMP) {
            oilTemp->update(s);
            return 1;
        }
        else if (id == WidgetID::OILPRESSURE) {
            oilPressure->update(s);
            return 1;
        }
        else if (id == WidgetID::FUELPRESSURE) {
            fuelPressure->update(s);
            return 1;
        }
        else if (id == WidgetID::BATTERYVOLT) {
            batteryVolt->update(s);
            return 1;
        }
        else if (id == WidgetID::AFR) {
            afr->update(s);
            return 1;
        }
        
        return 0;
    }

    void clear() override {
        oilTemp->clear();
        oilPressure->clear();
        fuelPressure->clear();
        batteryVolt->clear();
        afr->clear();
    }

private:
    ValueWidget* oilTemp;
    ValueWidget* oilPressure;
    ValueWidget* fuelPressure;
    ValueWidget* batteryVolt;
    ValueWidget* afr;

    void createWidgets() {
        
        // Calculate widget dimensions
        int widgetHeight = h / 2;
        int widgetWidth = w / 3;

        WidgetPlacement oilTempPlacement      = { x + ((0 * w) / 3), (y + ((0 * h) / 2)), widgetWidth, widgetHeight };
        WidgetPlacement oilPressurePlacement  = { x + ((1 * w) / 3), (y + ((0 * h) / 2)), widgetWidth, widgetHeight };
        WidgetPlacement fuelPressurePlacement = { x + ((2 * w) / 3), (y + ((0 * h) / 2)), widgetWidth, widgetHeight };
        WidgetPlacement batteryVoltPlacement  = { x + ((0 * w) / 3), (y + ((1 * h) / 2)), widgetWidth, widgetHeight };
        WidgetPlacement afrPlacement          = { x + ((1 * w) / 3), (y + ((1 * h) / 2)), widgetWidth, widgetHeight };

        oilTemp = new ValueWidget(tft, oilTempPlacement, "Oil Temp");
        oilPressure = new ValueWidget(tft, oilPressurePlacement, "Oil Pressure");
        fuelPressure = new ValueWidget(tft, fuelPressurePlacement, "Fuel Pressure");
        batteryVolt = new ValueWidget(tft, batteryVoltPlacement, "Battery Volt");
        afr = new ValueWidget(tft, afrPlacement, "AFR");
    }
};


#endif // SCREEN2_H