/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */

#include "simulation.h"


int main(int argc, char* argv[]) {
  SnazeSimulation snaze;
  // SnazeSimulation is a singleton.
  //std::cout << argc << "e" << argv[1] << std::endl;
  snaze.initialize(argc, argv);
  //help_message();
  // The Game Loop.
  /*while (not snaze.is_over()) {
    snaze.process_events();
    snaze.update();
    snaze.render();
  }*/
  return 0;
}

