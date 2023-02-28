#include <SPI.h>

// Arduino pins used for the display connection
#define PIN_DMD_nOE 9 // D9 active low Output Enable, setting this low lights all the LEDs in the
// selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_A 6       // D6
#define PIN_DMD_B 7       // D7
#define PIN_DMD_CLK 13    // D13_SCK  is SPI Clock if SPI is used
#define PIN_DMD_SCLK 8    // D8
#define PIN_DMD_R_DATA 11 // D11_MOSI is SPI Master Out if SPI is used
// Define this chip select pin that the Ethernet W5100 IC or other SPI device
// uses if it is in use during a DMD scan request then scanDisplayBySPI() will
// exit without conflict! (and skip that scan)
#define PIN_OTHER_SPI_nCS 10
// ######################################################################################################################
// ######################################################################################################################

// DMD I/O pin macros
#define LIGHT_DMD_ROW_01_05_09_13()                                            \
  {                                                                            \
    digitalWrite(PIN_DMD_B, LOW);                                              \
    digitalWrite(PIN_DMD_A, LOW);                                              \
  }
#define LIGHT_DMD_ROW_02_06_10_14()                                            \
  {                                                                            \
    digitalWrite(PIN_DMD_B, LOW);                                              \
    digitalWrite(PIN_DMD_A, HIGH);                                             \
  }
#define LIGHT_DMD_ROW_03_07_11_15()                                            \
  {                                                                            \
    digitalWrite(PIN_DMD_B, HIGH);                                             \
    digitalWrite(PIN_DMD_A, LOW);                                              \
  }
#define LIGHT_DMD_ROW_04_08_12_16()                                            \
  {                                                                            \
    digitalWrite(PIN_DMD_B, HIGH);                                             \
    digitalWrite(PIN_DMD_A, HIGH);                                             \
  }
#define LATCH_DMD_SHIFT_REG_TO_OUTPUT()                                        \
  {                                                                            \
    digitalWrite(PIN_DMD_SCLK, HIGH);                                          \
    digitalWrite(PIN_DMD_SCLK, LOW);                                           \
  }
#define OE_DMD_ROWS_OFF()                                                      \
  { digitalWrite(PIN_DMD_nOE, LOW); }
#define OE_DMD_ROWS_ON()                                                       \
  { digitalWrite(PIN_DMD_nOE, HIGH); }
//byte * bDMDScreenRAM = (byte *) malloc();
bool valu = false;
void setup() {
  // initialize the SPI port
  SPI.begin();   // probably don't need this since it inits the port pins only, which we do just below with the appropriate DMD interface setup
  SPI.setBitOrder(MSBFIRST);  //
  SPI.setDataMode(SPI_MODE0); // CPOL=0, CPHA=0
  SPI.setClockDivider(SPI_CLOCK_DIV4);  // system clock / 4 = 4MHz SPI CLK to shift registers. If using a short cable, can put SPI_CLOCK_DIV2 here for 2x faster updates

  digitalWrite(PIN_DMD_A, LOW); //
  digitalWrite(PIN_DMD_B, LOW); //
  digitalWrite(PIN_DMD_CLK, LOW); //
  digitalWrite(PIN_DMD_SCLK, LOW);  //
  digitalWrite(PIN_DMD_R_DATA, HIGH); //
  digitalWrite(PIN_DMD_nOE, LOW); //

  pinMode(PIN_DMD_A, OUTPUT); //
  pinMode(PIN_DMD_B, OUTPUT); //
  pinMode(PIN_DMD_CLK, OUTPUT); //
  pinMode(PIN_DMD_SCLK, OUTPUT);  //
  pinMode(PIN_DMD_R_DATA, OUTPUT);  //
  pinMode(PIN_DMD_nOE, OUTPUT); //
  delay(10);

  for (int i = 0; i < 16; i++) {
    SPI.transfer(0x55);
  }
   SPI.transfer(0xf1);
  OE_DMD_ROWS_OFF();
  LATCH_DMD_SHIFT_REG_TO_OUTPUT();
  LIGHT_DMD_ROW_01_05_09_13();
  OE_DMD_ROWS_ON();
//  digitalWrite(PIN_DMD_nOE, HIGH);
//   delay(10);

}

void loop() {
  
  //  for (int i = 0; i < 4; i++) {
  //    SPI.transfer(0x55);
  //  }
      OE_DMD_ROWS_OFF();
  //  LATCH_DMD_SHIFT_REG_TO_OUTPUT();
  //  LIGHT_DMD_ROW_01_05_09_13();
    OE_DMD_ROWS_ON();
  // put your main code here, to run repeatedly:
  //  for (int i = 0; i < 128; i++) {
  //    digitalWrite(11, valu = !valu);
  //    digitalWrite(13, HIGH);
  //    digitalWrite(13, LOW);
  //  }
  //  digitalWrite(8, HIGH);
  //  digitalWrite(8, LOW);
  //  OE_DMD_ROWS_OFF();
  //  LATCH_DMD_SHIFT_REG_TO_OUTPUT();
  //  LIGHT_DMD_ROW_01_05_09_13();
  //  OE_DMD_ROWS_ON();

}
