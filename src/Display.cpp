// display.cpp

#include "display.h"
#include "gauge_bw.h"
#include "gauge_definitions.h"

// Define display constants
#define SCREEN_WIDTH 240 
#define SCREEN_HEIGHT 240
#define GAUGE_IMAGES 61 
#define BUFFER_UPDATES 2      // Reduce buffer size
#define GAUGE_UPDATE_MS 16    // ~60Hz updates

// Add new constants at top
#define NEEDLE_WIDTH 20    // Width of needle area to update
#define NEEDLE_HEIGHT 120  // Height of needle area
#define NEEDLE_X (SCREEN_WIDTH/2 - NEEDLE_WIDTH/2)
#define NEEDLE_Y (SCREEN_HEIGHT/2 - NEEDLE_HEIGHT/2)

// Add at top with other defines
#define CENTER_X (SCREEN_WIDTH / 2)
#define CENTER_Y (SCREEN_HEIGHT / 2)
#define HIGHLIGHT_WIDTH 3
#define INNER_RADIUS 90
#define OUTER_RADIUS 110

// Variables
float mapPressure = 0;
float lastMapPressure = 0.0;
int current_gauge = 0;
int target_gauge = 0; 

SemaphoreHandle_t displayMutex = NULL;  // Definition with initialization
uint32_t lastUpdateTime = 0;
float pressureBuffer[BUFFER_UPDATES] = {0};
uint8_t bufferIndex = 0;

void initDisplay() {
    displayMutex = xSemaphoreCreateMutex();
    // ...existing display init code...
}

float getSmoothedPressure() {
    float sum = 0;
    for(int i = 0; i < BUFFER_UPDATES; i++) {
        sum += pressureBuffer[i];
    }
    return sum / BUFFER_UPDATES;
}

bool shouldUpdateGauge() {
    uint32_t now = millis();
    if(now - lastUpdateTime >= GAUGE_UPDATE_MS) {
        lastUpdateTime = now;
        return true;
    }
    return false;
}

// Add debugging flag
bool debug_drawing = true;

// Add this function to convert encoder position to angle
// float stepToAngle(int step) {
//     return map(step, 0, TOTAL_STEPS, 240, -60); // Map steps to degrees (300 degree range)
// }

