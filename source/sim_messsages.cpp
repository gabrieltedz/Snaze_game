#include "simulation.h"

/**
 * @brief Help message
*/
void SnazeSimulation::help_message(){
    std::cout << "$ ./build/snaze " << std::endl;
    std::cout << "Usage: snaze [<options>] <input_level_file>" << std::endl;
    std::cout << "      Game simulation options:" << std::endl;
    std::cout << "          --help              Print this help text." << std::endl;
    std::cout << "          --fps <num>         Number of frames (board) presented per second. Default = 4" << std::endl;
    std::cout << "          --lives <num>       Number of iles the snake shall have. Default = 5." << std::endl;
    std::cout << "          --food <num>        Number of food pellets for the entire simulation. Default = 10." << std::endl;
    std::cout << "          --playertype <type> Type of snake intelligence: random, backtracking. Default = backtracking" << std::endl;
}

/**
 * @brief Introduction message at the start of every game indicating authors, copyright, and in-game
 * values given by arguments via CLI
*/
void SnazeSimulation::introduction_message(){
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "       ===> Welcome to the classic Snake Game! <===" << std::endl;
    std::cout << "             copyright DIMAp / UFRN 2023" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << " Levels loaded: 0 | Snake lives: " << ret_lives() << " | Apples to eat: " << ret_food() << std::endl;
    std::cout << " Clear all levels to win the game. Good luck!!" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << ">>> Press <ENTER> to start the game!" << std::endl;
    std::cout << std::endl;
    std::cout << "Lives: " << ret_lives() << " | Score: 0       | Food eaten: 0 out of 10" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;

}