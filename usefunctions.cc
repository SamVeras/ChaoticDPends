#include "usefunctions.hh"
#include "globals.hh"

namespace SM {

float degree_to_radians(float dgr) {
  return dgr * (SM::TAU / 360);
};

}  // namespace SM