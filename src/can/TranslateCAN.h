/*
* IMPORTANT:
* 
* List of all CAN IDs the dashboard uses to filter, translate, and display CAN bus data.
* This file MUST BE EDITED to correspond to your vehicle's CAN bus IDs otherwise 
* it may not be reading your vehicle properly.
* 
* Additionally, the functions used to translate values from the CAN byte arrays
* MUST BE EDITED otherwise it won't properly grab meaningful data.
* (One way of doing it fast could be bit masking & bit shifting)
*/


#ifndef TRANSLATE_CAN_H 
#define TRANSLATE_CAN_H

#include <Arduino.h>

//----- Defines ---------------------------------------------------------------

//FIXME define real IDs

#define CAN_RPM           0x1DC 
#define CAN_GEAR          0x1DC
#define CAN_SPEED         0x158 
#define CAN_OILTEMP       0x096
#define CAN_OILPRESSURE   0x039
#define CAN_COOLANTTEMP   0x1DC
#define CAN_FUELPSI       0x158
#define CAN_FUELPERCENT   0x164
#define CAN_BATTERYVOLT   0x18E
#define CAN_AFR           0x136


//----- Translator Class ------------------------------------------------------

class TranslateCAN {
private:
	/*none*/
public:

  //FIXME define real parsers for vehicle

	static uint16_t rpm          (uint8_t* bytes) { return ((uint16_t)bytes[1] << 8) | bytes[2]; }  
	static char*    gear         (uint8_t* bytes) { return "-"; } 
	static uint16_t speed        (uint8_t* bytes) { return (((uint16_t)bytes[0] << 8) | bytes[1])/160; }  
	static uint16_t oilTemp      (uint8_t* bytes) { return 0; }   
	static uint16_t oilPressure  (uint8_t* bytes) { return 0; }   
	static uint16_t coolantTemp  (uint8_t* bytes) { return 0; }   
	static uint16_t fuelPSI      (uint8_t* bytes) { return 0; }   
	static uint16_t fuelPercent  (uint8_t* bytes) { return 0; }   
	static float    batteryVolt  (uint8_t* bytes) { return 0.0; } 
	static float    afr          (uint8_t* bytes) { return 0.0; } 
	
};


#endif // TRANSLATE_CAN_H