#include "fun.hh"
#include "globals.hh"

float SM::degrees_to_radians(float degrees) {
  return degrees * (SM::PI / 180.f);
};
float SM::radians_to_degrees(float radians) {
  return radians * (180.f / SM::PI);
};
