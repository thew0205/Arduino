#include <IRremote.h>  //including infrared remote header file     
constexpr int RECV_PIN = 2; // the pin where you connect the output pin of IR sensor
;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  IrReceiver.begin(RECV_PIN,ENABLE_LED_FEEDBACK);
  //irrecv.enableLEDFeedback(true);

}int i =0;

void loop() {
  // put your main code here, to run repeatedly:
   if (IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    Serial.println(IrReceiver.decodedIRData.decodedRawData,HEX);
    Serial.println(++i);
    IrReceiver.resume();
   }

}
//F30CFF00
//0
//E718FF00
//A15EFF00
//0
//F708FF00
//0
//E31CFF00
//A55AFF00
//0
//BD42FF00
//0
//AD52FF00
//0
//B54AFF00
//0
//E916FF00
//0
