#pragma once
#include "raylib.h"
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <string>

struct Offset {
    int x, y;
};

inline const int rows = 20;
inline const int columns = 10;
inline const int width = 800;
inline const int height = 1600;
inline const int size = 80;
inline double inputUpdate = 0.0;
inline double inputInterval = 0.06;
inline double downUpdate = 0.0;
inline double downInterval = 0.55;
inline double lockUpdate = 0.0;
inline double lockInterval = 1.0;
inline double clearUpdate = 0.0;
inline double clearInterval = 0.5;
inline double scoreMultiplier = 1.0;

inline Color gameOverScreen = {0, 0, 0, 200};
inline Rectangle yesHitbox = {130, 900, 220, 90};
inline Rectangle noHitbox = {130, 1000, 160, 90};
inline std::array<std::array<Offset, 5>, 4> counterOffset = {{
{{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}},
{{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}},
{{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}},
{{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}}
}};
inline std::array<std::array<Offset, 5>, 4> clockwiseOffset = {{
{{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}},
{{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}}},
{{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}},
{{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}}
}};
inline std::array<std::array<Offset, 5>, 4> ICounterOffset = {{
{{{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}}},
{{{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}},
{{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}}},
{{{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}}}
}};
inline std::array<std::array<Offset, 5>, 4> IClockwiseOffset = {{
{{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}}},
{{{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}}},
{{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}},
{{{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}}
}};
