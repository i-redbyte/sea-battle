#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "iostream"
#include "Player.h"
#include <Board.h>

class HumanPlayer : public Player {
public:
    using Player::Player;

    void makeMove(Board& board) override;

    void placeShips(Board& board) override;

    static void clearInputStream() { // move to utils
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

#endif // HUMANPLAYER_H
