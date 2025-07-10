#pragma once
#include "consts.h"
#include "arena.h"

class Block {
    public:
        std::array<std::vector<std::vector<char>>, 4> body;
        Vector2 position;
        Color color;
        int dimensions;
        int rotation;
        int arenaX;
        int arenaY;

        Block();
        void moveLeft();
        void moveRight();
        void moveDown();
        void draw();
        void rotateCounter();
        void rotateClockwise();
        virtual std::unique_ptr<Block> clone() = 0;
        virtual bool atLeft() = 0;
        virtual bool atRight() = 0;
        virtual bool atBottom() = 0;
        bool collidingLeft(const Arena&);
        bool collidingRight(const Arena&);
        bool collidingBottom(const Arena&);
        bool rotationIsPossible(const Arena&, const Offset&, int);
        virtual void counterKick(const Arena&, int);
        virtual void clockwiseKick(const Arena&, int);
};