#include "2.0_level.h"
#include <random>

/**
 * @brief Display char matrix
*/
void Level::display(){
    for(int i{0}; i < m_lines; i++){
        for (int j{0}; j < m_columns; j++){
            std::cout << m_map[i][j];
        } std::cout << std::endl;
    }
}

/**
 * @brief Read char matrix as argument, encode it into a CellType matrix 
*/
void Level::read_level_maze(){

    // Current char in the char matrix
    char current_char;
    
    CellType type;

    // Resize m_maze
    m_maze.resize(m_lines, std::vector<CellType>(m_columns, CellType::EMPTY));

    for(int i{0}; i < m_lines; i++){
        for (int j{0}; j < m_columns; j++){
            current_char = m_map[i][j];

            switch(current_char){
                case '#':
                type = CellType::WALL;
                break;

                case '.':
                type = CellType::INVISIBLE_WALL;
                break;

                case '&':
                type = CellType::SPAWN_POINT;
                spawn_point.p_line = i;
                spawn_point.p_column = j;
                snake_head = spawn_point;
                break;

                case ' ':
                type = CellType::EMPTY;
                break;

                case '*':
                type = CellType::FOOD;
                break;
            }

            m_maze[i][j] = type;
        }
    }
}


void Level::display_run_game(){
    
    CellType type;
    std::string current_char;
    for(int i{0}; i < m_lines; i++){

        for (int j{0}; j < m_columns; j++){
            type = m_maze[i][j];

            switch(type){
                case (CellType::WALL):
                std::cout << Color::tcolor("█", Color::BRIGHT_GREEN);
                break;

                case (CellType::INVISIBLE_WALL):
                std::cout << " ";
                break;

                case (CellType::SPAWN_POINT):
                std::cout << Color::tcolor("<", Color::BRIGHT_YELLOW);
                break;

                case (CellType::EMPTY):
                std::cout << " ";
                break;
            
                case(CellType::FOOD):
                std::cout << "x"; 
                break;

                case(CellType::SNAKE_HEAD_FORWARD):
                std::cout << Color::tcolor("v", Color::BRIGHT_YELLOW);
                break;

                case(CellType::SNAKE_HEAD_BACKWARD):

                std::cout << Color::tcolor("ʌ", Color::BRIGHT_YELLOW);
                break;

                case(CellType::SNAKE_HEAD_LEFT):
                std::cout << Color::tcolor(">", Color::BRIGHT_YELLOW);
                break;

                case(CellType::SNAKE_HEAD_RIGHT):
                std::cout << Color::tcolor("<", Color::BRIGHT_YELLOW);
                break;

                case(CellType::SNAKE_BODY):
                std::cout << Color::tcolor("●", Color::BRIGHT_YELLOW);
                break;
            }

            //std::cout << current_char;
        } std::cout << std::endl;
    }
}


//brief Deletes the food item from the level.
//This function removes the food item from the level by updating the corresponding cell to EMPTY.
void Level::delete_food(){
    m_maze[m_pos_food.p_line][m_pos_food.p_column] = CellType::EMPTY;
}



//@brief Generates the position for a new food item. 
//This function randomly selects a valid position in the maze and sets it as the new food location.
void Level::pos_new_food(){

    bool pos_valid{false};

    while(!pos_valid){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution_line(0, m_lines - 1);
        std::uniform_int_distribution<int> distribution_column(0, m_columns - 1);
        m_pos_food.p_line = distribution_line(gen);
        m_pos_food.p_column = distribution_column(gen);

        if(m_maze[ m_pos_food.p_line][m_pos_food.p_column] == CellType::EMPTY){
            pos_valid = true;
            m_maze[m_pos_food.p_line][ m_pos_food.p_column] = CellType::FOOD;
        } 
    }
}

/**
 * @brief Resets the position and body of the snake.
 * 
 * This function resets the position and body of the snake in the level. It clears the snake's tail
 * from the maze, sets the snake's head position to the spawn point, and resets the body size.
 * 
 * @param size_body The size of the snake's body, which is updated to 1 after the reset.
 */
void Level::reset_snake(size_t& size_body){


    while (!snake_tail.empty()){
        auto temp = snake_tail.front();
        snake_tail.pop();
        m_maze[temp.p_line][temp.p_column] = CellType::EMPTY;   
    } 

    snake_head.p_column = spawn_point.p_column;
    snake_head.p_line = spawn_point.p_line;
    size_body = 1;

    m_maze[ snake_head.p_column][snake_head.p_line] = CellType::SPAWN_POINT;  


}

