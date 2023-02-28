#include <DFRobot_DHT11.h>

DFRobot_DHT11 DHT;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read(7);
  DHT.temperature;
  DHT.humidity;
  

}
