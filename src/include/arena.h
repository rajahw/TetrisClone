#pragma once
#include "consts.h"

class Arena {
    public:
        Arena();
        void initialize();
        void draw();
        void testPrint();
        std::array<std::array<char, 10>, 20> body;
};