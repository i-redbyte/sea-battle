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

private:
    static std::pair<int, int> calculateBestMove(Board &enemyBoard);
};

#endif // AIPLAYER_H
