#include <SPI.h>
#include <TimerOne.h>

#define pin_noe 9
#define pin_b 7
#define pin_a 6
#define pin_sck 8
#define pin_clk 13
#define pin_r_data 11
byte bDMDByte = 0;
#define PIN_DMD_nOE                                                            \
  9 // D9 active low Output Enable, setting this low lights all the LEDs in the
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
byte pixel = 0;

void scan() {
  if (pixel < 5) {

    for (int i = 0; i < 1; i++) {
      //    SPI.transfer(0xaa);
      //        SPI.transfer(0xaa);
      //        SPI.transfer(0x55);
      SPI.transfer(0xaa);
      //    digitalWrite(11,! scan_row);
      //
      //    digitalWrite (13 , HIGH);
      //    pixel = !pixel;
      //    digitalWrite(13, LOW);
    }
  }
  OE_DMD_ROWS_OFF();
  LATCH_DMD_SHIFT_REG_TO_OUTPUT();
  switch (bDMDByte) {
    case 0:     // row 1, 5, 9, 13 were clocked out
      LIGHT_DMD_ROW_01_05_09_13();
      bDMDByte = 1;
      break;
    case 1:     // row 2, 6, 10, 14 were clocked out
      LIGHT_DMD_ROW_02_06_10_14();
      bDMDByte = 2;
      break;
    case 2:     // row 3, 7, 11, 15 were clocked out
      LIGHT_DMD_ROW_03_07_11_15();
      bDMDByte = 3;
      break;
    case 3:     // row 4, 8, 12, 16 were clocked out
      LIGHT_DMD_ROW_04_08_12_16();
      bDMDByte = 0;
      break;
  }
  OE_DMD_ROWS_ON();
}
void setup() {
  // put your setup code here, to run once:
  /* We send out interleaved data for 4 rows at a time */
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan);
  SPI.begin();    // probably don't need this since it inits the port pins only, which we do just below with the appropriate DMD interface setup
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


  for (int i = 0; i < 150; i++) {
    SPI.transfer(0x00);
    //    SPI.transfer(0);
    //    SPI.transfer(0);
    //    SPI.transfer(0xaa);
    //    digitalWrite(11, 0);
    //
    //    digitalWrite (13 , HIGH);
    //    pixel = !pixel;
    //    digitalWrite(13, LOW);
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  //  for (int i = 0; i < 32; i++) {
  //
  //    SPI.transfer(0);
  //  }
  //  digitalWrite(pin_noe, LOW);
  //  digitalWrite(pin_sck, HIGH); // Latch DMD shift register output
  //  digitalWrite(pin_sck, LOW); // (Deliberately left as digitalWrite to ensure decent latching time)
  //  digitalWrite(pin_a, scan_row & 0x01);
  //  digitalWrite(pin_b, scan_row & 0x02);
  //  scan_row = (scan_row + 1) % 4;
  //  digitalWrite(pin_noe, HIGH);
  //  delay(1000);
}
