#ifndef _SNAKEGAME_H_
#define _SNAKEGAME_H_

// Done

#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
using std::cout;
using std::endl;
#include <algorithm>
using std::all_of;
using std::fill_n;
#include <vector>
using std::vector;
#include <iterator>
using std::back_inserter;
#include <sstream>
using std::ostringstream;
#include <numeric>
using std::accumulate;
#include <stack>
using std::stack;
#include <queue>
using std::queue;

#include "2.0_level.h"



/**
 * @brief Class that contains the simulator of the snaze game
*/
class SnakeGame {
private:

    /**
     * @brief Enumeration representing different states of the game.
     */
    enum class game_state : uint {
        STARTING = 0,                       //!< Beginning the game.
        PLAYING_MODE,                       //!< Reading user command (Play sub-menu).
        NEW_FOOD,                           //!< Generates the position of the food.
        NEW_PATH,                           //!< Finds the path to be followed.
        SNAKE_DIE,                          //!< Snake has died.
        UPDATE_DIRECTION,                   //!< Updates the matrix with the new snake position.
        RANDOM_DIRECTION,                   //!< Chooses a random direction.
        NEW_LEVEL,                          //!< User wants to start a new game.
        NEW_STATE,
        CONFIRMING_FINISHED_LEVEL,          //!< User has already started a match. Confirmation needed.
        PRINT_DISPLAY,                      //!< Prints the game.
        GAME_OVER,                          //!< Game over state.
        FINISHED_PUZZLE                     //!< User has completed a puzzle.
    };

    /**
     *  @brief Enumeration representing different type players of the game.
    */
    enum class player_type : uint {
        RANDOM = 0,                       //!< player random
        BACKTRACKING                      //!< backtracking player
     
    };


    bool game_over;      //!< Is the game over?
    unsigned short fps;      //!< Numbers of frames per second | Default = 4
    unsigned short lives;    //!< Lives the snake has | Default = 5
    unsigned short food;    //!< Quantity of food pellets for the entire simulation | Default = 10
    player_type m_player_type;
    std::ifstream inputfile;    //!< Name of the level input file
    std::vector<Level> m_levels;  //!< Vector containing the levels of the game


        
public:
    game_state m_game_state;            //!< Represents the current state of the game.
    direction m_direction;              //!< Represents the direction of the snake.
    std::queue<direction> path;         //!< Queue containing the directions to be followed.
    Level level;                        //!< Represents the current level in the game.
    short num_levels;                   //!< Position to access the current level.
    size_t score;                       //!< Represents the player's score.
    size_t snake_size_body;             //!< Represents the size of the snake's body.
    size_t foods;                       //!< Represents the quantity of food eaten by the snake.


    
    /**
     * @brief constructor
    */
    SnakeGame();

    /**
     * @brief Default deconstructor
    */
    ~SnakeGame() = default;
    
    /**
     * @brief Read arguments from CLI, update simulation values and read level that will be played
    */
    void initialize(int argc, char* argv[]);

    /**
     * @brief Function that returns if the game is over or not
    */
    bool is_over();
 
    /**
     * @brief Return starting lives
    */
    unsigned short ret_lives();

    size_t ret_score();


    /**
     * @brief Return starting food amount
    */
    unsigned short ret_food();

    /**
     * @brief Help message
    */
    void help_message();

    /**
     * @brief Introduction message at the start of every game indicating authors, copyright, and in-game
     * values given by arguments via CLI
    */
    void introduction_message();

    /**
     * @brief Outputs the current game data.
     * 
     * This function is responsible for displaying the current state of the game data.
     */
    void data_game();

    /**
     * @brief Displays the game over message.
     * 
     * This function is responsible for displaying the game over message.
     */
    void game_over_display();

    /**
     * @brief Displays an alternative game over message.
     * 
     * This function is an alternative display for the game over message.
     */
    void game_over2_display();

    /**
     * @brief Displays the game win message.
     * 
     * This function is responsible for displaying the game win message.
     */
    void game_win_display();

    /**
     * @brief Displays the "snake" entry message.
     * 
     * This function is responsible for displaying the entry message when starting the game, which says "snake".
     */
    void snake_display();

    /**
     * @brief Tests if the string is convertible to int
    */
    bool aux_is_convert_to_int(const std::string& str);


    /**
     * @brief Takes a string argument indicating the name for the input file and opens it 
    */
    void open_file(const std::string& filename);

    /**
     * @brief Read the information contained in the file
    */    
    void read_file();

    
    /**
     * @brief Processes game events.
     * 
     * This function is responsible for processing game events, such as user input or other events
     * relevant to the game's mechanics.
     */
    void process_events();

    /**
     * @brief Renders the current game state.
     * 
     * This function handles the rendering of the game, displaying the relevant information and graphics
     * based on the current state of the game.
     */
    void render();

    /**
     * @brief Updates the game state.
     * 
     * This function is responsible for updating the game state based on the current conditions,
     * advancing the game logic and progressing to the next frame or state.
     */
    void update();

};

#endif