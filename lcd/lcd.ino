/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//LiquidCrystal lcd(8,9,10,0,1,2,3, d4, d5, d6, d7);
extern "C"{
  void send_character(); void send_function(); void initf();
}
void setup() {
  initf();
//  delay(100);
  // set up the LCD's number of columns and rows:
//  lcd.begin(16, 2);
  // Print a message to the LCD.
//  lcd.print("Hello, aas!");
//  PORTD = 0x51;
//  PORTC |=  (0x01 << 0)|(0x01 << 2) ;
//
//
//      PORTC = 0 ;

asm volatile("ldi r17, 0b00111000");
send_function();

asm volatile("ldi r17, 0b00000010");
send_function();

asm volatile("ldi r17, 0b00001111");
send_function();

asm volatile("ldi r17, 0b00000110");
send_function();

asm volatile("ldi r17, 0x30");
      send_character();
      asm volatile("ldi r17, 0x31");
       send_character();
       asm volatile("ldi r17, 0x32");
        send_character();

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
//  play();
//  // print the number of seconds since reset:
//  lcd.print(millis() / 1000);
}


/*
copy_data_section:
    ldi zl, lo8(_end_text )
    ldi zh, hi8(_end_text )
    
    ldi xl, lo8(_start_data)
    ldi xh, hi8(_start_data )
    ldi yl, lo8(_end_data)
    ldi yh, hi8(_end_data )
copy_data_section_loop:
    cp xl, yl
    cpc xh, yh
    breq end_copy_data_section
    lpm r20, z
    st x+, r20
    adiw zl,0x01
    rjmp copy_data_section_loop
end_copy_data_section:


copy_bss_section:
    ldi xl, lo8(_start_bss)
    ldi xh, hi8(_start_bss )
    ldi yl, lo8(_end_bss )
    ldi yh, hi8(_end_bss )
copy_bss_section_loop:
    cp xl, yl
    cpc xh, yh
    breq end_copy_bss_section
    st x+, r1
    rjmp copy_bss_section_loop
end_copy_bss_section:*/
