#define pin_noe GPIO_NUM_22
#define pin_b GPIO_NUM_21
#define pin_a GPIO_NUM_19
#define pin_sck GPIO_NUM_2
#define pin_clk GPIO_NUM_18
#define pin_r_data GPIO_NUM_23


uint8_t by = 0;
uint8_t scan_row = 0;
void outputTasks(TimerHandle_t handle) {
  for (int i = 0; i < 128; i++) {
    //    SPI.transfer(0xaa);
    //    SPI.transfer(0xaa);
    //    SPI.transfer(0xaa);
    //    SPI.transfer(0xaa);
    gpio_set_level(pin_r_data, 0);
    by = !by;
    gpio_set_level(pin_clk, 1);
    gpio_set_level(pin_clk, 0);
  }

  gpio_set_level(pin_noe, 0);
  gpio_set_level(pin_sck, 1); // Latch DMD shift register output
  gpio_set_level(pin_sck, 0);  // (Deliberately left as gpio_set_level to ensure
  // decent latching time)
  gpio_set_level(pin_a, scan_row & 0x01);
  gpio_set_level(pin_b, scan_row & 0x02);
  scan_row = (scan_row + 1) % 4;
  gpio_set_level(pin_noe, 1);
  // char pri[SUPPORTED_DEVICES + 1] = {'\0'};

  // ShiftRegisterOutput595::instance.write(output);
  // printBinary(LOGTAG_OUTPUT, output, pri);
  // ESP_LOGI(LOGTAG_OUTPUT, "the binary is: %s", pri);
}


void setup() {
  // p
  gpio_pad_select_gpio(pin_noe);
  ESP_ERROR_CHECK(gpio_set_direction(pin_noe, GPIO_MODE_OUTPUT));
  ESP_ERROR_CHECK(gpio_set_level(pin_noe, 0));
  gpio_pad_select_gpio(pin_b);
  ESP_ERROR_CHECK(gpio_set_direction(pin_b, GPIO_MODE_OUTPUT));
  ESP_ERROR_CHECK(gpio_set_level(pin_b, 0));
  gpio_pad_select_gpio(pin_a);
  ESP_ERROR_CHECK(gpio_set_direction(pin_a, GPIO_MODE_OUTPUT));
  ESP_ERROR_CHECK(gpio_set_level(pin_a, 0));
  gpio_pad_select_gpio(pin_sck);
  ESP_ERROR_CHECK(gpio_set_direction(pin_sck, GPIO_MODE_OUTPUT));
  ESP_ERROR_CHECK(gpio_set_level(pin_sck, 0));
  gpio_pad_select_gpio(pin_r_data);
  ESP_ERROR_CHECK(gpio_set_direction(pin_r_data, GPIO_MODE_OUTPUT));
  ESP_ERROR_CHECK(gpio_set_level(pin_r_data, 0));
  gpio_pad_select_gpio(pin_clk);
  ESP_ERROR_CHECK(gpio_set_direction(pin_clk, GPIO_MODE_OUTPUT));
  ESP_ERROR_CHECK(gpio_set_level(pin_clk, 0));
  //ut your setup code here, to run once:
  auto outputTimerHandler = xTimerCreate(
                              "output timer", 2 / portTICK_PERIOD_MS, pdTRUE, NULL, outputTasks);
  xTimerStart(outputTimerHandler, 0);


}

void loop() {
  // put your main code here, to run repeatedly:

}
