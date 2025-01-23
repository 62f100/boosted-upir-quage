#include "can.h"
#include "driver/twai.h"
#include <Arduino.h> // Include for Serial
//#include <freertos/FreeRTOS.h> 
//#include <freertos/task.h> // Include for vTaskDelay

// Define CAN pins
#define CAN_TX_PIN GPIO_NUM_4
#define CAN_RX_PIN GPIO_NUM_5

// Define CAN constants
#define MSCAN_BASE 1520  // Base address for MS CAN
#define MSCAN_LEN  64
#define MS_BASE_ID 1520
#define MAP_GROUP 2
#define MAP_CAN_ID (MS_BASE_ID + MAP_GROUP)

extern float mapPressure; // Declare mapPressure as extern since it's defined in display.cpp

void setupTWAI() {
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_PIN, CAN_RX_PIN, TWAI_MODE_NORMAL);
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  g_config.rx_queue_len = 32;
  g_config.tx_queue_len = 32;
  g_config.alerts_enabled = TWAI_ALERT_RX_DATA | TWAI_ALERT_ERR_PASS;

  if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
    Serial.println("Failed to install TWAI driver");
    return;
  }

  if (twai_start() != ESP_OK) {
    Serial.println("Failed to start TWAI driver");
    return;
  }
}

void processCANMessage(twai_message_t *message) {
  if (message->identifier == MAP_CAN_ID) {
    uint16_t raw_map = (message->data[2] << 8) | message->data[3];
    mapPressure = raw_map / 10.0; 
  }
}

void canTaskFunction(void *parameter) {
  while(1) {
    twai_message_t message;
    esp_err_t result = twai_receive(&message, pdMS_TO_TICKS(0));
    if (result == ESP_OK) {
      processCANMessage(&message);
    }
    vTaskDelay(1); 
  }
}




