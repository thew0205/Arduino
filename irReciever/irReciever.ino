/*
   IR read codes
   by Hanie kiani
   https://electropeak.com/learn/
*/
#include <IRremote.h>  //including infrared remote header file     
constexpr int RECV_PIN = 7; // the pin where you connect the output pin of IR sensor
IRrecv irrecv(RECV_PIN);
decode_results results;
long int tim = 0;
bool isFirst = true;
int count = 0;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}
void loop()
{
  if (irrecv.decode(&results))// Returns 0 if no data ready, 1 if data ready.

  { if (isFirst) {
      tim = millis();
      isFirst = false;
      count = 1;
    }
    else {
      ++count;
    }

    //Results of decoding are stored in result.value
    Serial.println(" ");
    Serial.print("Code: ");
    Serial.println(results.value); //prints the value a a button press
    Serial.println(" ");

    irrecv.resume(); // Restart the ISR state machine and Receive the next value
  }
  if (!isFirst && millis() - tim >= 1000) {
      Serial.println(count);
      isFirst = true;
    }
}
