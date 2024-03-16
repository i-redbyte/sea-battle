#include "HumanPlayer.h"
#include <ctime>
#include <random>

//test function
void HumanPlayer::placeShips(Board& board) {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> shipLengths = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for (int length : shipLengths) {
        bool placed = false;
        while (!placed) {
            int x = gen() % board.getSize();
            int y = gen() % board.getSize();
            bool horizontal = gen() % 2 == 0;
            if (board.canPlaceShip(x, y, length, horizontal)) {
                board.placeShip(x, y, length, horizontal);
                placed = true;
            }
        }
    }
}

void HumanPlayer::makeMove(Board& enemyBoard) {
    bool hitAgain;
    do {
        int x, y;
        std::cout << "Введите X и Y для выстрела (0-" << enemyBoard.getSize() - 1 << "): ";
        std::cin >> x >> y;
        hitAgain = enemyBoard.shoot(x, y);
        if (!hitAgain) {
            std::cout << "Попробуйте еще раз." << std::endl;
            clearInputStream();
        }
    } while (hitAgain);
}
