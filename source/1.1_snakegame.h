#ifndef _SNAKEGAME_H_
#define _SNAKEGAME_H_


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

    enum class game_state : uint {
        STARTING,  //!< Beginning the game.
        //====================================================
        PLAYING_MODE,  //!< Reading user command (Play sub-menu).
        //----------------------------------------------------
        NEW_PATH,             //!< encontrar o caminho a ser seguido.
        UPDATE_DIRECTION,        //!< Atualiza a matriz com a nova posiçãod da cobra.
        NEW_LEVEL,        //!< User wants to start a new game.
        CONFIRMING_FINISHED_LEVEL,  //!< User has already started a match. We need
                                    //!< to confime s/he wants to bail out.
        PRINT_DISPLAY,              //!< imprime o jogo. 

        // ====================================================
        GAME_OVER,
        FINISHED_PUZZLE  //!< User has completed a puzzle.
    };
    bool game_over;      //!< Is the game over?
    unsigned short fps;      //!< Numbers of frames per second | Default = 4
    unsigned short lives;    //!< Lives the snake has | Default = 5
    unsigned short food;    //!< Quantity of food pellets for the entire simulation | Default = 10

    std::ifstream inputfile;    //!< Name of the level input file
    std::vector<Level> m_levels;

    
public:

    game_state m_game_state; ///ESTADOS DO GAME 
    std::queue<char> path;  //fila com as direções a ser seguida 
    //podemos colocar um enum com as direções

    char* appleEmoji = u8"\U0001F34E";
    
    /**
     * @brief Default constructor
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