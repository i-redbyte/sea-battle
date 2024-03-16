#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <cstdlib>
#include <ctime>

class AIPlayer : public Player {
public:
    using Player::Player;

    void makeMove(Board &board) override;

    void placeShips(Board &board) override;
};

#endif // AIPLAYER_H
