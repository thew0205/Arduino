

#define BLENOTIFICATIONLED (2)
#define left_forward (10)
#define left_backward (9)
#define left_speed_measure (2)
#define right_speed_measure (3)
#define right_forward (8)
#define right_backward (7)
#define engine_speed_control (9)
#define RECV_PIN (2)
#define FREQUENCY (30000)
#define RESOUTION (8)
#define MAX_SPEED (255)
#define MIN_SPEED (150)
#define LEFT_SPPEDCONTROL (5)
#define RIGHT_SPPEDCONTROL (6)

#define TRIGGER_PIN  (11)  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     (12)  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE (500) // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define UPDATETIME (100)


void setupCar();
