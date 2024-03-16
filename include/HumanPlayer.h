#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include <iostream>

class HumanPlayer : public Player {
public:
    using Player::Player;

    void makeMove(Board& board) override;

    void placeShips(Board& board) override;
};

#endif // HUMANPLAYER_H
