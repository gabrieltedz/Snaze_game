#ifndef _SIMULATION_H_
#define _SIMULATION_H_

/**
 * @brief Class that contains the simulator of the snaze game
*/
class SnazeSimulation {
private:

    bool game_over{false};      //!< Is the game over?
    unsigned short fps{4};      //!< Numbers of frames per second | Default = 4
    unsigned short lives{5};    //!< Lives the snake has | Default = 5
    unsigned short food{10};    //!< Quantity of food pellets for the entire simulation | Default = 10
public:
    /**
     * @brief Read arguments from CLI, update simulation values and read level that will be played
    */
    void initialize(int argc, char* argv[]);

    /**
     * @brief Function that returns if the game is over or not
    */
    bool is_over();
    void process_events();
    void render();
    void update();

    /**
     * @brief Return lives
    */
    unsigned short ret_lives();

    /**
     * @brief Help message
    */
    void help_message();

    /**
     * @brief Introduction message at the start of every game indicating authors, copyright, and in-game
     * values given by arguments via CLI
    */
    void introduction_message();
};

#endif