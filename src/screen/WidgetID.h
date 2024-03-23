#ifndef WIDGETID_H
#define WIDGETID_H

/**
 * WidgetID is an enum class that contains the IDs 
 * of the widgets used in the project
 * to identify which widget to update in each Screen class 
 * when feeding information to the update method.
*/

enum WidgetID {
    RPM,
    GEAR,
    SPEED,
    OILTEMP,
    OILPRESSURE,
    COOLANTTEMP,
    FUELPRESSURE,
    FUELPERCENT,
    BATTERYVOLT,
    AFR
};

#endif // WIDGETID_H