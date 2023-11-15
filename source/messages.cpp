#include "messages.h"

void introduction_message(){
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "===> Welcome to the classic Snake Game! <===" << std::endl;
    std::cout << "       copyright DIMAp / UFRN 2023" << std::endl;
    /*
    std::cout << 
    std::cout << 
    std::cout <<*/ 

}

void help_message(){
    std::cout << "$ ./build/snaze " << std::endl;
    std::cout << "Usage: snaze [<options>] <input_level_file>" << std::endl;
    std::cout << "      Game simulation options:" << std::endl;
    std::cout << "          --help              Print this help text." << std::endl;
    std::cout << "          --fps <num>         Number of frames (board) presented per second." << std::endl;
    std::cout << "          --lives <num>       Number of iles the snake shall have. Default = 5." << std::endl;
    std::cout << "          --food <num>        Number of food pellets for the entire simulation. Default = 10." << std::endl;
    std::cout << "          --playertype <type> Type of snake intelligence: random, backtracking. Default = backtracking" << std::endl;
}