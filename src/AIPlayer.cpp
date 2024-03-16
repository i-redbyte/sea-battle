#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <cstdlib>
#include <ctime>

class AIPlayer : public Player {
public:
    using Player::Player;

    void makeMove(Board& enemyBoard) override {
        std::srand(std::time(nullptr));
        int x = std::rand() % Board::boardSize;
        int y = std::rand() % Board::boardSize;
        enemyBoard.shoot(x, y);
    }
};

#endif // AIPLAYER_H
