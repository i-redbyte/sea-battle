#include "AIPlayer.h"
#include <cstdlib>
#include <ctime>
#include <random>

void AIPlayer::placeShips(Board& board) {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> dis(0, board.getSize() - 1);
    std::uniform_int_distribution<> disBool(0, 1);
    std::vector<int> shipLengths = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    for (int length : shipLengths) {
        bool placed = false;
        while (!placed) {
            int x = dis(gen);
            int y = dis(gen);
            bool horizontal = disBool(gen) == 1;

            if (board.canPlaceShip(x, y, length, horizontal)) {
                board.placeShip(x, y, length, horizontal);
                placed = true;
            }
        }
    }
}


void AIPlayer::makeMove(Board& enemyBoard) {
    bool hitAgain;
    do {
        int x = std::rand() % enemyBoard.getSize();
        int y = std::rand() % enemyBoard.getSize();
        hitAgain = enemyBoard.shoot(x, y);
    } while (hitAgain);
}

