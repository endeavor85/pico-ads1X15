#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#include "ads1X15.h"

int main(int argc, char **argv) {
  // turn on board LED
  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  gpio_put(PICO_DEFAULT_LED_PIN, 1);

  stdio_init_all();

  // delay before printf (otherwise it likely won't print)
  sleep_ms(500);

  // SETUP

  // Use this for the 16-bit version
  // ADS1115 ads(PICO_DEFAULT_I2C_INSTANCE, ADS1X15_ADDRESS, PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN);

  // Use this for the 12-bit version
  ADS1015 ads(PICO_DEFAULT_I2C_INSTANCE, ADS1X15_ADDRESS, PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN);

  printf("Hello!\n");

  printf("Single-ended readings from AIN0 with >3.0V comparator\n");
  printf("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)\n");
  printf("Comparator Threshold: 1000 (3.000V)\n");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  ads.begin();

  // Setup 3V comparator on channel 0
  ads.startComparator_SingleEnded(0, 1000);

  // LOOP

  while(true) {
    int16_t adc0;

    // Comparator will only de-assert after a read
    adc0 = ads.getLastConversionResults();
    printf("AIN0: %d\n", adc0);

    sleep_ms(100);
  }
}
