// encoder_handler.h

#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H

#include <Arduino.h>
#include "gauge_definitions.h"

class EncoderHandler {
private:
    const int clockPin;
    const int dataPin;
    int lastClockState;
    int currentPosition;
    const int totalSteps;

public:
    EncoderHandler(int clkPin, int dtPin) 
        : clockPin(clkPin), 
          dataPin(dtPin),
          totalSteps(TOTAL_STEPS) {
        
        pinMode(clockPin, INPUT);
        pinMode(dataPin, INPUT);
        lastClockState = digitalRead(clockPin);
        // Calculate starting position based on STARTING_PSI
        currentPosition = (STARTING_PSI - MIN_PSI) / PSI_PER_STEP;
    }

    int getCurrentPosition() {
        return currentPosition;
    }

    float getCurrentPSI() {
        return MIN_PSI + (currentPosition * PSI_PER_STEP);
    }

    float getCurrentAngle() {
        return stepToAngle(currentPosition);
    }

    void update() {
        int clockState = digitalRead(clockPin);

        if (clockState != lastClockState && clockState == LOW) {
            if (digitalRead(dataPin) != clockState) {
                // Clockwise
                if (currentPosition < totalSteps) currentPosition++;
            } else {
                // Counter-clockwise
                if (currentPosition > 0) currentPosition--;
            }
        }
        lastClockState = clockState;
    }
};

#endif
