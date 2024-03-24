/**
 * Overrange and underrange limits for CAN values
*/

#ifndef LIMITS_H
#define LIMITS_H

//FIXME define real limits for vehicle

#define CAN_RPM_UPPER_LIMIT           8500

#define CAN_OILTEMP_UPPER_LIMIT       150
#define CAN_OILTEMP_LOWER_LIMIT       -40

#define CAN_OILPRESSURE_UPPER_LIMIT   100
#define CAN_OILPRESSURE_LOWER_LIMIT   0

#define CAN_COOLANTTEMP_UPPER_LIMIT   120
#define CAN_COOLANTTEMP_LOWER_LIMIT   -40

#define CAN_FUELPRESSURE_UPPER_LIMIT  100
#define CAN_FUELPRESSURE_LOWER_LIMIT  0

#define CAN_FUELPERCENT_LOWER_LIMIT   15

#define CAN_BATTERYVOLT_UPPER_LIMIT   13.0
#define CAN_BATTERYVOLT_LOWER_LIMIT   11.1

#define CAN_AFR_UPPER_LIMIT           13.5
#define CAN_AFR_LOWER_LIMIT           12.2

#endif // LIMITS_H