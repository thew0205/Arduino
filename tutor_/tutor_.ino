void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

}

int delay_time = 0;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(delay_time);
  digitalWrite(13, LOW);
  delay(delay_time);
  delay_time = delay_time +1;

}
