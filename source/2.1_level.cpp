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

void Level::display_maze(){
    std::cout << "display maze:" << std::endl;

    CellType type;
    char current_char;
    for(int i{0}; i < m_lines; i++){

        for (int j{0}; j < m_columns; j++){
            type = m_maze[i][j];

            switch(type){
                case (CellType::WALL):
                current_char = '#';
                break;

                case (CellType::INVISIBLE_WALL):
                current_char = '.';
                break;

                case (CellType::SPAWN_POINT):
                current_char = '&';
                break;

                case (CellType::EMPTY):
                current_char = ' ';
                break;
            
                // case(CellType::FOOD):
                // current_char = ' ';
                // break;

                // case(CellType::SNAKE_HEAD):
                // current_char = '^';
                // break;
            }

            std::cout << current_char;
        } std::cout << std::endl;
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
                std::cout << ">";
                break;

                case (CellType::EMPTY):
                std::cout << " ";
                break;
            
                case(CellType::FOOD):
                std::cout << "x";
                break;

                case(CellType::SNAKE_HEAD_FORWARD):
                std::cout << "y";
                break;

                case(CellType::SNAKE_HEAD_BACKWARD):
                std::cout << 'v';
                break;

                case(CellType::SNAKE_HEAD_LEFT):
                std::cout << '<';
                break;

                case(CellType::SNAKE_HEAD_RIGHT):
                std::cout << '>';
                break;

                case(CellType::SNAKE_BODY):
                std::cout << "●";
                break;
            }

            //std::cout << current_char;
        } std::cout << std::endl;
    }
}

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

void Level::delete_food(){
    m_maze[m_pos_food.p_line][m_pos_food.p_column] = CellType::EMPTY;
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
    std::cin.ignore();


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

direction Level::path_random(size_t& size_body){
    direction teste;
    int random;
    bool path_valid{false};

    Position temp; 
    temp.p_line = snake_head.p_line;
    temp.p_column = snake_head.p_column;
    snake_tail.push(temp);

    while(!path_valid){
        int colunm = snake_head.p_column;
        int line = snake_head.p_line;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 3);
        random = distribution(gen);

        //forward
        if (random == 0){
            line -= 1;

            if (m_maze[line][colunm] == CellType::EMPTY || m_maze[line][colunm] == CellType::FOOD){
                teste = direction::FORWARD;

                path_valid = true;
            }
        }

        else if(random == 1){
            line += 1;

            if (m_maze[line][colunm] == CellType::EMPTY || m_maze[line][colunm] == CellType::FOOD){
                teste = direction::BACKWARD;

                path_valid = true;
            }
        }

        else if (random == 2){
            colunm -= 1;

            if (m_maze[line][colunm] == CellType::EMPTY || m_maze[line][colunm] == CellType::FOOD){
                teste = direction::LEFT;

                path_valid = true;
            }
        }


        else if (random == 3){
            colunm += 1;

            if (m_maze[line][colunm] == CellType::EMPTY || m_maze[line][colunm] == CellType::FOOD){
                teste = direction::RIGHT;

                path_valid = true;
            }
        }
        
    }

    if(size_body < snake_tail.size()){
        temp = snake_tail.front();
        snake_tail.pop();

        m_maze[temp.p_line][temp.p_column] = CellType::EMPTY;   
    }

    return teste;
}


void Level::snake_move(direction m_direction, size_t& size_body){

    Position temp; 
    temp.p_line = snake_head.p_line;
    temp.p_column = snake_head.p_column;
    snake_tail.push(temp);

    if(m_direction == direction::FORWARD){
        if(size_body > 1){
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_BODY;
        }
        else{
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;
        }

        snake_head.p_line -= 1;

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
        }

        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_FORWARD;
    }         





    else if(m_direction == direction::BACKWARD){
        if(size_body > 1){
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_BODY;
        }
        else{
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;
        }

        snake_head.p_line += 1;

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
        }

        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_BACKWARD;
    }





    else if(m_direction == direction::LEFT){

        if(size_body > 1){
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_BODY;
        }
        else{
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;
        }

        snake_head.p_column -= 1;

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
        }

        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_LEFT;
    }




    else if(m_direction == direction::RIGHT){

        if(size_body > 1){
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_BODY;
        }
        else{
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;
        }

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
        }
        snake_head.p_column += 1;

        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_RIGHT;
    }


    if(size_body < snake_tail.size()){
        temp = snake_tail.front();
        snake_tail.pop();

        m_maze[temp.p_line][temp.p_column] = CellType::EMPTY;   
    }
}


bool Level::isValid(int x, int y, int rows, int cols) {
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

Position Level::ret_spawn_position(){
    return spawn_point;
}