#ifndef _SIMULATION_H_
#define _SIMULATION_H_
#include "messages.h"

class SnazeSimulation {
private:

    bool game_over{false};
public:


    void initialize(int argc, char* agrv[]);
    bool is_over();
    void process_events();
    void render();
    void update();

};

#endif