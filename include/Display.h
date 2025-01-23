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

// Function declarations
void drawGaugeImage(uint8_t gauge_number);
void updateGaugePosition(float pressure);
void displayTaskFunction(void *parameter);

#endif // DISPLAY_H















