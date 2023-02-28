void setup() {
  Serial.begin(9600);
  //  pinMode(10, INPUT);
  // put your setup code here, to run once:
  //Enabling to SPI pheriperial clock, there is no need for this cause it reset value is 0
  PRR &= ~(1 << PRSPI);
  //setting MISO as output
  DDRB |= (1 << DDB5);
  //setting ss as input
  DDRB &= (1 << DDB3);
  //configuring spi
  //Enable interrupt
  //Enable SPI pheripheral
  SPCR |= ((1 << SPIE) | (1 << SPE));

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("SPDR: ");
    Serial.println(SPDR);
//    delay(1000);
  cli();
  for (volatile unsigned int i = 1; i < 100; i++) {
    Serial.print("done: ");
    Serial.println(i);
    delay(5000);
  }
  
  sei();
}
