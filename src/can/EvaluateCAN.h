/*
* Evaluates the CAN data received from the vehicle and determines if the data is within the expected range.
* False corresponds to an error state, true corresponds to a normal state.
*/


#ifndef EVALUATE_CAN_H 
#define EVALUATE_CAN_H

#include <Arduino.h>
#include "limits.h"

//----- Evaluator Class ------------------------------------------------------

class EvaluateCAN {
private:
    /*none*/
public:

    static bool rpm        (uint16_t value) { return value >= CAN_RPM_UPPER_LIMIT; }  
    static bool gear       (char* value)    { return false; } // No limit defined for gear
    static bool speed      (uint16_t value) { return false; } // No limit defined for speed
    static bool oilTemp    (uint16_t value) { return value <= CAN_OILTEMP_LOWER_LIMIT || value >= CAN_OILTEMP_UPPER_LIMIT; }   
    static bool oilPressure(uint16_t value) { return value <= CAN_OILPRESSURE_LOWER_LIMIT || value >= CAN_OILPRESSURE_UPPER_LIMIT; }   
    static bool coolantTemp(uint16_t value) { return value <= CAN_COOLANTTEMP_LOWER_LIMIT || value >= CAN_COOLANTTEMP_UPPER_LIMIT; }   
    static bool fuelPSI    (uint16_t value) { return value <= CAN_FUELPRESSURE_LOWER_LIMIT || value >= CAN_FUELPRESSURE_UPPER_LIMIT; }   
    static bool fuelPercent(uint16_t value) { return value <= CAN_FUELPERCENT_LOWER_LIMIT; }   
    static bool batteryVolt(float value)    { return value <= CAN_BATTERYVOLT_LOWER_LIMIT || value >= CAN_BATTERYVOLT_UPPER_LIMIT; } 
    static bool afr        (float value)    { return value <= CAN_AFR_LOWER_LIMIT || value >= CAN_AFR_UPPER_LIMIT; } 
    
};


#endif // EVALUATE_CAN_H
