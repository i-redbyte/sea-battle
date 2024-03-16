#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>

class Player {
public:
    Player(const std::string &name) : name(name) {}

    virtual ~Player() {}

    virtual void makeMove(Board &enemyBoard) = 0;

    const std::string &getName() const { return name; }

protected:
    std::string name;
};

#endif // PLAYER_H