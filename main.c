

#include <stdint.h>
int32_t a12 = 4;
volatile uint8_t a1 = 7;

const int a3 = 8;
static void delay(volatile int32_t time) __attribute__((section("vector")));
int main() {
  //   volatile int a2 = 7;
  *((uint8_t *)(0x24)) |= 1 << 5;

  while (1) {
    *((uint8_t *)(0x25)) ^= (1 << 5);
    delay((int)0xff00);
  }
}

static void delay(volatile int32_t time) {
  while (time > a12) {
    time -= 255;
  }
}