/* pico_snake
 * Craig Cochrane, 2024
 *
 * snake.cpp
 *
 * Implement a Snake game class
 */

#include "snake.hpp"

#include "pico/rand.h"
#include "event_queue.hpp"
#include "buttons.hpp"
#include "textRenderer/TextRenderer.h"
#include "hardware/gpio.h"

Snake::Snake()
{
    head_x = 0;
    head_y = 0;

    direction_x = 1;
    direction_y = 0;
}

void Snake::process_inputs(EventQueue* event_queue)
{
    Event event = event_queue->get_event();
    while (event.type != NONE)
    {
        if (event.type == BUTTON_PRESS | event.type == BUTTON_LONG_PRESS | event.type == BUTTON_HOLD)
        {
            if (state == PRE_GAME || state == GAME_OVER)
            {
                state = IN_GAME;
                start_game();
            }

            Button* button = static_cast<Button*>(event.event_data);
            switch (button->num)
            {
                case 1:
                    direction_x = -1;
                    direction_y = 0;
                    break;
                case 2:
                    direction_x = 0;
                    direction_y = -1;
                    break;
                case 3:
                    direction_x = 0;
                    direction_y = 1;
                    break;
                case 4:
                    direction_x = 1;
                    direction_y = 0;
                    break;
            }
        }
        event = event_queue->get_event();
    }
}

void Snake::update(void)
{
    if (state == IN_GAME)
    {
        // check for collision with edge of screen
        if (head_x < 0 || head_x > 128 || head_y < 0 || head_y > 64)
        {
            state = GAME_OVER;
        }

        if (head_x == food_x && head_y == food_y)
        {
            place_food();
            snake_body_length += 1;
        }

        // update body position
        for (int i = (snake_body_length-1); i > 0; i--)
        {
            body[i].x = body[i-1].x;
            body[i].y = body[i-1].y;
        }
        body[0].x = head_x;
        body[0].y = head_y;

        head_x += direction_x;
        head_y += direction_y;

        // check for collision with head and body
        for (int i = 0; i < snake_body_length; i++)
        {
            if (head_x == body[i].x && head_y == body[i].y)
            {
                state = GAME_OVER;
            }
        }
    }
    
}

void Snake::draw(pico_ssd1306::SSD1306* display)
{
    switch (state)
    {
        case PRE_GAME:
            pico_ssd1306::drawText(display, font_16x32, "SNAKE", 24, 0);
            pico_ssd1306::drawText(display, font_8x8, "PRESS ANY", 28, 40);
            pico_ssd1306::drawText(display, font_8x8, "BUTTON TO START", 4, 48);
            break;

        case IN_GAME:
            display->setPixel(head_x, head_y);

            for (int i=0; i < snake_body_length; i++)
            {
                display->setPixel(body[i].x, body[i].y);    
            }

            display->setPixel(food_x, food_y);
            break;

        case GAME_OVER:
            pico_ssd1306::drawText(display, font_16x32, "GAME", 32, 0);
            pico_ssd1306::drawText(display, font_16x32, "OVER", 32, 33);
            break;
    }
}

void Snake::start_game(void)
{
    // set the player to a random point on screen
    head_x = get_rand_32() % 128;
    head_y = get_rand_32() % 64;
    snake_body_length = 0;

    place_food();
}

void Snake::place_food(void)
{
    // set the player to a random point on screen
    food_x = get_rand_32() % 128;
    food_y = get_rand_32() % 64;
}

void Snake::add_body_length(void)
{
    snake_body_length += 1;
}

int8_t Snake::random_direction(void)
{
    /* Generate a random number between -1 and 1 (inclusive) to be used as a random direction */
    return (int8_t) ((get_rand_32() % 3) - 1);
}
