#include "fun.hh"
#include "globals.hh"

float SM::degrees_to_radians(float degrees) {
  return degrees * (SM::PI / 180.f);
}
float SM::radians_to_degrees(float radians) {
  return radians * (180.f / SM::PI);
}
float SM::angle_interpolate(float angle1, float angle2, float proportion) {
  if (0 > proportion && proportion > 1)
    return -33.333333;
  return angle1 + ((angle2 - angle1) * proportion);
}