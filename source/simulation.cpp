#include "simulation.h"
#include <iostream>

/**
 * @brief Read arguments from CLI, update simulation values and read level that will be played
*/
void SnazeSimulation::initialize(int argc, char* argv[]){
    std::string arg;

    // If only no argument was given, error because it means a level wasnt loaded
    if (argc == 1){
        // error!
    } 
    
    // If only one argument was give, it's either --help or the input file name
    else if (argc == 2){
        arg = argv[1];
        // Only input level file given or --help
        if (arg == "--help"){
            // Output help message
            help_message();
            return exit(0);
        } 
        
        else {
            // input level file

            // If input level file is not valid give error notification!
        }
    } 
     // At least one optional argument and the input level file were given
    else {
        for (int i = 1; i < argc; i++){
            arg = argv[i];
            if (arg == "--help") {
                help_message();
                return exit(0);
            } else if (arg == "--fps"){
                arg = argv[++i];

                try {
                    // Add a verifier to check if it's positive
                    if (!(std::stoi(arg) >= 0)) {
                        std::cerr << "Error: Fps resulted in a negative value." << std::endl;
                        return exit(1);
                    }
                    fps = static_cast<short>(std::stoi(arg));
                    std::cout << "fps: " << fps << std::endl;
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: " << e.what() << std::endl;
                    return exit(1);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range: " << e.what() << std::endl;
                    return exit(1);
                }
            } else if (arg == "--lives") {
                arg = arg[++i];
                try {
                    // Add a verifier
                    if (!(std::stoi(arg) >= 0)) {
                        std::cerr << "Error: Fps resulted in a negative value." << std::endl;
                        return exit(1);
                    }
                    lives = static_cast<short>(std::stoi(arg));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: " << e.what() << std::endl;
                    return exit(1);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range: " << e.what() << std::endl;
                    return exit(1);
                }
            } else if (arg == "--food") {
                arg = arg[++i];
                try {
                    // Add a verifier
                    if (!(std::stoi(arg) >= 0)) {
                        std::cerr << "Error: Fps resulted in a negative value." << std::endl;
                        return exit(1);
                    }
                    food = static_cast<short>(std::stoi(arg));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: " << e.what() << std::endl;
                    return exit(1);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range: " << e.what() << std::endl;
                    return exit(1);
                }
            } else if (arg == "--playertype"){

            } 
            
            // input file name
            else {

                // If input file name is not valid, give error
                //error!!
            }
        }
    }
} 

bool is_over(){
    return false;
}

unsigned short SnazeSimulation::ret_lives(){
    return lives;
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
    std::cout << " Levels loaded: 0 | Snake lives: " << ret_lives() << "" << std::endl;
    std::cout << " " << std::endl;

}

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