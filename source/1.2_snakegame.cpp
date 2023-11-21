#include "1.1_snakegame.h"
/**
 * @brief Read arguments from CLI, update simulation values and read level that will be played
*/
void SnakeGame::initialize(int argc, char* argv[]){
    std::string arg;

    // If only no argument was given, error because it means a level wasnt loaded
    if (argc == 1){
        // error!
        std::cerr << "Error opening the file." << std::endl;
        return exit(1);
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
            open_file(arg);

            // If input level file is not valid give error notification (already done in open_file)
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
                std::cout << "passou aqui" << std::endl;
                open_file(arg);
                // If input file name is not valid, give error (this is already done in open_file)
                
                // Don't read any argument after this
                break;
            }
        }
    }
    // Read information on file
    std::cout << "passou" << std::endl;
    read_file();
} 

/**
 * @brief Function that returns if the game is over or not
*/
bool SnakeGame::is_over(){
    return false;
}

/**
 * @brief Return starting lives
*/
unsigned short SnakeGame::ret_lives(){
    return lives;
}

/**
 * @brief Return starting food amount
*/
unsigned short SnakeGame::ret_food(){
    return food;
}

/**
 * @brief Takes a string argument indicating the name for the input file and opens it 
*/
void SnakeGame::open_file(const std::string& filename){
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

/**
 * @brief Read the information contained in the file
*/
void SnakeGame::read_file(){
    int lines{-1};
    int columns{-1};
    int levels{0};
    std::string str;
    std::vector<std::vector<char>> matrix;

    bool is_valid{false};
    bool invalid{false};

    while(inputfile >> lines >> columns){
  
        // validation auxiliation values
        is_valid = false;
        invalid = false;

        // Read the rest of the line that contains lines and columns (essentially jump to next line)
        getline(inputfile,str);

        if(lines > 100 || lines < 1 || columns < 1 || columns > 100){
            //error!
            // lines or columns out of range (lines,columns > 100)        
            
        }

        matrix.resize(lines);

        // Resize each row to the specified number of columns and initialize with a default value (in this case, '0')
        for (int i = 0; i < lines; ++i) {
        matrix[i].resize(columns, '0');
        }
    
        // Read characters (columns * lines) times
        for (int i = 0; i < lines; i++){
            
            // Read line
            getline(inputfile, str);
    
            for (int j = 0; j < columns; j++){
                // Checks for the second aparition of the spawnpoint in the level, determining that it is in fact invalid
                if (str[j] == '&' && is_valid == true){
                    invalid = true;
                    is_valid = false;
                    break;
                } 
                
                // Checks for the first aparition of the spawnpoint in the level
                else if (str[j] == '&' && is_valid == false){
                    is_valid = true;
                }
                matrix[i][j] = str[j];
            }

            if (invalid == true){
                break;
            } 

        }
        
        if (is_valid == true){
            Level level{lines,columns, matrix};
            level.read_level_maze();
            m_levels.push_back(level);

            std::cout << "completo: " << std::endl;
            level.display();
        } else if (invalid == true){
            // Ignore level
        }

        

        

        // Read characters (columns * lines) times
        /*for (unsigned short i = 0; i < lines; i++) {
            getline(inputfile, str);

            
            // test to see if number of columns is right

            /*if (str.size() == columns) {
                std::cout << "ok";
            } else {
                std::cout << i << " str: " << str;
                std::cout << " not ok";
            }*/
    }
    
    inputfile.close();
}