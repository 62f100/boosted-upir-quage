// display.cpp

#include "display.h"
#include "gauge_bw.h"

// Define display constants
#define SCREEN_WIDTH 240 
#define SCREEN_HEIGHT 240
#define GAUGE_IMAGES 61 

// Variables
float mapPressure = 0;
float lastMapPressure = 0.0;
int current_gauge = 0;
int target_gauge = 0; 

void drawGaugeImage(uint8_t gauge_number) {
    if (gauge_number >= GAUGE_IMAGES) {
        return;
    }
    
    const uint16_t* gauge_image;
    
    switch(gauge_number) {
        
        case 0:
            gauge_image = epd_bitmap_gauge_export_0000;
            break;
        case 1:
            gauge_image = epd_bitmap_gauge_export_0001;
            break;
        case 2:
            gauge_image = epd_bitmap_gauge_export_0002;
            break;
        case 3:
            gauge_image = epd_bitmap_gauge_export_0003;
            break;
        case 4:
            gauge_image = epd_bitmap_gauge_export_0004;
            break;
        case 5:
            gauge_image = epd_bitmap_gauge_export_0005;
            break;
        case 6:
            gauge_image = epd_bitmap_gauge_export_0006;
            break;
        case 7:
            gauge_image = epd_bitmap_gauge_export_0007;
            break;
        case 8:
            gauge_image = epd_bitmap_gauge_export_0008;
            break;
        case 9:
            gauge_image = epd_bitmap_gauge_export_0009;
            break;
        case 10:
            gauge_image = epd_bitmap_gauge_export_0010;
            break;
        case 11:
            gauge_image = epd_bitmap_gauge_export_0011;
            break;
        case 12:
            gauge_image = epd_bitmap_gauge_export_0012;
            break;
        case 13:
            gauge_image = epd_bitmap_gauge_export_0013;
            break;
        case 14:
            gauge_image = epd_bitmap_gauge_export_0014;
            break;
        case 15:
            gauge_image = epd_bitmap_gauge_export_0015;
            break;
        case 16:
            gauge_image = epd_bitmap_gauge_export_0016;
             break;
        case 17:
            gauge_image = epd_bitmap_gauge_export_0017;
            break;
        case 18:
            gauge_image = epd_bitmap_gauge_export_0018;
            break;
        case 19:
            gauge_image = epd_bitmap_gauge_export_0019;
            break; 
        case 20:
            gauge_image = epd_bitmap_gauge_export_0020;
            break;
        case 21:
            gauge_image = epd_bitmap_gauge_export_0021;
            break;
        case 22:
            gauge_image = epd_bitmap_gauge_export_0022;
            break;
        case 23:
            gauge_image = epd_bitmap_gauge_export_0023;
            break;
        case 24:
            gauge_image = epd_bitmap_gauge_export_0024;
            break;
         case 25:
            gauge_image = epd_bitmap_gauge_export_0025;
            break;       
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
            gauge_image = epd_bitmap_gauge_export_0053;
             break;
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

         

    }
    // Make sure width and height match your actual image dimensions
    display.startWrite();
    display.writeAddrWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    display.writePixels((uint16_t*)gauge_image, SCREEN_WIDTH * SCREEN_HEIGHT);
    display.endWrite(); 
    
}


void updateGaugePosition(float pressure) {
  // Subtract actual atmospheric pressure (106.50 kPa) to get relative pressure
  float relative_pressure = pressure - 106.50; 
  
  // Convert kPa to PSI (1 kPa = 0.145038 PSI)
  float pressure_psi = relative_pressure * 0.145038;

  // Map pressure values between -1 and 11 PSI to gauge positions (0-60)
  if (pressure_psi < -1) {
    // For pressures below -1 PSI, snap to lowest position
    target_gauge = 0;
    current_gauge = 0;  // Immediate update
  }
  else if (pressure_psi > 11) {
    // For pressures above 11 PSI, snap to highest position
    target_gauge = GAUGE_IMAGES - 1;
    current_gauge = GAUGE_IMAGES - 1;  // Immediate update
  }
  else {
    // Normal mapping between -1 and 11 PSI
    target_gauge = map(pressure_psi * 100, -100, 1100, 0, GAUGE_IMAGES - 1);
    
    // Constrain the gauge position to valid range
    target_gauge = constrain(target_gauge, 0, GAUGE_IMAGES - 1);

    // Smooth transition between gauge positions
    if (current_gauge < target_gauge) {
      current_gauge++;
    } else if (current_gauge > target_gauge) {
      current_gauge--;
    }
  }

  // Draw the gauge
  drawGaugeImage(current_gauge);

  // Debug output
  Serial.print("Pressure (PSI): ");
  Serial.print(pressure_psi);
  Serial.print(" Target gauge: ");
  Serial.print(target_gauge);
  Serial.print(" Current gauge: ");
  Serial.println(current_gauge);
}


void displayTaskFunction(void *parameter) {
  while(1) {
    if (mapPressure != lastMapPressure) {
      updateGaugePosition(mapPressure);
      lastMapPressure = mapPressure;
    }
    vTaskDelay(1);
  }
}














