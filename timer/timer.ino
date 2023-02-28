//typedef void (*VoidCallBack)(int);
//
//
//
//
//class Timer2 {
//  public:
//    void  init() {
//      cli();
//      TIMSK2 |= (1 << TOIE2);
//      sei();
//      callBacks = (void(**)(int)) malloc(sizeof(VoidCallBack));
//    }
//    void addCallBack(VoidCallBack callBack) {
//      callBacks[0] = callBack;
//    }
//    VoidCallBack *callBacks ;
//};
//Timer2 timer;
//int ledi = 0;
//void setup() {
//  // put your setup code here, to run once:
//  timer.init();
//  DDRB &= 0;
//  timer.addCallBack([](int a) {
//    ledi++;
//  });
//  //  digitalWrite(13, LOW);
//}
//
//ISR(TIMER2_OVF_vect) {
//  //  digitalWrite(13, digitalRead(13) ^ 1);
//  timer.callBacks[0](0);
//}
//byte led = false;
//void loop() {
//  // put your main code here, to run repeatedly:
//  if (ledi > 3000) {
//    PORTB ^= 1 << 5;
//    led = !led;
//    ledi = 0;
//  }
//}



#include <SPI.h>
#include <avr/interrupt.h>

volatile byte scan_row = 0;


ISR(TIMER2_OVF_vect)
{
  // (Deliberately left as digitalWrite to ensure decent latching time)

  // Digital outputs A, B are a 2-bit selector output, set from the scan_row variable (loops over 0-3),
  // that determines which set of interleaved rows we are outputting during this pass.
  // BA 0 (00) = 1,5,9,13
  // BA 1 (01) = 2,6,10,14
  // BA 2 (10) = 3,7,11,15
  // BA 3 (11) = 4,8,12,16
  digitalWrite(9, LOW);
  digitalWrite(6, scan_row & 0x01);
  digitalWrite(7, scan_row & 0x02);
  scan_row = (scan_row + 1) % 4;

  // Output enable pin is either fixed on, or PWMed for a variable brightness display

  digitalWrite(9, HIGH);
}

void setup() {
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0); // CPOL=0, CPHA=0

  SPI.setClockDivider(SPI_CLOCK_DIV4);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  cli();
  TCCR2A = 0; TCCR2B = 0;
  //OCR2A = reload;
  //TCCR2A = 1<<WGM21;
  TCCR2B = (1 << CS22) | (0 << CS21) | (1 << CS20);
  TIMSK2 = (1 << TOIE2);
  sei();

  bool a = 0;
  for (int i = 0; i < 32; i++) {
    SPI.transfer(0x00);
    //    digitalWrite(11, a = !a);
    //    digitalWrite(13, HIGH); // Latch DMD shift register output
    //    digitalWrite(13, LOW);
  }
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH); // Latch DMD shift register output
  digitalWrite(8, LOW);
  Serial.println("deon");
}
void loop() {
  //  delay(1000);
  //  for (int i = 0; i < 32; i++) {
  //        SPI.transfer(scan_row);
  ////    digitalWrite(11, 1);
  ////    digitalWrite(13, HIGH);
  ////    digitalWrite(13, LOW);
  //  }
  //  //  digitalWrite(9, LOW);
  //  digitalWrite(8, HIGH); // Latch DMD shift register output
  //  digitalWrite(8, LOW);
  //  digitalWrite(9, HIGH);

}

//void drawCircle(const DMDFrame& dmd, byte pos, byte radius) {
//  int radiusSqr = radius * radius;
//  for (int x = -radius; x <= radius; x++) {
//    for (int y = -radius; y <= radius; y++) {
//      if (x * x + y * y < radiusSqr ) {
//        dmd.setPixel(pos + x, 10 + y);
//      }
//
//    }
//  }
//}
typedef void (*VoidCallBack)(int);
class Timer2 {
  public:
    void  init() {

      cli();
      //      TCCR2A = 0;
      //      TCCR2B = 0;
      //      TCCR2B |= (1 << CS21);

      TIMSK2 |= (1 << TOIE0);
      sei();
      callBacks = (void(**)(int)) malloc(sizeof(VoidCallBack));
    }
    void addCallBack(VoidCallBack callBack) {
      callBacks[0] = callBack;
    }
    VoidCallBack *callBacks ;
};

///* Helper function to get a URL query tag from a query string of the type param1=val1&param2=val2 */
//esp_err_t httpd_query_key_value(const char *qry_str, const char *key, char *val, size_t val_size)
//{
//    if (qry_str == NULL || key == NULL || val == NULL) {
//        return ESP_ERR_INVALID_ARG;
//    }
//
//    const char   *qry_ptr = qry_str;
//    const size_t  buf_len = val_size;
//
//    while (strlen(qry_ptr)) {
//        /* Search for the '=' character. Else, it would mean
//         * that the parameter is invalid */
//        const char *val_ptr = strchr(qry_ptr, '=');
//        if (!val_ptr) {
//            break;
//        }
//        size_t offset = val_ptr - qry_ptr;
//
//        /* If the key, does not match, continue searching.
//         * Compare lengths first as key from url is not
//         * null terminated (has '=' in the end) */
//        if ((offset != strlen(key)) ||
//            (strncasecmp(qry_ptr, key, offset))) {
//            /* Get the name=val string. Multiple name=value pairs
//             * are separated by '&' */
//            qry_ptr = strchr(val_ptr, '&');
//            if (!qry_ptr) {
//                break;
//            }
//            qry_ptr++;
//            continue;
//        }
//
//        /* Locate start of next query */
//        qry_ptr = strchr(++val_ptr, '&');
//        /* Or this could be the last query, in which
//         * case get to the end of query string */
//        if (!qry_ptr) {
//            qry_ptr = val_ptr + strlen(val_ptr);
//        }
//
//        /* Update value length, including one byte for null */
//        val_size = qry_ptr - val_ptr + 1;
//
//        /* Copy value to the caller's buffer. */
//        strlcpy(val, val_ptr, MIN(val_size, buf_len));
//
//        /* If buffer length is smaller than needed, return truncation error */
//        if (buf_len < val_size) {
//            return ESP_ERR_HTTPD_RESULT_TRUNC;
//        }
//        return ESP_OK;
//    }
//    ESP_LOGD(TAG, LOG_FMT("key %s not found"), key);
//    return ESP_ERR_NOT_FOUND;
//}
