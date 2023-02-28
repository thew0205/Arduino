
#include <SPI.h>
void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);  // CPOL=0, CPHA=0
  pinMode(10, OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
}
char a = 'a';
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10, LOW);
// delay(50);
  SPI.transfer(a++);
    digitalWrite(10, HIGH);
  delay(50);
}
