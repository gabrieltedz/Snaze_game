#include "simulation.h"

/**
 * @brief Read arguments from CLI, update simulation values and read level that will be played
*/
void SnazeSimulation::initialize(int argc, char* argv[]){
    std::string arg;

    // If only no argument was given, error because it means a level wasnt loaded
    if (argc == 1){
        // error!
    } 
    
    // If only one argument was given, it's either --help or the input file name
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

        // Iterate through each argument
        for (int i = 1; i < argc; i++){

            arg = argv[i];
            
            // If argument is help, show help message and exit program
            if (arg == "--help") {
                help_message();
                return exit(0);
            } 
            
            // If argument is --fps, read the next value as short and update fps
            else if (arg == "--fps"){
                arg = argv[++i];

                try {
                    // Add a verifier to check if it's negative
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

            } 
            
            // If argument is --lives, read the next value as short and update lives
            else if (arg == "--lives") {
                arg = argv[++i];

                try {
                    // Add a verifier to check if it's negative
                    if (!(std::stoi(arg) >= 0)) {
                        std::cerr << "Error: Fps resulted in a negative value." << std::endl;
                        return exit(1);
                    }
                    lives = static_cast<short>(std::stoi(arg));
                    std::cout << "lives: " << lives << std::endl;
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: " << e.what() << std::endl;
                    return exit(1);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range: " << e.what() << std::endl;
                    return exit(1);
                }
            } 
            
            // If argument is --food, read the next value as short and update food
            else if (arg == "--food") {
                arg = argv[++i];

                try {
                    // Add a verifier to check if it's negative
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
                open_file(arg);
                // If input file name is not valid, give error
                //error!!
                
                // Don't read any argument after this
                break;
            }
        }
    }
} 

bool SnazeSimulation::is_over(){
    return false;
}

unsigned short SnazeSimulation::ret_lives(){
    return lives;
}

unsigned short SnazeSimulation::ret_food(){
    return food;
}

void SnazeSimulation::open_file(const std::string& filename){
    // Convert the string to a C-style string using c_str()
    const char* filenameCStr = filename.c_str();

    // Open the file using ifstream
    inputfile.open(filenameCStr);

    // Check if the file is successfully opened
    if (!inputfile.is_open()) {
        std::cerr << "Error opening the file.\n";
        // Handle the error appropriately, you might throw an exception or take other actions
        return exit(1);
    }
    std::cout << "opened file!" << std::endl;
}

void SnazeSimulation::read_file(){
    int lines{-1};
    int columns{-1};
    int levels{0};
    std::string str;

    while(inputfile >> lines >> columns){
        // Read characters (columns * lines) times
        for (unsigned short i = 0; i <= lines; i++) {
            getline(inputfile, str);

            if (str.size() == columns) {

            }
            std::cout << str << std::endl;
        }
    }
}