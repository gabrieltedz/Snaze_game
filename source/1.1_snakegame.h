#ifndef _SNAKEGAME_H_
#define _SNAKEGAME_H_

#include "2.0_level.h"
/**
 * @brief Class that contains the simulator of the snaze game
*/
class SnakeGame {
private:

    bool game_over{false};      //!< Is the game over?
    unsigned short fps{4};      //!< Numbers of frames per second | Default = 4
    unsigned short lives{5};    //!< Lives the snake has | Default = 5
    unsigned short food{10};    //!< Quantity of food pellets for the entire simulation | Default = 10

    std::ifstream inputfile;    //!< Name of the level input file
    std::vector<Level> m_levels;
    
public:
    
    SnakeGame() = default;

    /**
     * @brief Default constructor
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
     * @brief Takes a string argument indicating the name for the input file and opens it 
    */
    void open_file(const std::string& filename);

    /**
     * @brief Read the information contained in the file
    */    
    void read_file();

    void process_events();
    void render();
    void update();
};

#endif