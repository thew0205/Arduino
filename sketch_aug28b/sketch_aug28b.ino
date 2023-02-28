
#define left_forward (4)
#define left_backward (5)
#define left_speed_measure (32)
#define right_speed_measure (33)
#define right_forward (22)
#define right_backward (23)
#define engine_speed_control (9)
#define RECV_PIN (2)
#define FREQUENCY (30000)
#define RESOUTION (8)
#define MAX_SPEED (8191)
#define MIN_SPEED (3000)
#define LEFT_SPPEDCONTROL (0)
#define RIGHT_SPPEDCONTROL (1)
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  while (!Serial);

}
bool led = true;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World");
  if (Serial.available()) {
    while (Serial.available()) {
      Serial.read();
    }
    digitalWrite(13, led = !led);
  }
  delay(100);
}
//ledcWrite(RIGHT_SPPEDCONTROL, 210);
//ledcWrite(LEFT_SPPEDCONTROL, 210);
//delay(700);
//
//ledcWrite(RIGHT_SPPEDCONTROL, 00);
//ledcWrite(LEFT_SPPEDCONTROL, 00);
////   delay(2500);
//}
