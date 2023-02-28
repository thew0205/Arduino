void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, INPUT);

}
bool state = false;
int i = 0;
long int preTime = 0;
void loop() {
  char buf[100];

  // put your main code here, to run repeatedly:
  //  Serial.print(digitalRead(11));
  if (digitalRead(11) != state) {
    state = digitalRead(11);
    if (HIGH == state) {
      preTime = millis();
     
    }
    else {
      //      sprintf(buf, "end: %d start: %d : difference: %d", millis(), 5, miltlis() -  difference: );
      i++;
      Serial.print("No: ");
      Serial.print( i);
      Serial.print(" end: ");
      Serial.print(millis());
      Serial.print(" start: ");
      Serial.print(preTime);
      Serial.print(" difference: ");
      Serial.println( millis() -  preTime);
    }
  }
}
