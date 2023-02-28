#include <SPI.h>
//#include <TimerOne.h>

#define pin_noe 9
#define pin_b 7
#define pin_a 6
#define pin_sck 8
#define pin_clk 13
#define pin_r_data 11
byte scan_row = 2;

long pixel = 0;
auto by = HIGH;


void scanByte(byte value) {
  byte index = 0x01;
  for (byte i = 0; i < 8; i++) {
    digitalWrite(11, value & index);
    index <<= 1;
    digitalWrite (13 , HIGH);
    digitalWrite(13, LOW);
  }
}
byte pixelValue[] = {0xaa, 0b10001101, 0xdb, 0x55};
void scan() {
  if (true) {
    for (int i = 0; i < 4; i++) {
      scanByte(pixelValue[i]);
    }
  }
  digitalWrite(pin_noe, LOW);
  digitalWrite(pin_sck, HIGH); // Latch DMD shift register output
  digitalWrite(pin_sck, LOW); // (Deliberately left as digitalWrite to ensure decent latching time)
  digitalWrite(pin_a, scan_row & 0x01);
  digitalWrite(pin_b, scan_row & 0x02);
  scan_row = (scan_row + 1) % 4;
  digitalWrite(pin_noe, HIGH);
}
void setup() {
  // put your setup code here, to run once:
  /* We send out interleaved data for 4 rows at a time */
//  Timer1.initialize(1500);
//  Timer1.attachInterrupt(scan);

  digitalWrite(pin_clk, LOW);
  pinMode(pin_clk, OUTPUT);

  digitalWrite(pin_r_data, LOW);
  pinMode(pin_r_data, OUTPUT);

  digitalWrite(pin_noe, LOW);
  pinMode(pin_noe, OUTPUT);

  digitalWrite(pin_a, LOW);
  pinMode(pin_a, OUTPUT);

  digitalWrite(pin_b, LOW);
  pinMode(pin_b, OUTPUT);

  digitalWrite(pin_sck, LOW);
  pinMode(pin_sck, OUTPUT);




  //  for (int i = 0; i < 150; i++) {
  //    //    SPI.transfer(0);
  //    //    SPI.transfer(0);
  //    //    SPI.transfer(0);
  //    //    SPI.transfer(0xaa);
  //    digitalWrite(11, 0);
  //
  //    digitalWrite (13 , HIGH);
  //    pixel = !pixel;
  //    digitalWrite(13, LOW);
  //  }
  //
  digitalWrite(pin_noe, LOW);
  digitalWrite(pin_sck, HIGH); // Latch DMD shift register output
  digitalWrite(pin_sck, LOW); // (Deliberately left as digitalWrite to ensure decent latching time)
  digitalWrite(pin_a, scan_row & 0x01);
  digitalWrite(pin_b, scan_row & 0x02);
  scan_row = (scan_row + 1) % 4;
  digitalWrite(pin_noe, HIGH);
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //  for (int i = 0; i < 1; i++) {
  //    //    SPI.transfer(0);
  //    //    SPI.transfer(0);
  //    //    SPI.transfer(0);
  //    //    SPI.transfer(0xaa);
  //    digitalWrite(11, 1);
  //
  //    digitalWrite (13 , HIGH);
  //    pixel = !pixel;
  //    digitalWrite(13, LOW);
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
