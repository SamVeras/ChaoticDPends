#include "game.hpp"

int main(void) {
  srand(time(NULL));  // Seeda o gerador de números aleatórios

  Game game;
  game.run();  // Ponto de entrada do jogo

  return 0;
}
