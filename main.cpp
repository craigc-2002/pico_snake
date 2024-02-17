/* pico_snake
 * Craig Cochrane, 2024
 *
 * main.cpp
 *
 * Clone of Snake on Raspberry Pi Pico using my pico alarm clock hardware
 */

#include "pico/stdlib.h"
#include "event_queue.hpp"
#include "buttons.hpp"
#include "display.hpp"
#include "hardware/gpio.h"

#include "snake.hpp"

int main()
{
    EventQueue event_queue;
    pico_ssd1306::SSD1306 display = initialise_display();
    setup_buttons(&event_queue);

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    Snake snake;

    // main program loop
    while (1)
    {
        display.clear();
        
        snake.process_inputs(&event_queue);
        snake.update();
        snake.draw(&display);

        display.sendBuffer();
        sleep_ms(100);
    }
}