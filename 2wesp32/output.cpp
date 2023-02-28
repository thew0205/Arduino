
#include "car_control2wd.h"


constexpr char info [2][2] = {"s", "d"};
BluetoothSerial carBle;
//static bool startEngine = false;
static uint8_t engineSpeed = 0;
static volatile uint8_t rightTurnCount = 0;
static volatile uint8_t leftTurnCount = 0;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
uint8_t bleNotificationPrescalar = 5;
bool toggleBleIndicator = false;
uint8_t bleNotificationCount  = 1;


void IRAM_ATTR measureRightTurnsCount()
{
  ++rightTurnCount;
}
void IRAM_ATTR measureLeftTurnsCount()
{
  ++leftTurnCount;
}


void accelerate() {
  uint8_t* engineSpeed_p = &engineSpeed;
  if (*engineSpeed_p < MIN_SPEED) {
    *engineSpeed_p = MIN_SPEED;
  } else if (engineSpeed + 2 < MAX_SPEED) {
    engineSpeed += 2;
  }
  else {
    engineSpeed = MAX_SPEED;
  }

}

void decelerate() {
  uint8_t* engineSpeed_p = &engineSpeed;
  //  Serial.println("default_deceleration");
  if (*engineSpeed_p - 3 >= MIN_SPEED) {
    *engineSpeed_p -= 3;
  }
  else {
    *engineSpeed_p = 0;
  }
}


void default_deceleration() {

  uint8_t* engineSpeed_p = &engineSpeed;
  if (*engineSpeed_p - 1 >= MIN_SPEED) {
    *engineSpeed_p -= 1;
  }
  else {
    *engineSpeed_p = 0;
  }
}

void neutral_direction() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
}

void stop_engine() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
  engineSpeed = 0;
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
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

void turn_left_1w() {
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(right_backward, LOW);
}

void turn_right() {
  digitalWrite(left_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, HIGH);
}

void turn_right_1w() {
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
      Serial.println("button 3 pressed");
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
      engineSpeed = MIN_SPEED + 10;
      break;
    case '9':
      //      Serial.println("button 9 pressed");
      break;
    default:

      break;
  }
}




void sendInfo() {
  char finalInfo[100] = {0};
  sprintf(finalInfo, "s:%u, d:%lu\n\r", ( rightTurnCount + leftTurnCount) / 2, sonar.ping_cm());
  //  sprintf(finalInfo, "sd:%d, sl:%d, sr:%d, s:%d,\r\n", rightTurnCount - leftTurnCount , leftTurnCount , rightTurnCount , engineSpeed);
  carBle.write((unsigned char*)finalInfo, strlen(finalInfo));

  //  Serial.println(finalInfo);
}

void updateTask(TimerHandle_t handle) {
  bleNotificationCount++;
  if (bleNotificationCount % bleNotificationPrescalar == 0) {
    digitalWrite(BLENOTIFICATIONLED, toggleBleIndicator = !toggleBleIndicator);
    bleNotificationCount = 1;
  }
  default_deceleration();
  if (carBle.hasClient() > 0) {
    sendInfo();
    bleNotificationPrescalar = 25;
  }
  else {
    stop_engine();
    bleNotificationPrescalar = 5;
  }
  ledcWrite(RIGHT_SPPEDCONTROL, engineSpeed);
  ledcWrite(LEFT_SPPEDCONTROL, engineSpeed);
  leftTurnCount = 0;
  rightTurnCount = 0;

}

void setupTimer() {
  TimerHandle_t outputTimerHandler = xTimerCreate(
                                       "output timer", UPDATETIME / portTICK_PERIOD_MS, pdTRUE, NULL, updateTask);
  xTimerStart(outputTimerHandler, 0);
}

void bluetoothFunction (const uint8_t *buffer, size_t size) {
  for (int i = 0; i < size ; i++) {
    inputFunction(buffer[i]);
  }
}

void speedMeasureSetup() {

  pinMode(left_speed_measure, INPUT);
  attachInterrupt(left_speed_measure, measureLeftTurnsCount, CHANGE);
  //  for speed measurements
  pinMode(right_speed_measure, INPUT);
  attachInterrupt(right_speed_measure, measureRightTurnsCount, CHANGE);
}

void setupCarControl() {
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);

  //for speed control
  ledcSetup(LEFT_SPPEDCONTROL, FREQUENCY, RESOUTION);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(18, LEFT_SPPEDCONTROL);

  ledcSetup(RIGHT_SPPEDCONTROL, FREQUENCY, RESOUTION);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(19, RIGHT_SPPEDCONTROL);

}
void setupCar() {

  carBle.begin("Switches"); //Bluetooth device name
  carBle.onData(bluetoothFunction);
  pinMode(BLENOTIFICATIONLED, OUTPUT);


  setupTimer();
  speedMeasureSetup();

  setupCarControl();

}
