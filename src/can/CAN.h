#include "esp32-hal.h"
#include <stdint.h>
//CAN.h

/* ESP32 TWAI receive example (by Espressif) as a class

  Connect a CAN bus transceiver to the RX/TX pins.
  For example: SN65HVD230

  TWAI_MODE_NORMAL is used so that the TWAI controller will acknowledge bus messages.

  The API gives other possible speeds and alerts:
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/twai.html

  created 05-11-2022 by Stephan Martin (designer2k2)
*/

#ifndef CAN_CLASS_H 
#define CAN_CLASS_H

#include <Arduino.h>
#include "driver/twai.h"

#define DEFAULT_TIMEOUT 1000 //for watchdog

class CAN {
private:

  // watchdog timeout
  uint32_t watchdogTimeout; //ms

  // watchdog time of last message recv
  unsigned long rx_last;
  
  // if bus alive or not
  bool connected;

  // updates state of connected in realtime
  void refreshWatchdog(uint32_t rx_count) {
    if (rx_count > 0) {
      rx_last = millis();
      if (!connected) connected = true;
    }
    else {
      if (millis() - rx_last >= watchdogTimeout) {
        connected = false;
      }
    }
  }

public:

  //constructor
  CAN() : 
    rx_last(millis()),
    connected(false),
    watchdogTimeout(DEFAULT_TIMEOUT)
    {}

  bool init(int RX, int TX, uint32_t wdTimeout) {
    //
    watchdogTimeout = wdTimeout;

    int rc = 0;

    // Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX, (gpio_num_t)RX, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();  //Look in the api-reference for other speed sets.
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    
    uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA | TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_ERROR | TWAI_ALERT_RX_QUEUE_FULL;
    
    // Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
      rc = -1;
    }
    // Start TWAI driver
    else if (twai_start() != ESP_OK) {
      rc = -2;
    }
    // Reconfigure alerts to detect frame receive, Bus-Off error and RX queue full states
    else if (twai_reconfigure_alerts(alerts_to_enable, NULL) != ESP_OK) {
      rc = -3;
    }
    
    // TWAI driver is now successfully installed and started
    return (rc == 0);
  }

  // Returns # of rx messages waiting
  uint32_t avaliable() {
    // get statuses
    twai_status_info_t twaistatus;
    twai_get_status_info(&twaistatus); 

    // refresh watchdog
    refreshWatchdog(twaistatus.msgs_to_rx);

    // # rx messages waiting
    return twaistatus.msgs_to_rx; 
  }

  // Returns true if successful read
  bool get(twai_message_t* message) {
    return (twai_receive(message, 0) == ESP_OK);
  }

  // Returns false if watchdog timed out.
  // Refreshing of watchdog dependant/reliant 
  // on constant refresh of avaliable() method. //FIXME reliance on avaliable() to work
  bool isConnected() { return connected; }
	
};

#endif // CAN_CLASS_H