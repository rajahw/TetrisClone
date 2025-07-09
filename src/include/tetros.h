#pragma once
#include "consts.h"
#include "block.h"

class OBlock : public Block {
    public:
        OBlock();
        std::unique_ptr<Block> clone() override;
        bool atLeft() override;
        bool atRight() override;
        bool atBottom() override;
        void counterKick(const Arena&, int) override;
        void clockwiseKick(const Arena&, int) override;
};

class IBlock : public Block {
    public:
        IBlock();
        std::unique_ptr<Block> clone() override;
        bool atLeft() override;
        bool atRight() override;
        bool atBottom() override;
        void counterKick(const Arena&, int) override;
        void clockwiseKick(const Arena&, int) override;
};

class SBlock : public Block {
    public:
        SBlock();
        std::unique_ptr<Block> clone() override;
        bool atLeft() override;
        bool atRight() override;
        bool atBottom() override;
};

class ZBlock : public Block {
    public:
        ZBlock();
        std::unique_ptr<Block> clone() override;
        bool atLeft() override;
        bool atRight() override;
        bool atBottom() override;
};

class LBlock : public Block {
    public:
        LBlock();
        std::unique_ptr<Block> clone() override;
        bool atLeft() override;
        bool atRight() override;
        bool atBottom() override;
};

class JBlock : public Block {
    public:
        JBlock();
        std::unique_ptr<Block> clone() override;
        bool atLeft() override;
        bool atRight() override;
        bool atBottom() override;
};

class TBlock : public Block {
    public:
        TBlock();
        std::unique_ptr<Block> clone() override;
        bool atLeft() override;
        bool atRight() override;
        bool atBottom() override;
};