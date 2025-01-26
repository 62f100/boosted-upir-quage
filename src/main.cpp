// main.cpp

#include <Arduino.h>
#include "display.h"
#include "can.h"
#include "config.h"
#include <ESP32Encoder.h>

TaskHandle_t displayTask;
TaskHandle_t canTask;

// Create display instance with correct pins
Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, TFT_MISO);
Arduino_GC9A01 display = Arduino_GC9A01(bus, TFT_RES, 0 /* rotation */, true /* IPS */);

ESP32Encoder encoder;
volatile int encoderValue = 0;

void setup() {
    Serial.begin(115200);

    // Initialize PSRAM first
    if(!psramInit()) {
        Serial.println("PSRAM not available");
    } else {
        Serial.println("PSRAM initialized");
    }

    // Create semaphore before using it
    displayMutex = xSemaphoreCreateMutex();
    if (displayMutex == NULL) {
        Serial.println("Failed to create display mutex!");
        while(1) delay(100);  // Fatal error
    }

    // Initialize display with faster speed
    if (!display.begin(40000000)) {
        Serial.println("Display initialization failed!");
        while(1) delay(100);
    }

    pinMode(TFT_BLK, OUTPUT);
    digitalWrite(TFT_BLK, HIGH);
    display.fillScreen(BLACK);

    // Initialize CAN before creating tasks
    setupTWAI();

    // Setup encoder
    ESP32Encoder::useInternalWeakPullResistors = UP;
    encoder.attachHalfQuad(ENCODER_CLK, ENCODER_DT);
    encoder.setCount(0);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Set initial gauge position
    current_gauge = 4;
    target_gauge = 4;
    
    // Draw initial gauge after all initialization
    xSemaphoreTake(displayMutex, portMAX_DELAY);
    drawGaugeImage(4);
    xSemaphoreGive(displayMutex);

    // Create tasks last
    xTaskCreatePinnedToCore(
        displayTaskFunction,
        "displayTask",
        8192,
        NULL,
        3,
        &displayTask,
        0
    );

    xTaskCreatePinnedToCore(
        canTaskFunction,
        "canTask",
        4096,
        NULL,
        2,
        &canTask,
        1
    );
}

void loop() {
    vTaskDelay(1); // Keep watchdog happy
}



