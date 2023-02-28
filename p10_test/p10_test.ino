#define pin_noe 9
#define pin_a 6
#define pin_b 7
#define pin_sck 8

#include <SPI.h>

byte scan_row = 0;
ISR(TIMER1_OVF_vect)
{
  static uint8_t skip_isrs = 0;
  skip_isrs = (skip_isrs + 1) % 2;
  if (skip_isrs)
    return;
  scan_running_dmds();
}
void scan_running_dmds() {
  //  for (int i = 0; i < 1 ; i++) {
  //    //    SPI.transfer(0);
  //    shiftOut(11, 13, MSBFIRST, 0x55);
  //    //    SPI.transfer(0x00);
  //    //    SPI.transfer(0x00); SPI.transfer(0x00);
  //  }
  //  // delayMicroseconds(10);
  //  //  digitalWrite(pin_noe, LOW);
  //  digitalWrite(pin_sck, HIGH); // Latch DMD shift register output
  //  digitalWrite(pin_sck, LOW);
  //  digitalWrite(pin_a, scan_row & 0x01);
  //  digitalWrite(pin_b, scan_row & 0x02);
  //  scan_row = (scan_row + 1) % 4;
  //
  //  digitalWrite(pin_noe, HIGH);
}
void setup() {
  Serial.begin(9600);
  //  char oldSREG = SREG;
  //  cli();
  //SPI.begin();
  //  SPI.setBitOrder(MSBFIRST);
  //  SPI.setDataMode(SPI_MODE0);  /
  //  TIMSK1 = _BV(TOIE1); // set overflow interrupt
  //  SREG = oldSREG;
  // put your setup code here, to run once:
  //  / CPOL=0, CPHA=0

  pinMode(11, OUTPUT); pinMode(13, OUTPUT);
  digitalWrite(pin_noe, LOW);
  pinMode(pin_noe, OUTPUT);

  digitalWrite(pin_a, LOW);
  pinMode(pin_a, OUTPUT);

  digitalWrite(pin_b, LOW);
  pinMode(pin_b, OUTPUT);

  digitalWrite(pin_sck, LOW);
  pinMode(pin_sck, OUTPUT);
  //
  //  for (int i = 0; i < 128; i++) {
  //    //    SPI.transfer(0);
  //    //    shiftOut(13, 11, MSBFIRST, 0x55);
  //    SPI.transfer(0xff);
  //    //    SPI.transfer(0x00); SPI.transfer(0x00);
  //  }
  digitalWrite(pin_sck, HIGH); // Latch DMD shift register output
  digitalWrite(pin_sck, LOW);
  for (int i = 0; i < 1 ; i++) {
    //    SPI.transfer(0);
    shiftOut(11, 13, MSBFIRST, 0x00);
    //    SPI.transfer(0x02);
    //    SPI.transfer(0x00); SPI.transfer(0x00);
  }
  digitalWrite(pin_noe, HIGH);
}
int a = 0xff;
void loop() {
  // put your main code here, to run repeatedly:

  // delayMicroseconds(10);
  //  digitalWrite(pin_noe, LOW);
  digitalWrite(pin_sck, HIGH); // Latch DMD shift register output
  digitalWrite(pin_sck, LOW);
  digitalWrite(pin_a, scan_row & 0x01);
  digitalWrite(pin_b, scan_row & 0x02);
  scan_row = (scan_row + 1) % 4;

  //  digitalWrite(pin_noe, HIGH);
  Serial.println(a);
  delay(2000);
}
