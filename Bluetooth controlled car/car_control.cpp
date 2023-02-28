#include <TimerOne.h>

#include "car_control2wd.h"

#include <Arduino.h>

#include <NewPing.h>

constexpr char info [2][2] = {"s", "d"};

static volatile uint8_t rightTurnCount = 0;
static volatile uint8_t leftTurnCount = 0;
static volatile bool  canSendData = false;
static uint8_t engineSpeed = 0;

void __attribute__((always_inline))  accelerate() {
  uint8_t* engineSpeed_p = &engineSpeed;
  if (*engineSpeed_p < MIN_SPEED) {
    *engineSpeed_p = MIN_SPEED;
  } else if (engineSpeed + 4 < MAX_SPEED) {
    engineSpeed += 4;
  }
  else {
    engineSpeed = MAX_SPEED;
  }

}

void __attribute__((always_inline))  decelerate() {
  uint8_t* engineSpeed_p = &engineSpeed;
  //  Serial.println("default_deceleration");
  if (*engineSpeed_p - 7 >= MIN_SPEED) {
    *engineSpeed_p -= 7;
  }
  else {
    *engineSpeed_p = 0;
  }
}


void __attribute__((always_inline)) default_deceleration()  {

  uint8_t* engineSpeed_p = &engineSpeed;
  if (*engineSpeed_p - 2 >= MIN_SPEED) {
    *engineSpeed_p -= 2;
  }
  else {
    *engineSpeed_p = 0;
  }
}

void __attribute__((always_inline)) neutral_direction()  {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
}

void  __attribute__((always_inline)) stop_engine()  {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
  engineSpeed = 0;
}


void __attribute__((always_inline))  move_forward() {
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

void __attribute__((always_inline))  move_backward() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, HIGH);
}
bool isTurning = false;
void __attribute__((always_inline))  turn_left() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

void __attribute__((always_inline))  turn_left_1w() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

void  __attribute__((always_inline)) turn_right() {
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, HIGH);
}

void __attribute__((always_inline)) turn_right_1w()  {
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
}

void inputFunction(char input) {
  switch (input) {
    case '0':
      //      Serial.println("button on pressed");
      neutral_direction();
      break;
    case '1':
      //      Serial.println("button 1 pressed");
      move_forward();
      break;
    case '2':
//      Serial.println("button 2 pressed");
      turn_right();
      break;
    case '3':
      //      Serial.println("button 3 pressed");
      move_backward();
      break;
    case '4':
      //      Serial.println("button 4 pressed");
      turn_left();
      break;
    case '5':
      //      Serial.println("button 5 pressed");
      accelerate();
      break;
    case '6':
      //      Serial.println("button 6 pressed");
      decelerate();
      break;
    case '7':
//      Serial.println("button 7 pressed");
      stop_engine();
      break;
    case '8':
      //      Serial.println("button 8 pressed");
      engineSpeed = MIN_SPEED + 40;
      break;
    case '9':
      //      Serial.println("button 9 pressed");
      break;
    default:

      break;
  }
}

void sendInfo() {
  canSendData = true;
  default_deceleration();
  analogWrite(RIGHT_SPPEDCONTROL, engineSpeed);
  analogWrite(LEFT_SPPEDCONTROL, engineSpeed);
}

void  measureRightTurnsCount()
{
  ++rightTurnCount;
}
void  measureLeftTurnsCount()
{
  ++leftTurnCount;
}


void speedMeasureSetup() {

  pinMode(left_speed_measure, INPUT);
  attachInterrupt(digitalPinToInterrupt(left_speed_measure), measureLeftTurnsCount, CHANGE);
  //  for speed measurements
  pinMode(right_speed_measure, INPUT);
  attachInterrupt(digitalPinToInterrupt(right_speed_measure), measureRightTurnsCount, CHANGE);
}


void setupCarControl() {
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);

  //for speed control
  pinMode(LEFT_SPPEDCONTROL, OUTPUT);
  pinMode(RIGHT_SPPEDCONTROL, OUTPUT);
  analogWrite(RIGHT_SPPEDCONTROL, 0);
  analogWrite(LEFT_SPPEDCONTROL, 0);
}

void setupCar() {

  Serial.begin(9600); //Bluetooth device name
  NewPing sonar(TRIGGER_PIN, ECHO_PIN, 500);




  char  finalInfo[50] = {0};
  Timer1.initialize(100000);
  Timer1.attachInterrupt(sendInfo);


  speedMeasureSetup();

  setupCarControl();
  move_forward();
  for (;;) {
    if (Serial.available()) {
      inputFunction(Serial.read());
    }
    unsigned long obstacleDisatance = sonar.ping_cm();
    if (canSendData) {
      noInterrupts();
      sprintf(finalInfo, "s:%u, d:%lu\n\r", ( rightTurnCount + leftTurnCount) / 2, obstacleDisatance);
      rightTurnCount  = leftTurnCount = 0;
      canSendData = false;
      interrupts();
      Serial.println(finalInfo);

    }
  }

}
