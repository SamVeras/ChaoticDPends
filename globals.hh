#pragma once

namespace SM {

const char *const TITLE = "Screen";    // Game title
const int SCR_W = 120;                 // Internal screen width
const int SCR_H = 120;                 // Internal screen height
const int SCR_SCALE = 5;               // Screen scaling factor
const int SCR_TW = SCR_W * SCR_SCALE;  // Scaled screen width
const int SCR_TH = SCR_H * SCR_SCALE;  // Scaled screen height
const int DELAY_MS = 10;               // Delay in milliseconds

}  // namespace SM