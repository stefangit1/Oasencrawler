#include <iostream>

#include "GameBoard.h"

int main() {
    system("chcp 65001");
    GameBoard gameBoard;

    while (gameBoard.getState() == Playing) {
        std::cout << "\n\n\n\n\n\n\n";
        gameBoard.printBoard();

        char input;

        std::cout << "Health: " << gameBoard.getHealth()
                  << "\nRelics Found: " << gameBoard.getRelicsFound()
                  << "\nDifficulty: " << gameBoard.getDifficulty()
                  << "\nInventory: " << gameBoard.getItem(0) << " | " << gameBoard.getItem(1) << " | " << gameBoard.getItem(2) << std::endl;
        std::cout << "Enter Input:";
        std::cin >> input;

        switch (input) {
            case 'W':
            case 'w':
                gameBoard.moveUp();
                break;
            case 'S':
            case 's':
                gameBoard.moveDown();
                break;
            case 'D':
            case 'd':
                gameBoard.moveRight();
                break;
            case 'A':
            case 'a':
                gameBoard.moveLeft();
                break;
            default:
                std::cout << "Enter valid input" << std::endl;

        }

        if (gameBoard.getState() == Win) {
            gameBoard.resetBoard();
        } else if (gameBoard.getState() == Loss) {
            std::cout << "\n\n\n\n\n\n\n";
            gameBoard.printBoard();
            std::cout << "You lost!" << std::endl;
            std::cout << "Difficulty: " << gameBoard.getDifficulty() << std::endl;
        } else if (gameBoard.getState() == BlackJack) {
            if (gameBoard.getItem(0) != InstaBlackJack && gameBoard.getItem(1) != InstaBlackJack && gameBoard.getItem(2) != InstaBlackJack) {

                int card1 = std::rand() % 11 + 2;
                int card2 = std::rand() % 11 + 2;
                int card3 = 0;

                int dealer1 = std::rand() % 11 + 2;
                int dealer2 = std::rand() % 11 + 2;
                int dealer3 = std::rand() % 11 + 2;

                char blackjackInput;

                while (blackjackInput != 'h' && blackjackInput != 't') {
                    std::cout << "\n\n\n\n\n\n\n";
                    std::cout << "BLACKJACK (Dealer always draws 3 cards)\n\n";
                    std::cout << "Your cards:\n" << card1 << "\n" << card2 << "\n\n";
                    std::cout << "Dealer cards:\n" << dealer1 << "\n" << dealer2 << "\n\n";
                    std::cout << "(h)it or s(t)and: ";
                    std::cin >> blackjackInput;

                    switch (blackjackInput) {
                        case 'h':
                            card3 = std::rand() % 11 + 2;
                            break;
                        case 't':
                            break;
                        default:
                            std::cout << "Enter valid input" << std::endl;
                    }

                }

                std::cout << "Your total: " << card1 + card2 + card3 << std::endl;
                std::cout << "Dealer total: " << dealer1 + dealer2 + dealer3 << std::endl;

                if ((card1 + card2 + card3 > dealer1 + dealer2 + dealer3 && card1 + card2 + card3 <= 21) || dealer1 + dealer2 + dealer3 > 21)
                    std::cout << "You won at BlackJack!" << std::endl;
                else {
                    std::cout << "You lost at BlackJack! The dealer took away 1 health!" << std::endl;
                    gameBoard.takeDamage();
                }

                std::cout << "Enter anything to continue: ";
                std::cin >> blackjackInput;
                gameBoard.setState(Playing);
            } else {
                for (int i=0; i<3; i++) {
                    if (gameBoard.getItem(i) == InstaBlackJack) {
                        gameBoard.setItem(i, EmptyItem);
                        break;
                    }
                }
            }

        } else if (gameBoard.getState() == Roulette) {
            if (gameBoard.getItem(0) != ShowRouletteNumber && gameBoard.getItem(1) != ShowRouletteNumber && gameBoard.getItem(2) != ShowRouletteNumber) {
                std::cout << "\n\n\n\n\n\n\n";

                char rouletteinput;
                int rouletteNumber = std::rand() % 38;

                while (rouletteinput != 'o' && rouletteinput != 'e') {
                    std::cout << "\n\n\n\n\n\n\n";
                    std::cout << "ROULETTE: " << std::endl;
                    std::cout << "Choose (o)dd or (e)ven: \n\n\n";
                    std::cin >> rouletteinput;

                    std::cout << "Die Kugel landet auf: " << rouletteNumber << std::endl;

                    switch (rouletteinput) {
                        case 'o':
                            if (rouletteNumber % 2 == 1) std::cout << "You won at Roulette!" << std::endl;
                            else {
                                std::cout << "You lost at Roulette! The dealer took away 1 health!" << std::endl;
                                gameBoard.takeDamage();
                            }
                            break;
                        case 'e':
                            if (rouletteNumber % 2 == 0) std::cout << "You won at Roulette!" << std::endl;
                            else {
                                std::cout << "You lost at Roulette! The dealer took away 1 health!" << std::endl;
                                gameBoard.takeDamage();
                            }
                            break;
                    }

                }

                std::cout << "Enter anything to continue: ";
                std::cin >> rouletteinput;
                gameBoard.setState(Playing);
            } else {
                for (int i=0; i<3; i++) {
                    if (gameBoard.getItem(i) == ShowRouletteNumber) {
                        gameBoard.setItem(i, EmptyItem);
                        break;
                    }
                }
            }

        } else if (gameBoard.getState() == Slots) {
            if (gameBoard.getItem(0) != Jackpot && gameBoard.getItem(1) != Jackpot && gameBoard.getItem(2) != Jackpot) {
                std::cout << "\n\n\n\n\n\n\n";

                char slotsinput;
                int slotsSpinned = 0;
                int slot1 = 0, slot2 = 0, slot3 = 0;

                while (slotsSpinned < 3) {
                    std::cout << "\n\n\n\n\n\n\n";
                    std::cout << "SLOT MACHINE: " << std::endl;
                    std::cout << "==============" << std::endl;
                    std::cout << "| " << slot1 << " | " << slot2 << " | " << slot3 << " |" << std::endl;
                    std::cout << "==============" << std::endl;

                    std::cout << "Enter anything to spin: " << std::endl;
                    std::cin >> slotsinput;

                    slotsSpinned++;
                    if (slotsSpinned == 1) slot1 = std::rand() % 7 + 1;
                    if (slotsSpinned == 2) slot2 = std::rand() % 7 + 1;
                    if (slotsSpinned == 3) slot3 = std::rand() % 7 + 1;

                }

                std::cout << "\n\n\n\n\n\n\n";
                std::cout << "SLOT MACHINE: " << std::endl;
                std::cout << "==============" << std::endl;
                std::cout << "| " << slot1 << " | " << slot2 << " | " << slot3 << " |" << std::endl;
                std::cout << "==============" << std::endl;

                if (slot1 == slot2 && slot2 == slot3 && slot1 == slot3) {
                    std::cout << "!!!JACKPOT!!!" << std::endl;
                    std::cout << "You gained +1 Health!" << std::endl;
                    gameBoard.setHealth(gameBoard.getHealth() + 1);
                } else if (slot1 != slot2 && slot2 != slot3 && slot1 != slot3) {
                    std::cout << "You lost! The slot machine took away 1 health!" << std::endl;
                    gameBoard.takeDamage();
                } else {
                    std::cout << "Pair found! Nothing happened..." << std::endl;
                }

                std::cout << "Enter anything to continue: " << std::endl;
                std::cin >> slotsinput;
                gameBoard.setState(Playing);
            } else {
                for (int i=0; i<3; i++) {
                    if (gameBoard.getItem(i) == Jackpot) {
                        gameBoard.setItem(i, EmptyItem);
                        break;
                    }
                }
            }

        }

    }

    return 0;
}
