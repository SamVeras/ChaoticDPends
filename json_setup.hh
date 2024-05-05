#include "game.hh"
#include "nlohmann/json.hpp"
#include "pendulum.hh"

class PendulumSetup : public SM::Drawable {
 private:
  std::vector<std::unique_ptr<SM::Pendulum>> pvector;

 public:
  // PendulumSetup() = default;
  PendulumSetup(nlohmann::json setup);
  void update() override;
  void draw(SDL_Renderer* ren) const override;
};