/**
 * @brief Try to find the smallest path to the food
 * When this function is called there is already a food in the maze
*/
std::queue<direction> Level::new_path(){

    // Path that will be taken
    std::queue<direction> path;

    // Auxiliary char matrix to help the algorithm
    std::vector<std::vector<char>> matrix_char;

    // Auxiliary value position matrix to help the algorithm
    std::vector<std::vector<int>> matrix_value;

    Position food; // Position of current food
    Position head_of_snake; // Position of current head of snake
    CellType type;
    char character;

    // Resizing both matrixes
    matrix_char.resize(m_lines);
    matrix_value.resize(m_lines);
    for(int i{0}; i < m_lines; i++){
        matrix_char[i].resize(m_columns);
        matrix_value[i].resize(m_columns);
    }

    // Initialize all value of matrix_value as -3;
    for(int i{0}; i < m_lines; i++){
        for (int j{0}; j < m_columns; j++){
            matrix_value[i][j] = -3;
        }
    }
    
    // Converter matriz de cellType em matriz de char para 
    // Convert matrix of celltype into matrix of char for better visualization
    for(int i{0}; i < m_lines; i++){
        for (int j{0}; j < m_columns; j++){
            type = m_maze[i][j];
            switch (type)
            {
            case (CellType::WALL):
                character = '#';
                break;
            
            case (CellType::EMPTY):
                character = ' ';
                break;

            case (CellType::FOOD):
                character = 'f';
                // Store food position
                food.p_line = i;
                food.p_column = j;
                food.value = 1000;
                matrix_value[i][j] = 1000;
                break;

            case (CellType::INVISIBLE_WALL):
                character = '.';
                break;
            case (CellType::SNAKE_HEAD_BACKWARD):
                character = '1';

                // store head position
                head_of_snake.p_line = i;
                head_of_snake.p_column = j;
                head_of_snake.value = 0;
                matrix_value[i][j] = 0;
                break;

            case (CellType::SNAKE_HEAD_FORWARD):
                character = '2';
                head_of_snake.p_line = i;
                head_of_snake.p_column = j;
                head_of_snake.value = 0;
                matrix_value[i][j] = 0;
                break;

            case (CellType::SNAKE_HEAD_LEFT):
                character = '3';
                head_of_snake.p_line = i;
                head_of_snake.p_column = j;
                matrix_value[i][j] = 0;
                head_of_snake.value = 0;
                break;

            case (CellType::SNAKE_HEAD_RIGHT):
                character = '4';
                head_of_snake.p_line = i;
                head_of_snake.p_column = j;
                head_of_snake.value = 0;
                matrix_value[i][j] = 0;
                break;
            
            case (CellType::SPAWN_POINT):
                character = '&';
                head_of_snake.p_line = i;
                head_of_snake.p_column = j;
                head_of_snake.value = 0;
                matrix_value[i][j] = 0;
                break;

            case (CellType::SNAKE_BODY):
                character = '=';
                matrix_value[i][j] = -3;
                break;
            }
            matrix_char[i][j] = character;
        }
    }

    // teste output
    std::cout << "Linha cabeça: " << head_of_snake.p_line << " Coluna cabeça: "<< head_of_snake.p_column << " Valor cabeça: " << head_of_snake.value<< std::endl;
    std::cout << "Linha comida: " << food.p_line << " Coluna comida: "<< food.p_column << " Valor comida: " << food.value << std::endl;
    for(int i{0}; i < m_lines;i++){
        for (int j{0}; j < m_columns; j++){
            std::cout << matrix_char[i][j];
        } std::cout << std::endl;
    }

    // Até aqui sai a matriz de char normal que aparece no terminal

    std::queue<Position> my_queue;
    
    std::cout << "while loop: (aperte enter para continuar)" << std::endl;
    //std::cin.ignore();


    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {1, 0, -1, 0};

    for (int k = 0; k < 4; ++k) {
        int newX = food.p_line + dx[k];
        int newY = food.p_column + dy[k];

        if (isValid(newX, newY, m_lines, m_columns) && matrix_char[newX][newY] == ' ') {
            matrix_char[newX][newY] = '*';
            Position aux{newX, newY};
            aux.value = matrix_value[food.p_line][food.p_column] - 1;
            matrix_value[newX][newY] = aux.value;
            my_queue.push(aux);
        }
    }

    while (!my_queue.empty()) {
        Position current = my_queue.front();
        my_queue.pop();

        for (int k = 0; k < 4; ++k) {
            int newX = current.p_line + dx[k];
            int newY = current.p_column + dy[k];

            if (isValid(newX, newY, m_lines, m_columns) && matrix_char[newX][newY] == ' ') {
                matrix_char[newX][newY] = '*';
                Position aux{newX, newY};
                if (current.value != -3) {
                    aux.value = matrix_value[current.p_line][current.p_column] - 1;
                    matrix_value[newX][newY] = aux.value;
                }
                my_queue.push(aux);
            }
        }
    }

    std::cout << "saiu do while loop " << std::endl;

    for(int i{0}; i < m_lines;i++){
        for (int j{0}; j < m_columns; j++){
            std::cout << matrix_value[i][j] << " ";
        } std::cout << std::endl;
    }

    
    Position current = head_of_snake; // Starting point
    short closest_higher{0};
    short closest_direction{-3};
    Position closest_position;
    // Advance one block
    for(int k = 0; k < 4; k++){
        int newX = current.p_line + dx[k];
        int newY = current.p_column + dy[k];
        if (isValid(newX, newY, m_lines, m_columns) && matrix_value[newX][newY] > 0) {
            if (closest_higher < matrix_value[newX][newY]){
                closest_higher = matrix_value[newX][newY];
                closest_direction = k;
                closest_position.p_line = newX;
                closest_position.p_column = newY;
            }
        }    
    }
    current = closest_position;
    current.value = closest_higher;

    switch (closest_direction) {
        case 0:
            path.push(direction::RIGHT);
            break;
        case 1:
            path.push(direction::BACKWARD);
            break;
        case 2:
            path.push(direction::LEFT);
            break;
        case 3:
            path.push(direction::FORWARD);
            break;
        default:
            std::cout << "Deu erro, acho que a cobra não tem path para seguir" << std::endl;
            break;
    }

    // Follow the path from the snake's current position to the food
    while (matrix_value[current.p_line][current.p_column] != 1000) {
        for (int k = 0; k < 4; ++k) {
            int newX = current.p_line + dx[k];
            int newY = current.p_column + dy[k];
            if (isValid(newX, newY, m_lines, m_columns) && matrix_value[newX][newY] == (current.value + 1)) {
                switch (k) {
                    case 0:
                        path.push(direction::RIGHT);
                        break;
                    case 1:
                        path.push(direction::BACKWARD);
                        break;
                    case 2:
                        path.push(direction::LEFT);
                        break;
                    case 3:
                        path.push(direction::FORWARD);
                        break;
                }
                current.p_line = newX;
                current.p_column = newY;
                current.value = matrix_value[newX][newY];
                break;  // Move to the next step in the path
            }
        }
    }



    return path;
}

