#include "1.1_snakegame.h"

// Done

/**!
 *  This program implements the Snake simulation.
 *  @author Gabriel Victor da Silva
 *  @author Thiago Raquel
 */
int main(int argc, char* argv[]) {
  // Create object snaze from class SnakeGame
  SnakeGame snaze;

  // Read arguments from CLI, update starting game values and read level that will be played
  snaze.initialize(argc, argv);

  // Output intro message with atualized starting game values
  snaze.introduction_message();

  // The Game Loop.
  while (not snaze.is_over()) {
    snaze.process_events();
    snaze.update();
    snaze.render();
  }

  return 0;
}

