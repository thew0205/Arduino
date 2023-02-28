/*
  Scrolling alphabet demo, displays characters one at a time into a scrolling box.
*/

#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>

// Set Width to the number of displays wide you have
const int WIDTH = 1;

// You can change to a smaller font (two lines) by commenting this line,
// and uncommenting the line after it:
//const uint8_t *FONT = Arial14;
const uint8_t *FONT = SystemFont5x7;

const char *MESSAGE = "abcdefghijklmnopqrstuvwxyz";

SoftDMD dmd(WIDTH, 2); // DMD controls the entire display
DMD_TextBox box(dmd); // "box" provides a text box to automatically write to/scroll the display

void bitPixels(DMDFrame& dmd, byte* pixel, int width, int height , int x = 0, int y = 0) {

  byte index = 0x80;
  for (int h = 0 ; h < height; h++ ) {
    for (int w = 0 ; w < width; w++ ) {
      if (index == 0x08) {
        Serial.print(", 0b");
      }
      dmd.setPixel(x + w, y + h, (pixel[(w  + h * 32) / 8]&index) ? GRAPHICS_ON : GRAPHICS_OFF);
      Serial.print(pixel[(w  + h * 32) / 8]&index ? 1 : 0 );
      //      Serial.print(h, HEX);
      //      Serial.print("     ");
      //      Serial.print(index);
      //      Serial.print("     ");
      //      Serial.println( pixel[w / 8], HEX );
      if (index == 0x01) {
        index = 0x80;

      } else {
        index >>= 1;
      }


    }


    Serial.println();
  }

}

void write_0(DMDFrame& dmd , int x = 0 , int y = 0) {
  for (int i = 0 ; i < 3 ; i++) {
    dmd.setPixel(x + 1 + i, y);
    dmd.setPixel(x + 1 + i, y + 4);
    dmd.setPixel(x , y + 1 + i);
    dmd.setPixel(x + 4 , y + 1 + i);
    dmd.setPixel(x + 4 - 1 - i , y + 1 + i);
  }

}

void write_1(DMDFrame& dmd , int x = 0 , int y = 0) {
  for (int i = 0 ; i < 5 ; i++) {
    dmd.setPixel(x + 2, y + i);
  }
  for (int i = 0 ; i < 3 ; i++) {
    dmd.setPixel(x + 1 + i, y + 4);
  }
  dmd.setPixel(x + 1, y + 1);

}

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  dmd.setBrightness(255);
  dmd.selectFont(FONT);
  dmd.begin();
byte pit1[]={0xff, 0xff, 
0xf8, 0x1f, 
0xf9, 0x9f, 
0xfb, 0x5f, 
0xfb, 0xc1, 
0x82, 0x8d, 
0xb3, 0x4d, 
0xb1, 0xd9, 
0xab, 0x59, 
0x9b, 0xc1, 
0x82, 0xdf, 
0xfa, 0x9f, 
0xfb, 0xdf, 
0xfa, 0x9f, 
0xf8, 0x1f, 
0xff, 0xff};
  
  byte pit[] = {
    0b00000000, 0b00011111, 0b11111000, 0b00000000,
    0b00000000, 0b00011111, 0b11111000, 0b00000000,
    0b00000001, 0b11111111, 0b11111111, 0b10000000,
    0b00000001, 0b11111111, 0b11111111, 0b10000000,
    0b00000000, 0b11111111, 0b11111111, 0b00000000,
    0b00000111, 0b11111111, 0b11111111, 0b11100000,
    0b00000111, 0b11111111, 0b11111111, 0b11100000,
    0b00111111, 0b10111111, 0b11111111, 0b11111100,
    0b00111111, 0b11111111, 0b11111111, 0b11111100,
    0b00111111, 0b11111111, 0b11111111, 0b11111100,
    0b00011111, 0b11111111, 0b11111111, 0b11111100,
    0b00111111, 0b11111100, 0b00011111, 0b10000011,
    0b00101101, 0b01111100, 0b00111111, 0b10000011,
    0b00010101, 0b11111100, 0b00110111, 0b10000011,
    0b11111111, 0b10111100, 0b10011111, 0b10001011,
    0b11111111, 0b11110100, 0b00101101, 0b10000010,
    0b11111111, 0b10111111, 0b11010111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11110101, 0b11111111, 0b11111111, 0b11111111,
    0b11101011, 0b11111111, 0b11111111, 0b11111111,
    0b11101101, 0b11111111, 0b01111110, 0b10101010,
    0b11110001, 0b11111000, 0b00111110, 0b10010111,
    0b11101000, 0b11111100, 0b00111110, 0b10001010,
    0b11110001, 0b01111000, 0b00101111, 0b00011010,
    0b11000000, 0b01101100, 0b00111010, 0b00000011,
    0b11000000, 0b01011100, 0b00110110, 0b00000001

  };
  byte pixels[] = {0b00000000, 0b00011111, 0b11100000, 0b00000000,
                   0b00000111, 0b11111111, 0b11110100, 0b00000000,
                   0b00000000, 0b00000111, 0b11111111, 0b11000000,
                   0b00000000, 0b11111111, 0b11110101, 0b00000000,
                   0b00000000, 0b10011111, 0b11100001, 0b00000000,
                   0b00000000, 0b01000000, 0b00000010, 0b00000000,
                   0b00000000, 0b00111110, 0b01111100, 0b00000000,
                   0b00000000, 0b00000001, 0b10000000, 0b00000000,
                   0b00000000, 0b00000001, 0b10000000, 0b00000000,
                   0b00000000, 0b00111110, 0b01111100, 0b00000000,
                   0b00000000, 0b01000000, 0b00000010, 0b00000000,
                   0b00000000, 0b10011111, 0b11100001, 0b00000000,
                   0b00000000, 0b11111111, 0b11110101, 0b00000000,
                   0b00000000, 0b00011111, 0b11111111, 0b11000000,
                   0b00000111, 0b11111111, 0b11110100, 0b00000000,
                   0b00000000, 0b00011111, 0b11100000, 0b00000000,
                  };
  byte pixel[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
  bitPixels(dmd,  pit1, 16, 16);
  //  write_0(dmd, 26, 0);
  //  write_1(dmd, 26, 11);


}

// the loop routine runs over and over again forever:
void loop() {
  //  const char *next = MESSAGE;
  //  while(*next) {
  //    Serial.print(*next);
  //    box.print(*next);
  //    delay(200);
  //    next++;
  //  }
}
