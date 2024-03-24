
#ifndef SCREEN1_H
#define SCREEN1_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Screen.h"
#include "../widget/ValueWidget.h"
#include "driver/twai.h"
#include "../can/TranslateCAN.h"
#include "../can/EvaluateCAN.h"
#include "../widget/BarWidget.h"
#include "../can/limits.h"

/**
 * First screen of the dashboard.
*/

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
        tachometer->init();
        fuelPercent->init();
        gear->init();
        coolantTemp->init();
        speed->init();
    }

    int update(twai_message_t msg) override {
        uint32_t id = msg.identifier;
        if (id == CAN_RPM)         { 
            tachometer->setErrorState(EvaluateCAN::rpm(TranslateCAN::rpm(msg.data)));
            tachometer->update(TranslateCAN::rpm(msg.data));
        }
        if (id == CAN_GEAR)        { 
            gear->setErrorState(EvaluateCAN::gear(TranslateCAN::gear(msg.data)));
            gear->update(TranslateCAN::gear(msg.data)); 
        }
        if (id == CAN_SPEED)       { 
            speed->setErrorState(EvaluateCAN::speed(TranslateCAN::speed(msg.data)));
            speed->update(TranslateCAN::speed(msg.data)); 
        }
        if (id == CAN_COOLANTTEMP) { 
            coolantTemp->setErrorState(EvaluateCAN::coolantTemp(TranslateCAN::coolantTemp(msg.data)));
            coolantTemp->update(TranslateCAN::coolantTemp(msg.data)); 
        }
        if (id == CAN_FUELPERCENT) { 
            fuelPercent->setErrorState(EvaluateCAN::fuelPercent(TranslateCAN::fuelPercent(msg.data)));
            fuelPercent->update(TranslateCAN::fuelPercent(msg.data)); 
        }

        return (id == CAN_RPM || id == CAN_GEAR || id == CAN_SPEED || id == CAN_COOLANTTEMP || id == CAN_FUELPERCENT);
    }

    void clear() override {
        fuelPercent->clear();
        gear->clear();
        coolantTemp->clear();
        speed->clear();
    }

private:
    BarWidget*   tachometer;
    ValueWidget* fuelPercent;
    ValueWidget* gear;
    ValueWidget* coolantTemp;
    ValueWidget* speed;


    void createWidgets() {
        
        // Calculate widget dimensions
        int widgetHeight = h / 3;
        int widgetWidth = w / 3; 

        WidgetPlacement tachometerPlacement  = { x, y, w, h / 3 };
        WidgetPlacement fuelPercentPlacement = { x + ((0 * w) / 3), (y + ((1 * h) / 3)), widgetWidth, widgetHeight };
        WidgetPlacement gearPlacement        = { x + ((1 * w) / 3), (y + ((1 * h) / 3)), widgetWidth, widgetHeight };
        WidgetPlacement coolantTempPlacement = { x + ((2 * w) / 3), (y + ((1 * h) / 3)), widgetWidth, widgetHeight };
        WidgetPlacement speedPlacement       = { x + ((1 * w) / 3), (y + ((2 * h) / 3)), widgetWidth, widgetHeight };

        tachometer = new BarWidget(&tft, tachometerPlacement, 0, CAN_RPM_UPPER_LIMIT, CAN_RPM_UPPER_LIMIT);
        fuelPercent = new ValueWidget(tft, fuelPercentPlacement, "Fuel %");
        gear = new ValueWidget(tft, gearPlacement, "Gear");
        coolantTemp = new ValueWidget(tft, coolantTempPlacement, "Coolant Temp");
        speed = new ValueWidget(tft, speedPlacement, "Speed");
    }
};

#endif // SCREEN1_H