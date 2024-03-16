#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    using Player::Player;

    void makeMove(Board& enemyBoard) override {
        int x, y;
        std::cout << "Enter X and Y to shoot (0-" << Board::boardSize - 1 << "): ";
        std::cin >> x >> y;
        if (!enemyBoard.shoot(x, y)) {
            std::cout << "Try again." << std::endl;
        }
    }
};

#endif // HUMANPLAYER_H
