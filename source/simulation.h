#ifndef _SIMULATION_H_
#define _SIMULATION_H_
#include "messages.h"

class SnazeSimulation {
private:

    bool game_over{false};      // Is the game over?
    unsigned short fps;         // Numbers of frames per second
public:


    void initialize(int argc, char* argv[]);
    bool is_over();
    void process_events();
    void render();
    void update();

};

#endif