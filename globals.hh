#pragma once

namespace SM {

const char* const TITLE = "Screen";    // Game title
const int SCR_W = 700;                 // Internal screen width
const int SCR_H = 700;                 // Internal screen height
const int SCR_SCALE = 1;               // Screen scaling factor
const int SCR_TW = SCR_W * SCR_SCALE;  // Scaled screen width
const int SCR_TH = SCR_H * SCR_SCALE;  // Scaled screen height
const int DELAY_MS = 10;               // Delay in milliseconds

const float TAU = 6.2831853071795864;
const float GRAVITY = 9.8 / 100;
const float DAMPING = 0.999;

}  // namespace SM