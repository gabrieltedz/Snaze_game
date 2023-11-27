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
    Position(int l = 0, int c = 0) : p_line(l), p_column(c) {}
};

    /**
     * @brief Enumeration representing types of cells in the game.
     */
    enum class CellType {
        EMPTY,            //!< Empty position.
        WALL,             //!< Wall.
        INVISIBLE_WALL,   //!< Invisible wall.
        SPAWN_POINT,      //!< Spawn point.
        SNAKE_HEAD_FORWARD, //!< Snake head facing forward.
        SNAKE_HEAD_BACKWARD, //!< Snake head facing backward.
        SNAKE_HEAD_LEFT,   //!< Snake head facing left.
        SNAKE_HEAD_RIGHT,  //!< Snake head facing right.
        SNAKE_BODY,        //!< Snake body.
        FOOD              //!< Food.
    };


enum class direction : uint {
    FORWARD = 0,                         //!< Represents the forward direction.
    BACKWARD = 1,                            //!< Represents the backward direction.
    LEFT = 2,                                //!< Represents the left direction.
    RIGHT = 3,                               //!< Represents the right direction.
    UNDEFINED = 4                            //!< Represents the undefined direction.
};


class Level{
private:
    std::vector<std::vector<CellType>> m_maze; //!< Maze with CellType for calculations
public:

    std::vector<std::vector<char>> m_map;   //!< matrix of char that will be displayed.
    Position spawn_point;                   //!< Position of the snake's spawn point.
    Position m_pos_food;                    //!< Current position of the food.
    Position snake_head;                    //!< Current position of the snake's head.
    std::queue<Position> snake_tail;        //!< Queue that stores the positions of the snake's tail.
    direction direction_prev;

    int m_lines;                            //!< Number of lines the instance of level has.
    int m_columns;                          //!< Number of columns the instance of level has.


    /**
     * @brief Contructor that initializes lines, columns and map
    */
    //Level(int lines, int columns, std::vector<std::vector<char>> map) : m_lines(lines), m_columns(columns), m_map(map){}
     
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

    /**
     * @brief Displays each frame of the running game.
     * 
     * This function is responsible for displaying each frame of the running game.
     */
    void display_run_game();

    /**
     * @brief Generates the position of a new food.
     * 
     * This function generates the position for a new food item in the game space.
     */
    void pos_new_food();

    /**
     * @brief Deletes the food item from the game space.
     * 
     * This function removes the food item from the game space.
     */
    void delete_food();

    /**
     * @brief Moves the snake in each frame.
     * 
     * This function handles the movement of the snake in each frame of the game.
     * 
     * @param m_direction The direction in which the snake should move.
     * @param size_body The size of the snake's body.
     * @param food The amount of food eaten by the snake.
     */
    void snake_move(direction m_direction, size_t& size_body, size_t& food);

    /**
     * @brief Resets the position and body of the snake.
     * 
     * This function resets the position and body of the snake.
     * 
     * @param size_body The size of the snake's body.
     */
    void reset_snake(size_t& size_body);

    /**
     * @brief Generates a random direction for the snake to follow.
     * 
     * This function generates a random direction for the snake to follow.
     * 
     * @return A randomly generated direction.
     */
    direction path_random();

    /**
     * @brief Generates a queue of instructions for the snake to follow aiming for the food.
     * 
     * This function generates a queue of instructions for the snake to follow with the goal of reaching the food.
     * 
     * @return A queue of directions to guide the snake towards the food.
     */
    std::queue<direction> new_path();


    /**
     * @brief Return spawn position of current level
    */
    Position ret_spawn_position();
};

#endif