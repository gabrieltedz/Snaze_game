#include "simulation.h"
#include <iostream>

void SnazeSimulation::initialize(int argc, char* argv[]){
    std::string arg{argv[1]};

    if (argc == 1){
        // error!
    } else if (argc == 2){
        // Only input level file given or --help
        if (arg == "--help"){
            // Output help message
            help_message();
            return exit(0);
        } else {
            // input level file

            // If input level file is not valid give error notification!
        }
    } else { // At least one option and the input level file were given
        for (int i = 1; i < argc; i++){
            arg = argv[i];
            if (arg == "--help") {
                help_message();
                return exit(0);
            } else if (arg == "--fps"){
                arg = argv[++i];
                std::cout << "arg: " << arg << std::endl;
                try {
                    // Add a verifier
                    if (!(std::stoi(arg) >= 0)) {
                        std::cerr << "Error: Fps resulted in a negative value." << std::endl;
                        return exit(1);
                    }
                    fps = static_cast<short>(std::stoi(arg));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: " << e.what() << std::endl;
                    return exit(1);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range: " << e.what() << std::endl;
                    return exit(1);
                }
            }
        }
    }

} 

bool is_over(){
    return false;
}

