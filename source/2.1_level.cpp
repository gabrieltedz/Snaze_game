#include "2.0_level.h"

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
                break;

                case ' ':
                type = CellType::EMPTY;
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
            
                case(CellType::FOOD):
                current_char = ' ';
                break;

                case(CellType::SNAKE_HEAD):
                current_char = '^';
                break;
            }

            std::cout << current_char;
        } std::cout << std::endl;
    }
}

Position Level::ret_spawn_position(){
    return spawn_point;
}