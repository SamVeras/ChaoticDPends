#include "usefunctions.hh"
#include "globals.hh"

namespace SM {

float degree_to_radians(float dgr) {
  return dgr * (360 / SM::TAU);
};

}  // namespace SM