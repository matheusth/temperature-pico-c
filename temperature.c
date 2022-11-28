#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/time.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define GPIO_BLUE 5
#define GPIO_GREEN 6
#define GPIO_RED 7

int main(void){
    stdio_init_all();
    
    //Led pins setup
    gpio_init(GPIO_BLUE);
    gpio_init(GPIO_GREEN);
    gpio_init(GPIO_RED);
    gpio_set_dir(GPIO_BLUE, GPIO_OUT);
    gpio_set_dir(GPIO_GREEN, GPIO_OUT);
    gpio_set_dir(GPIO_RED, GPIO_OUT);


    //setup adc
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    while(1){
        uint16_t raw = adc_read();
        const float conversion = 3.3f / (1<<12);
        float voltage = raw * conversion;

        float temp = 27 - (voltage - 0.706)/0.001721;
        printf("temperature: %f ºC\n", temp);
        if(temp < 18.f){
            gpio_put(GPIO_BLUE, GPIO_ON);
            gpio_put(GPIO_GREEN, GPIO_OFF);
            gpio_put(GPIO_RED, GPIO_OFF);
        }else if(temp >= 18.f && temp < 23.f){
            gpio_put(GPIO_BLUE, GPIO_OFF);
            gpio_put(GPIO_GREEN, GPIO_ON);
            gpio_put(GPIO_RED, GPIO_OFF);
        }else{
            gpio_put(GPIO_BLUE, GPIO_OFF);
            gpio_put(GPIO_GREEN, GPIO_OFF);
            gpio_put(GPIO_RED, GPIO_ON);
        }
        sleep_ms(1000);
    }
}
