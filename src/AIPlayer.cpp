#include "AIPlayer.h"
#include <ctime>
#include <random>
#include <iostream>

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
    std::pair<int, int> bestMove = calculateBestMove(enemyBoard);
    int x = bestMove.first;
    int y = bestMove.second;
    std::cout << "Компьютер стреляет по координатам: (" << x << ", " << y << ")" << std::endl;
    enemyBoard.shoot(x, y);
}

std::pair<int, int> AIPlayer::calculateBestMove(Board& enemyBoard) {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<std::pair<int, int>> potentialMoves;
    for (int x = 0; x < enemyBoard.getSize(); ++x) {
        for (int y = 0; y < enemyBoard.getSize(); ++y) {
            if (!enemyBoard.hasBeenShot(x, y)) {
                if (enemyBoard.isNextToHit(x, y)) {
                    potentialMoves.emplace_back(x, y);
                }
            }
        }
    }

    if (potentialMoves.empty()) {
        for (int x = 0; x < enemyBoard.getSize(); ++x) {
            for (int y = 0; y < enemyBoard.getSize(); ++y) {
                if (!enemyBoard.hasBeenShot(x, y)) {
                    potentialMoves.emplace_back(x, y);
                }
            }
        }
    }

    std::uniform_int_distribution<> dis(0, potentialMoves.size() - 1);
    return potentialMoves[dis(gen)];
}


