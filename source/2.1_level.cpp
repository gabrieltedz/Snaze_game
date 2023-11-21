#include "2.0_level.h"

void Level::display(){
    for(int i{0}; i < m_lines; i++){
        for (int j{0}; j < m_columns; j++){
            std::cout << m_map[i][j];
        } std::cout << std::endl;
    }
}

void Level::read_level_maze(){

    char current_char;
    CellType type;

    /*for(int i{0}; i < m_lines; i++){

        for (int j{0}; j < m_columns;j++){
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
                break;

                case ' ':
                type = CellType::EMPTY;
                break;
            }

            m_maze[i].push_back(type);
        }
    }*/
}