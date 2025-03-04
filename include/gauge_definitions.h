// gauge_definitions.h
#ifndef GAUGE_DEFINITIONS_H
#define GAUGE_DEFINITIONS_H

#include <Arduino.h>

// Add this map function for float values
inline float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - out_min) + out_min;
}

// Screen dimensions - using direct values since we know it's 240x240
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define CENTER_X 120
#define CENTER_Y 120

// Gauge radius definitions
#define OUTER_RADIUS 110    // Outer edge of hash marks
#define INNER_RADIUS 90     // Inner edge of hash marks
#define HIGHLIGHT_WIDTH 3   // Width of the highlighted hash mark

// Angle definitions (in degrees)
#define START_ANGLE 135    // Start angle for the gauge (bottom left)
#define END_ANGLE 45      // End angle for the gauge (bottom right)

// PSI definitions
#define MIN_PSI 2.4f
#define MAX_PSI 8.0f
#define PSI_PER_STEP 0.2f
#define STARTING_PSI 2.4f

// Calculate total steps based on PSI range
#define TOTAL_STEPS 60

// Function to convert PSI to angle
inline float psiToAngle(float psi) {
    return mapf(psi * 10.0f, MIN_PSI * 10.0f, MAX_PSI * 10.0f, START_ANGLE, END_ANGLE);
}

// Function to convert steps to angle
inline float stepToAngle(int step) {
    return mapf((float)step, 0.0f, (float)TOTAL_STEPS, START_ANGLE, END_ANGLE);
}

void drawHighlightedHash(int position, uint16_t color);

#endif



