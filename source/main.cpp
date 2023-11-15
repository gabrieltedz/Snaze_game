#include "simulation.h"

/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */
int main(int argc, char* argv[]) {
  // Create object snaze from class SnazeSimulation
  SnazeSimulation snaze;

  // Read arguments from CLI, update starting game values and read level that will be played
  snaze.initialize(argc, argv);
  snaze.read_file();
  // Output intro message with atualized starting game values
  snaze.introduction_message();

  // The Game Loop.
  /*while (not snaze.is_over()) {
    snaze.process_events();
    snaze.update();
    snaze.render();
  }*/
  return 0;
}

