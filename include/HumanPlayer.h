#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include <iostream>

class HumanPlayer : public Player {
public:
    using Player::Player;

    void makeMove(Board& board) override {
        int x, y;
        std::cout << "Введите X и Y для выстрела (0-" << board.getSize() - 1 << "): ";
        std::cin >> x >> y;
        if (!board.shoot(x, y)) {
            std::cout << "Попробуйте еще раз." << std::endl;
        }
    }

    void placeShips(Board& board) override;
};

#endif // HUMANPLAYER_H
