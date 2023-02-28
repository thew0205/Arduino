/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
volatile int a = 10;
volatile long long c = 9;
volatile long long  b ;
volatile long long d;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.

  DDRB |= (1 << PORT5);
  a -= 100;
  Serial.print(a);

}

// the loop function runs over and over again forever
void loop() {
  PINB |=  (1 << PORT5); // turn the LED on (HIGH is the voltage level)
  __asm__("nop");
  for (volatile uint32_t i = 0; i < 100000; i++) {
    /* code */
  }
  PORTB ^=  (1 << PORT5);   for (volatile uint32_t i = 0; i < 100000; i++) {
    /* code */
  }
  // wait for a second
  // wait for a second
}

//C:\Program Files (x86)\Arduino\hardware\tools\avr\bin> avrdude -C../etc/avrdude.conf -v -patmega328p -cstk500v1 -PCOM8 -b19200 -Ulfuse:r:m
