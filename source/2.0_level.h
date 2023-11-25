#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>


#include "../lib/text.color.h"


/**
 * @brief Struct to give the position of a specific cell, ex the snakes head, the spawnpoint, food etc
*/
struct Position {
    int p_line;
    int p_column;
    int value{-3}; // If value == -3, it means the value of that position was untouched
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
    SNAKE_HEAD_FORWARD,
    SNAKE_HEAD_BACKWARD,
    SNAKE_HEAD_LEFT,
    SNAKE_HEAD_RIGHT,
    SNAKE_BODY,
    FOOD
};

enum class direction : uint {
    FORWARD = 0,                         //!< Represents the forward direction.
    BACKWARD,                            //!< Represents the backward direction.
    LEFT,                                //!< Represents the left direction.
    RIGHT                                //!< Represents the right direction.
};


class Level{
private:
    std::vector<std::vector<CellType>> m_maze; //!< Maze with CellType for calculations
public:
    Position spawn_point; 
    Position m_pos_food;
    Position snake_head; 
    std::queue<Position> snake_tail;


    int m_lines;  //!< Number of lines the instance of level has
    int m_columns;    //!< Number of columns the instance of level has

    std::vector<std::vector<char>> m_map; //!< matrix of char that will be displayed
    /**
     * @brief Contructor that initializes lines, columns and map
    */
    Level(int lines, int columns, std::vector<std::vector<char>> map) : m_lines(lines), m_columns(columns), m_map(map){}
     
    Level() = default;
    
    ~Level() = default;

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

    void display_run_game();

    void pos_new_food();

    void delete_food();

    void snake_move(direction m_direction, size_t& size_body);

    direction path_random(size_t& size_body);

    std::queue<direction> new_path();

    bool isValid(int x, int y, int rows, int cols);

    


    /**
     * @brief Return spawn position of current level
    */
    Position ret_spawn_position();
};

#endif