/**
 * @brief Generates a random direction for the snake to follow, avoiding walls and its own body.
 * 
 * This function randomly selects a direction for the snake to move, ensuring that the chosen path
 * is not obstructed by walls or the snake's body.
 * 
 * @return A randomly selected direction for the snake.
 */
direction Level::path_random() {
    // Chosen direction for the snake's movement.
    direction direction_snaze;

    // Random number determining the snake's movement direction.
    int random;

    // Flag indicating the validity of the generated path.
    bool path_valid{false};
    int teste = 0;


    // Continue generating a random direction until a valid path is found
    while (!path_valid) {

        bool peso_f{false};
        bool peso_b{false};
        bool peso_l{false};
        bool peso_r{false};

        int column = snake_head.p_column;
        int line = snake_head.p_line;

        if(m_pos_food.p_line > line){
            peso_b = true;
            teste++;
        }
        else if(m_pos_food.p_line < line){
            peso_f = true;
            teste++;
        }
        else if(m_pos_food.p_column > column){
            peso_r = true;
            teste++;
        }
        else if(m_pos_food.p_column < column){
            peso_l = true;
            teste++;
        }
        if(teste == 4){
            peso_b = peso_f = peso_l = peso_r = true;
            teste = 0;
        }

        // Generate a random number (0 to 3) representing a direction
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 3);
        random = distribution(gen);

        // Check if there's a wall or snake body in all directions, set random to 4 if so
        if ((m_maze[line - 1][column] == CellType::WALL || m_maze[line - 1][column] == CellType::SNAKE_BODY) &&
            (m_maze[line + 1][column] == CellType::WALL || m_maze[line + 1][column] == CellType::SNAKE_BODY) &&
            (m_maze[line][column - 1] == CellType::WALL || m_maze[line][column - 1] == CellType::SNAKE_BODY) &&
            (m_maze[line][column + 1] == CellType::WALL || m_maze[line][column + 1] == CellType::SNAKE_BODY)) {
            random = 4;
        }

        // Check and update positions based on the randomly selected direction
        if (random == 0 && peso_f == true) { // Forward
            line -= 1;
            if (m_maze[line][column] == CellType::EMPTY || m_maze[line][column] == CellType::FOOD) {
                direction_snaze = direction::FORWARD;
                path_valid = true;
            }
        } 
        else if (random == 1 && peso_b == true) { // Backward
            line += 1;
            if (m_maze[line][column] == CellType::EMPTY || m_maze[line][column] == CellType::FOOD) {
                direction_snaze = direction::BACKWARD;
                path_valid = true;
            }
        } 
        else if (random == 2 && peso_l == true) { // Left
            column -= 1;
            if (m_maze[line][column] == CellType::EMPTY || m_maze[line][column] == CellType::FOOD) {
                direction_snaze = direction::LEFT;
                path_valid = true;
            }
        } 
        else if (random == 3 && peso_r == true) { // Right
            column += 1;
            if (m_maze[line][column] == CellType::EMPTY || m_maze[line][column] == CellType::FOOD) {
                direction_snaze = direction::RIGHT;
                path_valid = true;
            }
        } 
        else if (random == 4) { // Undefined
            direction_snaze = direction::UNDEFINED;
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;
            path_valid = true;
        }

        if(direction_prev == direction::BACKWARD and direction_snaze == direction::FORWARD and teste <= 4){
            path_valid = false;
        }
        else if(direction_prev == direction::FORWARD and direction_snaze == direction::BACKWARD and teste <= 4){
            path_valid = false;
        }
        else if(direction_prev == direction::RIGHT and direction_snaze == direction::LEFT and teste <= 4){
            path_valid = false;
        }
        else if(direction_prev == direction::LEFT and direction_snaze == direction::RIGHT and teste <= 4){
            path_valid = false;
        }



    }

    direction_prev = direction_snaze;
    return direction_snaze;
}

