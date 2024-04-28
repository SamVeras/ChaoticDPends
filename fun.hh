#pragma once

namespace SM {
// Converte graus para radianos
float degrees_to_radians(float degrees);
// Converte radianos para graus
float radians_to_degrees(float radians);
// Retorna o ângulo na proporção entre dois outros (recebe graus, retorna radianos)
float angle_interpolate(float angle1, float angle2, float proportion);
}  // namespace SM