void drawGaugeImage(uint8_t gauge_number) {
    if (gauge_number >= GAUGE_IMAGES) {
        Serial.printf("Invalid gauge number: %d\n", gauge_number);
        return;
    }
    
    static uint8_t last_gauge = 255;
    const uint16_t* gauge_image = nullptr;
    
    // Complete switch case for all images
    switch(gauge_number) {
        case 0: gauge_image = epd_bitmap_gauge_export_0000; break;
        case 1: gauge_image = epd_bitmap_gauge_export_0001; break;
        case 2: gauge_image = epd_bitmap_gauge_export_0002; break;
        case 3: gauge_image = epd_bitmap_gauge_export_0003; break;
        case 4: gauge_image = epd_bitmap_gauge_export_0004; break;
        case 5: gauge_image = epd_bitmap_gauge_export_0005; break;
        case 6: gauge_image = epd_bitmap_gauge_export_0006; break;
        case 7: gauge_image = epd_bitmap_gauge_export_0007; break;
        case 8: gauge_image = epd_bitmap_gauge_export_0008; break;
        case 9: gauge_image = epd_bitmap_gauge_export_0009; break;
        case 10:gauge_image = epd_bitmap_gauge_export_0010; break;
        case 11:gauge_image = epd_bitmap_gauge_export_0011; break;
        case 12:gauge_image = epd_bitmap_gauge_export_0012; break;
        case 13:gauge_image = epd_bitmap_gauge_export_0013; break;
        case 14:gauge_image = epd_bitmap_gauge_export_0014; break;
        case 15:gauge_image = epd_bitmap_gauge_export_0015; break;
        case 16:gauge_image = epd_bitmap_gauge_export_0016; break;
        case 17:gauge_image = epd_bitmap_gauge_export_0017; break;
        case 18:gauge_image = epd_bitmap_gauge_export_0018; break;
        case 19:gauge_image = epd_bitmap_gauge_export_0019; break; 
        case 20:gauge_image = epd_bitmap_gauge_export_0020; break;
        case 21:gauge_image = epd_bitmap_gauge_export_0021; break;
        case 22:gauge_image = epd_bitmap_gauge_export_0022; break;
        case 23:gauge_image = epd_bitmap_gauge_export_0023; break;
        case 24:gauge_image = epd_bitmap_gauge_export_0024; break;
        case 25:gauge_image = epd_bitmap_gauge_export_0025; break;       
        case 26:
            gauge_image = epd_bitmap_gauge_export_0026;
            break;
        case 27:
            gauge_image = epd_bitmap_gauge_export_0027;
            break;
        case 28:
            gauge_image = epd_bitmap_gauge_export_0028;
            break;
         case 29:
            gauge_image = epd_bitmap_gauge_export_0029;
            break;
        case 30:
            gauge_image = epd_bitmap_gauge_export_0030;
            break;
        case 31:
            gauge_image = epd_bitmap_gauge_export_0031;
            break;
        case 32:
            gauge_image = epd_bitmap_gauge_export_0032;
            break;
        case 33:
            gauge_image = epd_bitmap_gauge_export_0033;
            break;
        case 34:
            gauge_image = epd_bitmap_gauge_export_0034;
            break;
        case 35:
            gauge_image = epd_bitmap_gauge_export_0035;
            break;
        case 36:
            gauge_image = epd_bitmap_gauge_export_0036;
            break;
        case 37:
            gauge_image = epd_bitmap_gauge_export_0037;
            break;
        case 38:
            gauge_image = epd_bitmap_gauge_export_0038;
            break;
        case 39:
            gauge_image = epd_bitmap_gauge_export_0039;
            break;
        case 40:
            gauge_image = epd_bitmap_gauge_export_0040;
            break;
        case 41:
            gauge_image = epd_bitmap_gauge_export_0041;
            break;
        case 42:
            gauge_image = epd_bitmap_gauge_export_0042;
            break;
        case 43:
            gauge_image = epd_bitmap_gauge_export_0043;
            break;
        case 44:
            gauge_image = epd_bitmap_gauge_export_0044;
            break;
        case 45:
            gauge_image = epd_bitmap_gauge_export_0045;
            break;
        case 46:
            gauge_image = epd_bitmap_gauge_export_0046;
            break;
        case 47:
            gauge_image = epd_bitmap_gauge_export_0047;
            break;
        case 48:
            gauge_image = epd_bitmap_gauge_export_0048;
            break;
        case 49:
            gauge_image = epd_bitmap_gauge_export_0049;
        break;
        case 50:
            gauge_image = epd_bitmap_gauge_export_0050;
        break;
        case 51:
            gauge_image = epd_bitmap_gauge_export_0051;
        break;
        case 52:
             gauge_image = epd_bitmap_gauge_export_0052;
        break;
        case 53:
            gauge_image = epd_bitmap_gauge_export_0053; break;
        case 54:
            gauge_image = epd_bitmap_gauge_export_0054;
        break;
        case 55:
             gauge_image = epd_bitmap_gauge_export_0055;
        break;
        case 56:
             gauge_image = epd_bitmap_gauge_export_0056;
        break; 

        case 57:
        gauge_image = epd_bitmap_gauge_export_0057;
        break;
        case 58:
        gauge_image = epd_bitmap_gauge_export_0058;
        break;
        case 59:
        gauge_image = epd_bitmap_gauge_export_0059;
        break;      

        case 60:
        gauge_image = epd_bitmap_gauge_export_0060;
        break;
        default:
            Serial.printf("No image for gauge number: %d\n", gauge_number);
            return;
    }
    
    if (gauge_image == nullptr || displayMutex == nullptr) {
        Serial.println("Invalid pointer!");
        return;
    }

    display.startWrite();
    display.writeAddrWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    display.writePixels((uint16_t*)gauge_image, SCREEN_WIDTH * SCREEN_HEIGHT);
    display.endWrite();
}

// Add function to draw just the highlight
void drawHighlightedHash(int position, uint16_t color) {
    float angle = stepToAngle(position);
    float radians = (angle - 90) * PI / 180.0;
    
    if (xSemaphoreTake(displayMutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
        for(int i = -HIGHLIGHT_WIDTH/2; i <= HIGHLIGHT_WIDTH/2; i++) {
            float offset_radians = ((angle + i) - 90) * PI / 180.0;
            int x1_offset = CENTER_X + (INNER_RADIUS * cos(offset_radians));
            int y1_offset = CENTER_Y + (INNER_RADIUS * sin(offset_radians));
            int x2_offset = CENTER_X + (OUTER_RADIUS * cos(offset_radians));
            int y2_offset = CENTER_Y + (OUTER_RADIUS * sin(offset_radians));
            display.drawLine(x1_offset, y1_offset, x2_offset, y2_offset, color);
        }
        xSemaphoreGive(displayMutex);
    }
}

void updateGaugePosition(float pressure) {
    float relative_pressure = pressure - 106.50;
    float pressure_psi = relative_pressure * 0.145038;

    int new_target;
    if(pressure_psi < -1) {
        new_target = 0;
    } else if(pressure_psi > 11) {
        new_target = GAUGE_IMAGES - 1;
    } else {
        new_target = map(pressure_psi * 100, -100, 1100, 0, GAUGE_IMAGES - 1);
    }

    current_gauge = constrain(new_target, 0, GAUGE_IMAGES - 1);
    drawGaugeImage(current_gauge);
}

// Optimize display task timing
void displayTaskFunction(void *parameter) {
    while(1) {
        if(mapPressure != lastMapPressure) {
            updateGaugePosition(mapPressure);
            lastMapPressure = mapPressure;
        }
        vTaskDelay(1); // Minimal delay
    }
}














