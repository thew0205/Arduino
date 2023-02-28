/*
  Countdown on a single DMD display
*/

#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>

const int LED_pin = 13;
volatile byte count;
const int COUNTDOWN_FROM = 12;
int counter = COUNTDOWN_FROM;
ISR(TIMER2_OVF_vect)
{
  count++;
}

SoftDMD dmd(1, 1); // DMD controls the entire display
DMD_TextBox box(dmd, 0, 2);  // "box" provides a text box to automatically write to/scroll the display

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, LOW);
  cli();
  TCCR2A = 0; TCCR2B = 0;
  //OCR2A = reload;
  //TCCR2A = 1<<WGM21;
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 = (1 << TOIE2);
  sei();
  Serial.print("OCR2A: ");
  Serial.println(OCR2A, HEX);
  Serial.print("TCCR2A: ");
  Serial.println(TCCR2A, HEX);
  Serial.print("TCCR2B: ");
  Serial.println(TCCR2B, HEX);
  Serial.print("TIMSK2: ");
  Serial.println(TIMSK2, HEX);
  Serial.println("TIMER2 Setup Finished.");
  dmd.setBrightness(255);
  dmd.selectFont(Arial14);
  dmd.begin();
}

// the loop routine runs over and over again forever:
void loop() {
  box.print(' ');
  box.print(counter);
  box.println(F("..."));
  counter--;
  //  delay(1000);
  if (count >= 5)
  {
    flash();
    Serial.println(millis());
    count = 0;
  }

  if (counter == 0) {
    for (int i = 0; i < 3; i++) {
      dmd.fillScreen(true);
      delay(500);
      dmd.clearScreen();
      delay(500);
    }
    box.clear();
    counter = 12;
  }
}


void flash()
{

  static boolean output = HIGH;
  digitalWrite(LED_pin, output);
  output = !output;
}
