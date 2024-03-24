
#ifndef SCREEN2_H
#define SCREEN2_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Screen.h"
#include "../widget/ValueWidget.h"
#include "driver/twai.h"

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

    int update(twai_message_t msg) override {
        uint32_t id = msg.identifier;
        if (id == CAN_OILTEMP)      { 
            oilTemp->setErrorState(EvaluateCAN::oilTemp(TranslateCAN::oilTemp(msg.data)));
            oilTemp->update(TranslateCAN::oilTemp(msg.data)); 
        }
        if (id == CAN_OILPRESSURE)  { 
            oilPressure->setErrorState(EvaluateCAN::oilPressure(TranslateCAN::oilPressure(msg.data)));
            oilPressure->update(TranslateCAN::oilPressure(msg.data)); 
        }
        if (id == CAN_FUELPSI) { 
            fuelPressure->setErrorState(EvaluateCAN::fuelPSI(TranslateCAN::fuelPSI(msg.data)));
            fuelPressure->update(TranslateCAN::fuelPSI(msg.data)); 
        }
        if (id == CAN_BATTERYVOLT)  { 
            batteryVolt->setErrorState(EvaluateCAN::batteryVolt(TranslateCAN::batteryVolt(msg.data)));
            batteryVolt->update(TranslateCAN::batteryVolt(msg.data)); 
        }
        if (id == CAN_AFR)          { 
            afr->setErrorState(EvaluateCAN::afr(TranslateCAN::afr(msg.data)));
            afr->update(TranslateCAN::afr(msg.data)); 
        }

        return (id == CAN_OILTEMP || id == CAN_OILPRESSURE || id == CAN_FUELPSI || id == CAN_BATTERYVOLT || id == CAN_AFR);
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