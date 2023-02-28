#include <IRremote.h>  //including infrared remote header file 
#include <NewPing.h>
#define left_forward 3
#define left_backward 4
#define right_forward 5
#define right_backward 6
#define engine_speed_control 9
#define RECV_PIN 2
#define ECHO_PIN 8
#define TRIG_PIN 9

#define BUTTON_ON 0xBA45FF00
#define BUTTON_0 0xE916FF00
#define BUTTON_1 0xF30CFF00
#define BUTTON_2 0xE718FF00
#define BUTTON_3 0xA15EFF00
#define BUTTON_4 0xF708FF00
#define BUTTON_5 0xE31CFF00
#define BUTTON_6 0xA55AFF00
#define BUTTON_7 0xBD42FF00
#define BUTTON_8 0xAD52FF00
#define BUTTON_9 0xB54AFF00
#define BUTTON_VOL_MINUS 0xEA15FF00
#define BUTTON_VOL_PLUS 0xF609FF00

static bool startEngine = false;
static int engineSpeed = 125;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  for (byte i = 0; i < 4 ; i++) {
    pinMode(3 + i, OUTPUT);
    digitalWrite(3 + i , LOW);
  }
  stop_engine();
  //  analogWrite(engine_speed_control, engineSpeed);

}


void loop() {
  // put your main code here, to run repeatedly:
  ir_function();

}// loop

enum Direction : byte {
  center = 0,
  left = 1,
  right = 2,
  left_1w ,
  right_1w ,
  increase_speed,
  decrease_speed
};

void ir_function() {
  if (IrReceiver.decode()) {
    static Direction perviousDirection = center;
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case BUTTON_ON:
        Serial.println("button on pressed");
        stop_engine();
        perviousDirection = center;
        break;
      case BUTTON_0:
        Serial.println("button 0 pressed");
        break;
      case BUTTON_1:
        Serial.println("button 1 pressed");
        stop_engine();
        perviousDirection = center;
        turn_left_1w();
        perviousDirection = left_1w;
        break;
      case BUTTON_2:
        Serial.println("button 2 pressed");
        move_forward();
        perviousDirection = center;
        break;
      case BUTTON_3:
        Serial.println("button 3 pressed");
        turn_right_1w();
        perviousDirection = right_1w;
        break;
      case BUTTON_4:
        Serial.println("button 4 pressed");
        turn_left();
        perviousDirection = left;
        break;
      case BUTTON_5:
        Serial.println("button 5 pressed");
        stop_engine();
        perviousDirection = center;
        break;
      case BUTTON_6:
        Serial.println("button 6 pressed");
        turn_right();
        perviousDirection = right;
        break;
      case BUTTON_7:
        Serial.println("button 7 pressed");
        break;
      case BUTTON_8:
        Serial.println("button 8 pressed");
        move_backward();
        perviousDirection = center;
        break;
      case BUTTON_9:
        Serial.println("button 9 pressed");
        break;
      case BUTTON_VOL_PLUS:
        Serial.println("button vol + pressed");
        increase_engine_speed();
        perviousDirection = increase_speed;
        break;
      case BUTTON_VOL_MINUS:
        Serial.println("button vol - pressed");
        decrease_engine_speed();
        perviousDirection = decrease_speed;
        break;
      case 0x0:
        switch (perviousDirection) {
          case left:
            turn_left();
            break;
          case right:
            turn_right();
            break;
          case left_1w:
            turn_left_1w();
            break;
          case right_1w:
            turn_right_1w();
            break;
          case increase_speed:
            increase_engine_speed();
            break;
          case decrease_speed:
            decrease_engine_speed();
            break;
        }
        Serial.println("button pressed double");
        break;
      default:
        perviousDirection = center;
        break;
    }
    IrReceiver.resume();
  }

}


void increase_engine_speed() {
  if (engineSpeed + 10 <= 255) {
    engineSpeed += 10;
  }
  else {
    engineSpeed = 255;
  }
  analogWrite(engine_speed_control, engineSpeed);
}

void decrease_engine_speed() {
  if (engineSpeed - 10 >= 125) {
    engineSpeed -= 10;
  }
  else {
    engineSpeed = 125;
  }
  analogWrite(engine_speed_control, engineSpeed);
}


void stop_engine() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
}

void move_forward() {
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

void move_backward() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, HIGH);
}

void turn_left() {
  //  analogWrite(engine_speed_control, 120);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
  delay(100);
  //  analogWrite(engine_speed_control, engineSpeed);
  stop_engine();
}

void turn_left_1w() {
  //  analogWrite(engine_speed_control, 200);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
  delay(100);
  //  analogWrite(engine_speed_control, engineSpeed);
  stop_engine();
}

void turn_right() {
  //  analogWrite(engine_speed_control, 120);
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, HIGH);
  delay(100);
  //  analogWrite(engine_speed_control, engineSpeed);
  stop_engine();
}

void turn_right_1w() {
  //  analogWrite(engine_speed_control, 200);
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
  delay(100);
  //  analogWrite(engine_speed_control, engineSpeed);
  stop_engine();
}
