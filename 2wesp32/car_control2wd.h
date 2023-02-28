#include <Arduino.h>

#include <NewPing.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

#include "BluetoothSerial.h"

#define BLENOTIFICATIONLED (2)
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
#define MAX_SPEED (200)
#define MIN_SPEED (170)
#define LEFT_SPPEDCONTROL (0)
#define RIGHT_SPPEDCONTROL (1)

#define TRIGGER_PIN  (26)  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     (27)  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE (500) // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define UPDATETIME (100)


void setupCar();
