// main.cpp

#include <Arduino.h>
#include "display.h"
#include "can.h"
#include "config.h"

TaskHandle_t displayTask;
TaskHandle_t canTask;

// Create display instance with correct pins
Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, TFT_MISO);
Arduino_GC9A01 display = Arduino_GC9A01(bus, TFT_RES, 0 /* rotation */, true /* IPS */);


void setup() {
  Serial.begin(115200);

  // Initialize PSRAM if available
  if(!psramInit()) {
    Serial.println("PSRAM not available");
  } else {
    Serial.println("PSRAM initialized");
  }

  // Initialize display with faster speed
  if (!display.begin(40000000)) { // Try 40MHz
    Serial.println("Display initialization failed!");
    while (1) delay(5);
  }

  pinMode(TFT_BLK, OUTPUT);
  digitalWrite(TFT_BLK, HIGH);
  display.fillScreen(BLACK);

  // Start with gauge at neutral position (image 16)
  current_gauge = 4;
  target_gauge = 4;
  drawGaugeImage(4); // Draw the neutral position first

  setupTWAI();

  // Create tasks on separate cores
  xTaskCreatePinnedToCore(
      displayTaskFunction,
      "displayTask",
      10000,
      NULL,
      1,
      &displayTask,
      0
  );

  xTaskCreatePinnedToCore(
      canTaskFunction,
      "canTask",
      10000,
      NULL,
      2,
      &canTask,
      1
  );
}

void loop() {
  vTaskDelay(1); // Keep watchdog happy
}



