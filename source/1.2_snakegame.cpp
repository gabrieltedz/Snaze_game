#include "1.1_snakegame.h"


/**
 * @brief Tests if the string is convertible to int
*/
bool SnakeGame::aux_is_convert_to_int(const std::string& str) {
    try {
        size_t pos;
        std::stoi(str, &pos);
        
        // Check if the entire string was used in the conversion
        return pos == str.length();
    } catch (std::invalid_argument&) {
        // stoi threw an invalid_argument exception, indicating a conversion error
        return false;
    } catch (std::out_of_range&) {
        // stoi threw an out_of_range exception, indicating the value is out of the range of int
        return false;
    }
}

/**
 * @brief Constructor
*/
SnakeGame::SnakeGame(){

    food = 10;
    lives = 3;
    fps = 4;
    num_levels = 0;

    score = 0;
    snake_size_body = 1;
    foods = 0;
    m_player_type = player_type::BACKTRACKING;

    game_over = false;
    m_game_state = game_state::STARTING;
}


/**
 * @brief Read arguments from CLI, update simulation values and read level that will be played
*/
void SnakeGame::initialize(int argc, char* argv[]){
    std::string arg;

    // If only no argument was given, error because it means a level wasnt loaded
    if (argc == 1){
        // error!
        std::cerr << "Error opening the file." << std::endl;

        // Display usage
        help_message();

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

                // Advance to next argument
                arg = argv[++i];

                // If the current argument is convertible to int
                if(aux_is_convert_to_int(arg) == true){
                    try {
                        // Add a verifier to check if it's negative
                        if (!(std::stoi(arg) >= 0)) {
                            std::cout << Color::tcolor("Error: Fps resulted in a negative value.", Color::BRIGHT_RED, Color::BOLD) << "\n\n";
                            help_message();
                            return exit(1);
                        }
                        else if(std::stoi(arg) >= 100){
                            std::cout << Color::tcolor("Error:The FPS exceeded the limit.", Color::BRIGHT_RED, Color::BOLD) << "\n\n";
                            help_message();
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
                } else {
                    std::cout << "Missing number after argument --fps!" << std::endl;
                    exit(1);
                }

            } 
            
            // If argument is --lives, read the next value as short and update lives
            else if (arg == "--lives") {
                // Advance to next argument
                arg = argv[++i];

                // If the current argument is convertible to int
                if(aux_is_convert_to_int(arg) == true){
                    try {
                        // Add a verifier to check if it's negative
                        if (!(std::stoi(arg) >= 0)) {
                            std::cout << Color::tcolor("Error:The quantity of lives is negative.", Color::BRIGHT_RED, Color::BOLD) << "\n\n";
                            help_message();
                            return exit(1);
                        }
                        else if(std::stoi(arg) > 20){
                            std::cout << Color::tcolor("Error:The quantity of lives exceeded the limit.", Color::BRIGHT_RED, Color::BOLD) << "\n\n";
                            help_message();
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
                } else {
                    std::cout << "Missing number after argument --lives!" << std::endl;
                    exit(1);
                }
                
            } 
            
            // If argument is --food, read the next value as short and update food
            else if (arg == "--food") {

                // Advance one
                arg = argv[++i];

                // Check if current argument is convertible to int
                if(aux_is_convert_to_int(arg) == true){
                    try {
                        // Add a verifier to check if it's negative
                        if (!(std::stoi(arg) >= 0)) {
                            std::cerr << "Error: The quantity of foods is negative." << std::endl;
                            std::cout << Color::tcolor("Error: The quantity of foods is negative.", Color::BRIGHT_RED, Color::BOLD) << "\n\n";
                            help_message();
                            return exit(1);
                        }
                        else if(std::stoi(arg) > 50){
                            std::cout << Color::tcolor("Error:The quantity of foods exceeded the limit.", Color::BRIGHT_RED, Color::BOLD) << "\n\n";
                            help_message();
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
                } else {
                    std::cout << "Missing number after argument --food!" << std::endl;
                    exit(1);
                }

            } else if (arg == "--playertype"){
                arg = argv[++i];
                if (arg == "random"){
                    m_player_type = player_type::RANDOM;
                } else if (arg == "backtracking"){
                    m_player_type = player_type::BACKTRACKING;
                } else {
                    std::cout << "Unknown option after argument --playertype!" << std::endl;
                    exit(1);
                }
            } 
            
            // If not any options from the above, it's assumed it's the file's name
            else {
                open_file(arg);
                // If input file name is not valid, give error (this is already done in open_file)
                
                // Don't read any argument after this
                break;
            }
        }
    }
    // Read information on file
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

size_t SnakeGame::ret_score(){
    return score;
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
        std::cerr << "Error opening the file. File (" << filename << ") not found\n";
        // Handle the error appropriately, you might throw an exception or take other actions
        return exit(1);
    }
}

/**
 * @brief Read the information contained in the file
*/
void SnakeGame::read_file(){
    // Initialize variables as default
    int lines{-1};
    int columns{-1};
    //int levels{0};
    std::string str;
    std::vector<std::vector<char>> matrix;

    bool is_valid{false};
    bool invalid{false};

    // Read the lines and columns of levels in the file
    while(inputfile >> lines >> columns){
        Level level1;
  
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

            // If invalid, break
            if (invalid == true){
                break;
            } 

        }
        
        // If valid
        if (is_valid == true){
            // Initialize level with lines, columns and original char matrix
            level1.m_lines = lines;
            level1.m_columns = columns;
            level1.m_map = matrix;

            // Create CellType matrix
            level1.read_level_maze();

            // Add valid level to m_levels
            //std::cout << "\n novo level \n";
            m_levels.push_back(level1);

            //std::cout << "Posição spawn, line: " << level1.ret_spawn_position().p_line << ", column: " << level1.ret_spawn_position().p_column << std::endl;

            // Original char matrix
            //std::cout << "completo char: " << std::endl;
            //level1.display();

            // Celltype matrix
            //std::cout << "completo cell_type: " << std::endl;
            //level.display_maze();
        } 
        else if (invalid == true){
            // Ignore level
        }

    }
    inputfile.close();
}



/**
 * @brief Processes game events.
 * 
 * This function processes game events, such as user input.
 */
void SnakeGame::process_events(){
    if(m_game_state == game_state::STARTING || m_game_state == game_state::SNAKE_DIE){
        std::string empty;
        std::getline(std::cin, empty);
    }

}


/**
 * @brief Updates the game state based on the current game state.
 * 
 * This function handles the main game loop, updating the game state and
 * performing actions based on the current state.
 */
void SnakeGame::update(){
    /// Game initialization
    if(m_game_state == game_state::STARTING){
        // Set the level to be played and transition to the state of generating new food.
        level = m_levels[num_levels];
        m_game_state = game_state::NEW_FOOD;
    }

    /// Generate a new food at a random location
    else if(m_game_state == game_state::NEW_FOOD){
        // If the snake has eaten the required amount of food, move to the new level.
        if(foods == ret_food()){
            m_game_state = game_state::NEW_LEVEL;
        }
        // Generate the position of the new food.
        else{
            level.pos_new_food();
            m_game_state = game_state::NEW_PATH;
        }
    }

    /// Find the path to be followed
    else if(m_game_state == game_state::NEW_PATH){
        if(m_player_type == player_type::BACKTRACKING){
            path = level.new_path();


            if(path.empty()){
                m_game_state = game_state::RANDOM_DIRECTION;
               
            }
            else{
                // Transition to the state of updating the snake's direction.
                m_game_state = game_state::UPDATE_DIRECTION;
            }

        }
        else if(m_player_type == player_type::RANDOM){
            m_game_state = game_state::RANDOM_DIRECTION;
        }
    }

    // Update the snake's direction
    else if(m_game_state == game_state::UPDATE_DIRECTION){
        if(m_player_type == player_type::BACKTRACKING){

            if(path.empty()){
                m_game_state = game_state::NEW_FOOD;
            }
            else{
                auto temp = snake_size_body;
                // Move the snake in the specified direction and remove it from the path.
                level.snake_move(path.front(), snake_size_body, foods);
                path.pop();

                if(temp < snake_size_body) {
                    score += foods * 10;
                }
            
            }
        }
        else if(m_player_type == player_type::RANDOM){
            // Move the snake in the specified direction and remove it from the path.
            level.snake_move(path.front(), snake_size_body, foods);
            path.pop();
        }

    }

    // Choose a random direction
    else if(m_game_state == game_state::RANDOM_DIRECTION){

        if(m_player_type == player_type::BACKTRACKING){
            m_game_state = game_state::NEW_STATE;
        }
        auto temp = snake_size_body;
        auto aux = level.path_random(); // there is the error of the snake not moving here

        // If the direction is undefined, the snake dies.
        if(aux == direction::UNDEFINED){
            m_game_state = game_state::SNAKE_DIE;
        }
        else{
            // Move the snake in the randomly chosen direction.
            level.snake_move(aux, snake_size_body, foods);
        }

        // If the body size increased, generate a new food and update the score.
        if(temp < snake_size_body) {
            m_game_state = game_state::NEW_FOOD;
            score += foods * 10;
        }
    }

    // If the snake dies, reset the game.
    else if(m_game_state == game_state::SNAKE_DIE){
        level.reset_snake(snake_size_body);
        lives -= 1;

        // If no lives are left, transition to the game over state.
        if(lives == 0){
            m_game_state = game_state::GAME_OVER;
        }
        else{
            m_game_state = game_state::NEW_PATH;
        }
    }

    // Start a new level
    else if(m_game_state == game_state::NEW_LEVEL){
        snake_size_body = 1;
        // Change the level and update the matrix with the new data.

        num_levels++;
        // If there are more levels, reset the food count and transition to the starting state.
        if(m_levels.size() > num_levels){
            foods = 0;
            m_game_state = game_state::STARTING;
        }
        // Otherwise, transition to the finished puzzle state.
        else{
            m_game_state = game_state::FINISHED_PUZZLE;
        }
    }

    else if(m_game_state == game_state::NEW_STATE){
        m_game_state = game_state::NEW_PATH;

    }

    // Finished puzzle state
    else if(m_game_state == game_state::FINISHED_PUZZLE){
        // Exit the game.
        exit(1);
    }

    // Game over state
    else if(m_game_state == game_state::GAME_OVER){
        // Exit the game.
        exit(1);
    }
}

/**
 * @brief Renders the game state for display.
 * 
 * This function handles the rendering of the game state based on the current game state.
 * It displays relevant information or graphics for each game state.
 */
void SnakeGame::render(){

    // Rendering for the STARTING game state
    if(m_game_state == game_state::STARTING){
        // Display initial game data and the running game.
        data_game();
        level.display_run_game();

        // Prompt to press Enter to continue.
        std::cout << Color::tcolor( "\n>>> Press enter to continue.\n", Color::BRIGHT_WHITE, Color::BOLD);
    }

    // Rendering for the UPDATE_DIRECTION game state
    else if(m_game_state == game_state::UPDATE_DIRECTION){
        //std::cout << "MODO TRACKING";
        // Uncomment the following lines if rendering logic is to be executed.
        std::chrono::milliseconds duration{1000 / fps};
        std::this_thread::sleep_for(duration);
        data_game();
        level.display_run_game();
    }

    // Rendering for the RANDOM_DIRECTION game state
    else if(m_game_state == game_state::RANDOM_DIRECTION || m_game_state == game_state::NEW_STATE){
        //std::cout << "MODO RANDOM";
        // Pause for a short duration, then display game data and the running game.
        std::chrono::milliseconds duration{1000 / fps};
        std::this_thread::sleep_for(duration);
        data_game();
        level.display_run_game();
    }

    // Rendering for the SNAKE_DIE game state
    else if(m_game_state == game_state::SNAKE_DIE){
        // Display a message indicating the snake has died, prompt to press Enter to continue.
        std::cout << Color::tcolor( "The snake has died, press Enter to continue.\n", Color::BRIGHT_RED, Color::BOLD);
    }

    // Rendering for the FINISHED_PUZZLE game state
    else if(m_game_state == game_state::FINISHED_PUZZLE){
        // Display game data, the running game, and a win message.
        data_game();
        level.display_run_game();
        game_win_display();
    }

    // Rendering for the GAME_OVER game state
    else if(m_game_state == game_state::GAME_OVER){
        std::cout << "game over" << std::endl;
        // Display the game over message.
        data_game();
        level.display_run_game();
        game_over_display();
    }

}   
