#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>
#include <utility>

class Player {
public:
    explicit Player(std::string name) : name(std::move(name)) {}

    virtual ~Player() = default;

    virtual void makeMove(Board &board) = 0;

    virtual void placeShips(Board& board) = 0;

    const std::string &getName() const { return name; }

protected:
    std::string name;
};

#endif // PLAYER_H