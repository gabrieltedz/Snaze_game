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

// void Level::display_maze(){
//     std::cout << "display maze:" << std::endl;

//     CellType type;
//     char current_char;
//     for(int i{0}; i < m_lines; i++){

//         for (int j{0}; j < m_columns; j++){
//             type = m_maze[i][j];

//             switch(type){
//                 case (CellType::WALL):
//                 current_char = '#';
//                 break;

//                 case (CellType::INVISIBLE_WALL):
//                 current_char = '.';
//                 break;

//                 case (CellType::SPAWN_POINT):
//                 current_char = '&';
//                 break;

//                 case (CellType::EMPTY):
//                 current_char = ' ';
//                 break;
            
//                 // case(CellType::FOOD):
//                 // current_char = ' ';
//                 // break;

//                 // case(CellType::SNAKE_HEAD):
//                 // current_char = '^';
//                 // break;
//             }

//             std::cout << current_char;
//         } std::cout << std::endl;
//     }
// }

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

void Level::delete_food(){
    m_maze[m_pos_food.p_line][m_pos_food.p_column] = CellType::EMPTY;
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

std::queue<direction> Level::new_path(){
    std::queue<direction> teste;
    // teste.push(direction::LEFT);
    // teste.push(direction::BACKWARD);
    // teste.push(direction::RIGHT);
    // teste.push(direction::FORWARD);
    // teste.push(direction::LEFT);
    // teste.push(direction::BACKWARD);
    // teste.push(direction::RIGHT);
    // teste.push(direction::FORWARD);

    return teste;
}

direction Level::path_random(){
    direction teste;
    int random;
    bool path_valid{false};


    while(!path_valid){

        int colunm = snake_head.p_column;
        int line = snake_head.p_line;

        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 3);
        random = distribution(gen);

        if ((m_maze[line-1][colunm] == CellType::WALL || m_maze[line-1][colunm] == CellType::SNAKE_BODY)){
            if(m_maze[line+1][colunm] == CellType::WALL || m_maze[line+1][colunm] == CellType::SNAKE_BODY){
                if(m_maze[line][colunm-1] == CellType::WALL || m_maze[line][colunm-1] == CellType::SNAKE_BODY){
                    if(m_maze[line][colunm+1] == CellType::WALL || m_maze[line][colunm+1] == CellType::SNAKE_BODY){
                        random = 4;
                    }
                }
            }
        }


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
        
        else if(random == 4){
            teste = direction::UNDEFINED;
            m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;

            path_valid = true;
        }
    }


    return teste;
}

void Level::snake_move(direction m_direction, size_t& size_body, size_t& food){

    Position temp; 
    temp.p_line = snake_head.p_line;
    temp.p_column = snake_head.p_column;
    snake_tail.push(temp);


    if(size_body > 1){
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_BODY;
    }
    else if(size_body < 2){
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::EMPTY;
        
        
    }


        
    if(m_direction == direction::FORWARD){
        snake_head.p_line -= 1;

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
            food += 1;
        }
    }         
    else if(m_direction == direction::BACKWARD){
        snake_head.p_line += 1;

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
            food += 1;
        }
    }
    else if(m_direction == direction::LEFT){

        snake_head.p_column -= 1;

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
            food += 1;
        }
    }
    else if(m_direction == direction::RIGHT){
        snake_head.p_column += 1;

        if(m_maze[snake_head.p_line][snake_head.p_column] == CellType::FOOD){
            size_body += 1;
            food += 1;
        }
    }


    if(size_body <= snake_tail.size()){
        while (size_body <= snake_tail.size()){
            temp = snake_tail.front();
            snake_tail.pop();
            m_maze[temp.p_line][temp.p_column] = CellType::EMPTY;   
        } 

    }

    if(m_direction == direction::FORWARD){
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_FORWARD;
    }
    else if(m_direction == direction::BACKWARD){
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_BACKWARD;
    }
    else if(m_direction == direction::LEFT  ){
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_LEFT;
    }
    else if(  m_direction == direction::RIGHT){
        m_maze[snake_head.p_line][snake_head.p_column] = CellType::SNAKE_HEAD_RIGHT;
            
    }
    

}




Position Level::ret_spawn_position(){
    return spawn_point;
}