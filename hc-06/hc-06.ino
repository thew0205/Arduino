//#include <SoftwareSerial.h>
//SoftwareSerial hc06(2, 3);

void setup() {
  //Initialize Serial Monitor
  Serial.begin(9600);
  // scan
  //  hc06.begin(9600);
  //  hc06.print("AT");
  //  String result;
  //  unsigned long startTime = millis();
  //  while (millis() - startTime < 2000) {
  //    if (hc06.available()) {
  //      char c = hc06.read();
  //      Serial.write(c);
  //      result += c;  // append to the result string
  //    }
  //  }
  //    hc06.print("AT+NAMESwitches Display");
  //    scanBaudrate();
}

void loop() {
  String result;
  unsigned long startTime = millis();
  if (millis() - startTime > 2000) {

    Serial.println(startTime);
    startTime = millis();
  }
  if (Serial.available()) {
    Serial.println(Serial.read());
  }
  //hc06.print("s: 20, d: 500");
}
//
//void scanBaudrate() {
//  unsigned long bauds[12] = {300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 74880, 115200, 230400, 250000};
//  for (int i = 0; i < 12; i++) {
//
//    //    delay(10);
//    Serial.print(F("Baudrate "));
//    Serial.println(bauds[i]);
//    //    command("AT", 2000);
//    hc06.print("AT");
//    String result;
//    unsigned long startTime = millis();
//    while (millis() - startTime < 2000) {
//      if (hc06.available()) {
//        char c = hc06.read();
//        Serial.write(c);
//        result += c;  // append to the result string
//      }
//    }
//
//  }
//}
//String command(const char *toSend, unsigned long milliseconds) {
//  String result;
//  Serial.print("Sending: ");
//  Serial.println(toSend);
////  hc06.print(toSend);
//  unsigned long startTime = millis();
//  Serial.print(F("Received: "));
//  while (millis() - startTime < milliseconds) {
//    if (hc06.available()) {
//      char c = hc06.read();
//      Serial.write(c);
//      result += c;  // append to the result string
//    }
//  }
//  Serial.println();  // new line after timeout.
//  return result;
//}