/**
 * @brief Moves the snake in the specified direction, updating the game state.
 * 
 * This function handles the movement of the snake based on the specified direction.
 * It updates the snake's head, body, and the game state, taking into account collisions
 * with food and the snake itself.
 * 
 * @param m_direction The direction in which the snake should move.
 * @param size_body Reference to the size of the snake's body.
 * @param food Reference to the count of food eaten by the snake.
 */
void Level::snake_move(direction m_direction, size_t& size_body, size_t& food) {

    // Temporary marker to store the current position of the snake's head.
    Position temp;

    // Assigning the current line position of the snake's head to the temporary marker.
    temp.p_line = snake_head.p_line;

    // Assigning the current column position of the snake's head to the temporary marker.
    temp.p_column = snake_head.p_column;
 

    snake_tail.push(temp);                      

    // Update the maze based on the snake's size and direction
    if (size_body > 1) {
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_BODY;
    } 
    else if (size_body < 2) {
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;
    }

    // Move the snake's head and check for collisions with food
    if (m_direction == direction::FORWARD) {
        snake_head.p_line -= 1;
    } 
    else if (m_direction == direction::BACKWARD) {
        snake_head.p_line += 1;
    } 
    else if (m_direction == direction::LEFT) {
        snake_head.p_column -= 1;
    } 
    else if (m_direction == direction::RIGHT) {
        snake_head.p_column += 1;
    }

    if (m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD) {
        size_body += 1;
        food += 1;
    }

    // Remove the last segment of the snake's tail if its size exceeds the current body size
    if (size_body <= snake_tail.size()) {
        while (size_body <= snake_tail.size()) {
            temp = snake_tail.front();
            snake_tail.pop();
            m_maze[temp.p_line][temp.p_column] = CellType::EMPTY;   
        } 
    }

    // Update the maze with the new position of the snake's head based on the direction
    if (m_direction == direction::FORWARD) {
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_FORWARD;
    } 
    else if (m_direction == direction::BACKWARD) {
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_BACKWARD;
    } 
    else if (m_direction == direction::LEFT) {
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_LEFT;
    } 
    else if (m_direction == direction::RIGHT) {
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_RIGHT;
    }
}


bool Level::isValid(int x, int y, int rows, int cols) {
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

//Return spawn position of current level.
Position Level::ret_spawn_position(){
    return spawn_point;
}