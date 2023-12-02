#include "1.1_snakegame.h"

// Done

/**
 * @brief Help message
*/
void SnakeGame::help_message() {
    std::cout << "Usage: ./build/snaze" << std::endl;
    std::cout << "Usage: snaze [<options>] <input_level_file>" << std::endl;
    std::cout << "      Game simulation options:" << std::endl;
    std::cout << "          --help              Print this help text." << std::endl;
    std::cout << "          --fps <num>         Number of frames (boards) presented per second. Default = 4, and the maximum FPS is 100." << std::endl;
    std::cout << "          --lives <num>       Number of lives the snake shall have. Default = 5, and the maximum lives = 20." << std::endl;
    std::cout << "          --food <num>        Number of food pellets for the entire simulation. Default = 10, and the maximum number of foods = 50." << std::endl;
    std::cout << "          --playertype <type> Type of snake intelligence: random, backtracking. Default = backtracking." << std::endl;
}


/** 
 * @brief Introduction message at the start of every game indicating authors, copyright, and in-game
 * values given by arguments via CLI
 * 
 * This message indicates authors, copyright, and in-game values given by arguments via CLI.
 */
void SnakeGame::introduction_message() {
    snake_display();
    std::cout << Color::tcolor("-----------------------------------------------------------", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
    std::cout << Color::tcolor("       ===> Welcome to the classic Snake Game! <===", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
    std::cout << Color::tcolor("             copyright DIMAp / UFRN 2023", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
    std::cout << Color::tcolor("-----------------------------------------------------------", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
    std::cout <<  Color::tcolor(" Levels loaded: ", Color::BRIGHT_WHITE, Color::BOLD) << Color::tcolor( std::to_string(m_levels.size()), Color::BRIGHT_WHITE, Color::BOLD);
    std::cout <<  Color::tcolor(" | Snake lives: ", Color::BRIGHT_WHITE, Color::BOLD) << Color::tcolor( std::to_string(ret_lives()), Color::BRIGHT_WHITE, Color::BOLD);
    std::cout <<  Color::tcolor(" | Apples to eat: ", Color::BRIGHT_WHITE, Color::BOLD) << Color::tcolor( std::to_string(ret_food()), Color::BRIGHT_WHITE, Color::BOLD)  << std::endl;
    std::cout <<  Color::tcolor(  " Clear all levels to win the game. Good luck!!", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
    std::cout << Color::tcolor("-----------------------------------------------------------", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
    std::cout << Color::tcolor(">>> Press <ENTER> to start the game!", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
    std::cout << std::endl;

    std::cout << Color::tcolor("Lives: ", Color::BRIGHT_WHITE, Color::BOLD);
    for (size_t i = 0; i < ret_lives(); i++){std::cout << Color::tcolor("❤️", Color::BRIGHT_RED);}

    std::cout << Color::tcolor(" | Score: ", Color::BRIGHT_WHITE, Color::BOLD)  << Color::tcolor(std::to_string(ret_score()), Color::BRIGHT_WHITE, Color::BOLD);
    std::cout << Color::tcolor(" | Food eaten: ", Color::BRIGHT_WHITE, Color::BOLD)  << Color::tcolor(std::to_string(foods), Color::BRIGHT_WHITE, Color::BOLD);
    std::cout << Color::tcolor(" out of ", Color::BRIGHT_WHITE, Color::BOLD)  << Color::tcolor(std::to_string(ret_food()), Color::BRIGHT_WHITE, Color::BOLD) << std::endl;

    std::cout << Color::tcolor("-----------------------------------------------------------", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;
}


/**
 * @brief Displays the current game data.
 * 
 * This function is responsible for displaying the current state of the game data.
 */
void SnakeGame::data_game(){
    std::cout << Color::tcolor("\n\nLives: ", Color::BRIGHT_WHITE, Color::BOLD);
    for (size_t i = 0; i < ret_lives(); i++){std::cout << Color::tcolor("❤️", Color::BRIGHT_RED);}
     

    std::cout << Color::tcolor(" | Score: ", Color::BRIGHT_WHITE, Color::BOLD)  << Color::tcolor(std::to_string(ret_score()), Color::BRIGHT_WHITE, Color::BOLD);
    std::cout << Color::tcolor(" | Food eaten: ", Color::BRIGHT_WHITE, Color::BOLD)  << Color::tcolor(std::to_string(foods), Color::BRIGHT_WHITE, Color::BOLD);
    std::cout << Color::tcolor(" out of ", Color::BRIGHT_WHITE, Color::BOLD)  << Color::tcolor(std::to_string(ret_food()), Color::BRIGHT_WHITE, Color::BOLD) << std::endl;


    std::cout << Color::tcolor("-----------------------------------------------------------", Color::BRIGHT_WHITE, Color::BOLD) << std::endl;

}


/**
 * @brief Displays the game over message.
 * 
 * This function is responsible for displaying the game over message.
 */
void SnakeGame::game_over_display() {
    std::cout << std::endl << std::endl;
    std::cout << Color::tcolor("  ███   ███  █     █ █████     ███  █   █ █████ ████   ", Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor(" █     █   █ ██   ██ █        █   █ █   █ █     █   █  ", Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor(" █  ██ █████ █ █ █ █ ████     █   █ █   █ ████  ████   ", Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor(" █   █ █   █ █  █  █ █        █   █  █ █  █     █  ██  " , Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor("  ███  █   █ █     █ █████     ███    █   █████ █   ██ ", Color::BRIGHT_RED) << std::endl;
}

/**
 * @brief Displays an alternative game over message.
 * 
 * This function is an alternative display for the game over message.
 */
void SnakeGame::game_over2_display() {
    std::cout << std::endl << std::endl;
    std::cout << Color::tcolor(" █   █  ███  █   █    █      ███   ████ █████ ", Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor("  █ █  █   █ █   █    █     █   █ █     █     ", Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor("   █   █   █ █   █    █     █   █  ███  ████  ", Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor("   █   █   █ █   █    █     █   █     █ █     ", Color::BRIGHT_RED) << std::endl;
    std::cout << Color::tcolor("   █    ███   ███      ████  ███  ████  █████ ", Color::BRIGHT_RED) << std::endl;
}

/**
 * @brief Displays the game win message.
 * 
 * This function is responsible for displaying the game win message.
 */
void SnakeGame::game_win_display() {
    std::cout << std::endl << std::endl;
    std::cout << Color::tcolor("        █   █  ███  █   █    █ █ █ █  ██  █ ", Color::BRIGHT_GREEN) << std::endl;
    std::cout << Color::tcolor("         █ █  █   █ █   █    █ █ █    █ █ █ ", Color::BRIGHT_GREEN) << std::endl;
    std::cout << Color::tcolor("          █   █   █ █   █    █ █ █ █  █ █ █ ", Color::BRIGHT_GREEN) << std::endl;
    std::cout << Color::tcolor("          █   █   █ █   █    █ █ █ █  █ █ █ ", Color::BRIGHT_GREEN) << std::endl;
    std::cout << Color::tcolor("          █    ███   ███      ███  █  █ ███ ", Color::BRIGHT_GREEN) << std::endl;
}


/**
 * @brief Displays a "snake" entry message.
 * 
 * This function is responsible for displaying the entry message when starting the game, which says "snake".
 */
void SnakeGame::snake_display() {
    std::cout << std::endl << std::endl;
    std::cout << Color::tcolor("        ●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●", Color::BRIGHT_YELLOW) << std::endl;
    std::cout << Color::tcolor("        ●", Color::BRIGHT_YELLOW) << Color::tcolor("  ████  ██  █   ███   █████  █████  ", Color::BRIGHT_GREEN);
    std::cout << Color::tcolor("●", Color::BRIGHT_YELLOW) << std::endl;
    std::cout << Color::tcolor("        ●", Color::BRIGHT_YELLOW) << Color::tcolor(" █      █ █ █  █   █      █  █      ", Color::BRIGHT_GREEN);
    std::cout << Color::tcolor("●", Color::BRIGHT_YELLOW) << std::endl;
    std::cout << Color::tcolor("        ●", Color::BRIGHT_YELLOW) << Color::tcolor("  ███   █ █ █  █████   ███   ████   ", Color::BRIGHT_GREEN);
    std::cout << Color::tcolor("●", Color::BRIGHT_YELLOW) << std::endl;
    std::cout << Color::tcolor("        ●", Color::BRIGHT_YELLOW) << Color::tcolor("     █  █ █ █  █   █  █      █      ", Color::BRIGHT_GREEN);
    std::cout << Color::tcolor("●", Color::BRIGHT_YELLOW) << std::endl;
    std::cout << Color::tcolor("        ●", Color::BRIGHT_YELLOW) << Color::tcolor(" ████   █ ███  █   █  █████  █████  ", Color::BRIGHT_GREEN) << std::endl;
    std::cout << Color::tcolor("        ●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●<", Color::BRIGHT_YELLOW) << std::endl;

    std::cout << std::endl;
}


