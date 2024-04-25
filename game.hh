#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#define ERROR_SDL_INIT_FAIL -1

namespace SM {

// Classe abstrata desenhável
class Drawable {
 public:
  void virtual update()                      = 0;
  void virtual draw(SDL_Renderer* ren) const = 0;
};

// Classe principal
class Game {
 protected:
  SDL_Window*   win;     // Pointer para a janela SDL
  SDL_Renderer* ren;     // Pointer para o renderizador SDL
  bool          paused;  // true se pausado; false caso contrário
  // Vetor de ponteiros únicos de objetos concretos desenháveis
  std::vector<std::unique_ptr<Drawable>> drawables;

  bool input();         // Retorna verdadeiro para terminar programa
  void toggle_pause();  // Inverte a propriedade de pausa

 public:
  // Adiciona ponteiro único para o vetor de objetos desenháveis
  void add_drawable(std::unique_ptr<Drawable> ptr);
  // Função principal a ser chamada pelo usuário, precisa ser definida
  void run();

  Game();
  ~Game();
};

void handle_error(int error_code, const char* message);

}  // namespace SM