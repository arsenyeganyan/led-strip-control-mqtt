#include "ledStrip.h"
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B 16 
#define NUM_PIXELS 5

Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void ledSetup() {
  ws2812b.begin();
  ws2812b.clear();
  ws2812b.show();
}

void setAllPixels(int r, int g, int b) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        ws2812b.setPixelColor(i, ws2812b.Color(r, g, b));
    }
    ws2812b.show();
}

// void ledLoop() {
//   ws2812b.clear(); 
  
//   //turns all green with delay
//   for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {       
//     ws2812b.setPixelColor(pixel, ws2812b.Color(0, 255, 0)); 
//     ws2812b.show();           

//     delay(500); 
//   }

//   // turn off all pixels for two seconds
//   ws2812b.clear();
//   ws2812b.show(); 
//   delay(2000);  

//   // turn on all pixels to red at the same time for two seconds
//   for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {     
//     ws2812b.setPixelColor(pixel, ws2812b.Color(255, 0, 0)); 
//   }
//   ws2812b.show(); 
//   delay(1000); 

//   // turn off all pixels for one seconds
//   ws2812b.clear();
//   ws2812b.show(); 
//   delay(1000);
// }