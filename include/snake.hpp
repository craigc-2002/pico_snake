/* pico_snake
 * Craig Cochrane, 2024
 *
 * snake.hpp
 *
 * Implement a Snake game class
 */

#include "ssd1306.h"
#include "event_queue.hpp"

class Snake
{
    public:
        Snake(void);

        void process_inputs(EventQueue* event_queue);
        void update(void);
        void draw(pico_ssd1306::SSD1306* display);

    private:
        void start_game(void);
        void place_food(void);
        void add_body_length(void);
        int8_t random_direction(void);        

        enum GameState
        {
            PRE_GAME,
            IN_GAME,
            GAME_OVER
        };
        GameState state = PRE_GAME;

        int head_x;
        int head_y;

        int direction_x;
        int direction_y;

        int food_x;
        int food_y;

        struct Body
        {
            int x;
            int y;
        };
        Body body[128];
        int snake_body_length;
};
