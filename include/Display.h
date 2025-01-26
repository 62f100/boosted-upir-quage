// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Arduino_GFX_Library.h>

// Declare external variables
extern int current_gauge;
extern int target_gauge;
extern float mapPressure;
extern float lastMapPressure;

// Declare display as external
extern Arduino_GC9A01 display;

// Add new definitions
#define GAUGE_UPDATE_MS 16     // ~60Hz refresh rate
#define SMOOTHING_FACTOR 0.4f  // Increased for faster response
#define BUFFER_UPDATES 2       // Reduced buffer size

// Change declaration to extern
extern SemaphoreHandle_t displayMutex;  // This is just a declaration

extern uint32_t lastUpdateTime;
extern float pressureBuffer[];
extern uint8_t bufferIndex;

// Function declarations
void drawGaugeImage(uint8_t gauge_number);
void updateGaugePosition(float pressure);
void displayTaskFunction(void *parameter);
void initDisplay();
float getSmoothedPressure();
bool shouldUpdateGauge();

#endif // DISPLAY_H















