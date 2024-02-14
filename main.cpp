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
#include "textRenderer/TextRenderer.h"
#include <cstdio>

int main()
{
    EventQueue event_queue;
    pico_ssd1306::SSD1306 display = initialise_display();
    setup_buttons(&event_queue);

    int counter = 0;

    // main program loop
    while (1)
    {
        display.clear();

        // process events from queue
        Event event = event_queue.get_event();

        switch (event.type)
        {
            case BUTTON_PRESS:
                counter += 1;
        }

        // display on screen
        char test_display[] = "Snake Test";
        pico_ssd1306::drawText(&display, font_12x16, test_display, 0, 0);

        char counter_txt[4];
        sprintf(counter_txt, "%d", counter);
        pico_ssd1306::drawText(&display, font_16x32, counter_txt, 0, 17);

        display.sendBuffer();
        sleep_ms(10);
    }
}