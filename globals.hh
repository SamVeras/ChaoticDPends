#pragma once

namespace SM {

const char* const TITLE     = "Screen";           // Game title
const int         SCR_W     = 1000;               // Internal screen width
const int         SCR_H     = 1000;               // Internal screen height
const int         SCR_SCALE = 1;                  // Screen scaling factor
const int         SCR_TW    = SCR_W * SCR_SCALE;  // Scaled screen width
const int         SCR_TH    = SCR_H * SCR_SCALE;  // Scaled screen height
const int         DELAY_MS  = 1;                  // Delay in milliseconds

const float TAU     = 6.28318530717958647692;
const float PI      = 3.14159265358979323846;
const float GRAVITY = 9.8 / 100;
const float DAMPING = 0.999;  // 0.999;

const unsigned int TRAIL_LIFETIME   = 30;
const unsigned int NUM_OF_PENDULUMS = 2000;

}  // namespace SM