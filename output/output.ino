void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  for (int i = 0; i < 10; i++) {

    digitalWrite(13, LOW);

    //    delay(20);
    digitalWrite(2, HIGH);

    digitalWrite(2, LOW);

  }

  digitalWrite(4, HIGH);
  Serial.print(4);
  delay(5000);
  digitalWrite(4, LOW);

  byte b[8] = {1, 0, 1, 1, 1, 0, 0, 1 };
  //    put your main code here, to run repeatedly:
  if (1) {
    for (int i = 0; i < 8; i++) {
      //      Serial.println("Stage 1");

      digitalWrite(13, ( b[i]) );
      Serial.print(13);
      //      delay(3000);
      digitalWrite(2, HIGH);
      //      delay(3000);
      digitalWrite(2, LOW);
      //      delay(3000);
      digitalWrite(4, HIGH);
      Serial.print(4);
//      delay(3000);
      digitalWrite(4, LOW);
//      delay(3000);
    }
  }

  //  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  bool input;
  //  input = (Serial.read() == '0');
  //  if (input) {
  //    while (Serial.read() != '\n');
  //
  //    Serial.println("pt");
  //    digitalWrite(13, HIGH);
  //    digitalWrite(13, LOW);
  //  }

}
