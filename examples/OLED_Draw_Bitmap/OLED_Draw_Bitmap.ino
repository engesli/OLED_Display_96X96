/*
  The new OLED module drive IC has two version,
  1. SH1107G
  2. SSD1327
  
  Change the paramater of the drive IC name to init the module.
  **
  ** SeeedGrayOled.init(SSD1327);  // SSD1327 or SH1107G
  **

  Copyright - Seeedstudio
  Author - lambor
  Date - 4/24/2017
*/

#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>

static const unsigned char SeeedLogo[] PROGMEM = 
{

0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x60, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x06, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x01, 0xC0, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
0x07, 0x80, 0x01, 0xE0, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x0F, 0x80, 0x01, 0xE0,
0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0F, 0x00, 0x01, 0xE0, 0x08, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x30, 0x0F, 0x00, 0x01, 0xE0, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
0x0F, 0x00, 0x01, 0xE0, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0F, 0x00, 0x01, 0xE0,
0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x0F, 0x00, 0x01, 0xE0, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x38, 0x0F, 0x00, 0x01, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
0x0F, 0x80, 0x01, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x0F, 0x80, 0x01, 0xE0,
0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x0F, 0x80, 0x03, 0xE0, 0x78, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x1E, 0x07, 0x80, 0x03, 0xE0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E,
0x07, 0x80, 0x03, 0xE0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x07, 0x80, 0x03, 0xC1,
0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x87, 0xC0, 0x07, 0xC1, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0x83, 0xC0, 0x07, 0x83, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
0xC3, 0xC0, 0x07, 0x87, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE1, 0xE0, 0x07, 0x0F,
0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF0, 0xE0, 0x0F, 0x0F, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0xF8, 0xF0, 0x0E, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0xF8, 0x70, 0x1C, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x30, 0x18, 0x7E,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x18, 0x30, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1F, 0x88, 0x21, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0F, 0xC4, 0x47, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x0F, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x02, 0x00, 0x06, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x06,
0x00, 0x00, 0x60, 0x00, 0x7E, 0x3F, 0x0F, 0xC3, 0xF0, 0xFA, 0x0F, 0xDF, 0xE1, 0x9F, 0xEC, 0x7E,
0xE6, 0x73, 0x9C, 0xE7, 0x39, 0xCE, 0x1C, 0xDF, 0xE1, 0xB9, 0xEC, 0xE7, 0xE0, 0x61, 0xD8, 0x66,
0x1B, 0x86, 0x1C, 0x06, 0x61, 0xB0, 0x6D, 0xC3, 0x7C, 0x7F, 0xFF, 0xFF, 0xFF, 0x06, 0x0F, 0x86,
0x61, 0xB0, 0x6D, 0x83, 0x3E, 0x7F, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0xC6, 0x61, 0xB0, 0x6D, 0x83,
0xC3, 0x61, 0x18, 0x46, 0x03, 0x86, 0x18, 0x66, 0x61, 0xB0, 0x6D, 0xC3, 0xFE, 0x7F, 0x9F, 0xE7,
0xF9, 0xFE, 0x1F, 0xE6, 0x3F, 0x9F, 0xEC, 0xFE, 0x7E, 0x3F, 0x0F, 0xC3, 0xF0, 0xFA, 0x0F, 0xC6,
0x3F, 0x9F, 0xEC, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00,
0x00, 0x20, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x20, 0x82, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0xF3, 0xCF, 0x70, 0x9E, 0x79, 0xE7, 0x80, 0x00, 0x00,
0x00, 0x00, 0x7D, 0x9E, 0x68, 0x20, 0xB2, 0xC8, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x9E,
0x6F, 0x20, 0xB2, 0xF9, 0xE7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x46, 0x9A, 0x61, 0x20, 0xB2, 0xCB,
0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xF3, 0xCF, 0x30, 0x9E, 0x79, 0xE7, 0x90, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x02, 0x00, 0x00, 0x82, 0x60, 0x00, 0x00,
0xF8, 0x00, 0x00, 0x40, 0x40, 0x02, 0x00, 0x00, 0x83, 0x60, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x40,
0x60, 0xB7, 0x79, 0xE7, 0x81, 0xC7, 0x92, 0x70, 0x89, 0xE7, 0x9E, 0x78, 0x7C, 0xE2, 0xC9, 0x2C,
0x81, 0xCC, 0xD2, 0x40, 0xFB, 0x21, 0xB2, 0x48, 0x40, 0x62, 0xF9, 0x2C, 0x80, 0x8C, 0xD2, 0x40,
0x8B, 0xE7, 0xB0, 0x48, 0x40, 0xE2, 0xC9, 0x2C, 0x80, 0x84, 0xD2, 0x40, 0x8B, 0x2D, 0x92, 0x48,
0x7D, 0xB3, 0x79, 0x27, 0x80, 0x87, 0x9E, 0x40, 0x8D, 0xE7, 0x9E, 0x48, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup()
{
  Wire.begin();	
  SeeedGrayOled.init(SH1107G);          // initialize SEEED OLED display
  
  SeeedGrayOled.clearDisplay();                  //  clear the screen and set start position to top left corner
  //Draw binary Bitmap
  SeeedGrayOled.drawBitmap(SeeedLogo,96*96/8);   //  Draw binary Bitmap (96 pixels *96 pixels  / 8) bytes
}

void loop()
{
  
}





