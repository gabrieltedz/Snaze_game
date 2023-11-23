#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "../lib/text.color.h"


/**
 * @brief Struct to give the position of a specific cell, ex the snakes head, the spawnpoint, food etc
*/
struct Position {
    int p_line;
    int p_column;
    Position(int l = 0, int c = 0) : p_line(l), p_column(c) {}
};

/**
 * @brief Types of cells the game can have
*/
enum class CellType{
    EMPTY,
    WALL,
    INVISIBLE_WALL,
    SPAWN_POINT,
    SNAKE_HEAD,
    SNAKE_BODY,
    FOOD
};

class Level{
private:
    int m_lines;  //!< Number of lines the instance of level has
    int m_columns;    //!< Number of columns the instance of level has
    std::vector<std::vector<char>> m_map; //!< matrix of char that will be displayed
    std::vector<std::vector<CellType>> m_maze; //!< Maze with CellType for calculations
    Position spawn_point;
public:
    /**
     * @brief Contructor that initializes lines, columns and map
    */
    Level(int lines, int columns, std::vector<std::vector<char>> map) : m_lines(lines), m_columns(columns), m_map(map){}
    
    /**
     * @brief displays current level
    */
    void display();

    /**
     * @brief Reads a matrix of char and encodes it into the customized CellType maze setup
    */
    void read_level_maze();

    /**
     * @brief Display CellType matrix
    */
    void display_maze();


    /**
     * @brief Return spawn position of current level
    */
    Position ret_spawn_position();
};

#endif