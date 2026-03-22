#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

GameBoard::GameBoard() {
    std::srand(std::time(nullptr));

    inventory[0] = EmptyItem;
    inventory[1] = EmptyItem;
    inventory[2] = EmptyItem;

    playerCoord.x = 0;
    playerCoord.y = 0;

    enemyCoord.x = 4;
    enemyCoord.y = 4;
    enemyTile = Enemy;

    relicsFound = 0;
    health = 5;

    difficulty = 1;
    resetBoard();
}

void GameBoard::resetBoard() {
    includesRelic = false;
    relicsFound = 0;
    relicsAmount = 0;
    gameState = Playing;

    do {
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                random = std::rand() % (difficulty+9) + 1;
                if (x == playerCoord.x && y == playerCoord.y) boardArray[playerCoord.x][playerCoord.y] = Player;
                else if (x == enemyCoord.x && y == enemyCoord.y) boardArray[enemyCoord.x][enemyCoord.y] = Enemy;
                else if (random >= 1 && random <= 4) boardArray[x][y] = Empty;
                else if (random >= 5 && random <= difficulty+7) {
                    if (std::rand() % 3 + 1 == 1) boardArray[x][y] = BlackJackTile;
                    else if (std::rand() % 3 + 1 == 2) boardArray[x][y] = RouletteTile;
                    else if (std::rand() % 3 + 1 == 3) boardArray[x][y] = SlotsTile;
                }
                else if (random == difficulty+8) boardArray[x][y] = Well;
                else {
                    boardArray[x][y] = Relic;
                    includesRelic = true;
                    relicsAmount++;
                }
            }
        }
    } while (!includesRelic);
}

void GameBoard::printTile(Tile tile) const {
    switch (tile) {
        case Empty:
            std::cout << "  ";
            break;
        case BlackJackTile:
        case RouletteTile:
        case SlotsTile:
            std::cout << "! ";
            break;
        case Well:
            std::cout << "○ ";
            break;
        case Relic:
            std::cout << "♦ ";
            break;
        case Player:
            std::cout << "♟ ";
            break;
        case Enemy:
            std::cout << "☠ ";
            break;
    }
}

void GameBoard::printBoard() const {
    std::cout << "----------" << std::endl;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            printTile(boardArray[x][y]);
        }
        std::cout << std::endl;
    }
    std::cout << "----------" << std::endl;
}

void GameBoard::moveUp() {
    if (playerCoord.y <=0) return;

    Tile next = boardArray[playerCoord.x][playerCoord.y-1];

    boardArray[playerCoord.x][playerCoord.y] = Empty;
    playerCoord.y--;
    boardArray[playerCoord.x][playerCoord.y] = Player;

    enemyMove();

    if (next == BlackJackTile || next == RouletteTile || next == SlotsTile) foundDanger(next);
    else if (next == Relic) foundRelic();
    else if (next == Well) health++;
}

void GameBoard::moveDown() {
    if (playerCoord.y >= 4) return;

    Tile next = boardArray[playerCoord.x][playerCoord.y+1];

    boardArray[playerCoord.x][playerCoord.y] = Empty;
    playerCoord.y++;
    boardArray[playerCoord.x][playerCoord.y] = Player;

    enemyMove();

    if (next == BlackJackTile || next == RouletteTile || next == SlotsTile) foundDanger(next);
    else if (next == Relic) foundRelic();
    else if (next == Well) health++;
}

void GameBoard::moveLeft() {
    if (playerCoord.x <= 0) return;

    Tile next = boardArray[playerCoord.x-1][playerCoord.y];

    boardArray[playerCoord.x][playerCoord.y] = Empty;
    playerCoord.x--;
    boardArray[playerCoord.x][playerCoord.y] = Player;

    enemyMove();

    if (next == BlackJackTile || next == RouletteTile || next == SlotsTile) foundDanger(next);
    else if (next == Relic) foundRelic();
    else if (next == Well) health++;
}

void GameBoard::moveRight() {
    if (playerCoord.x >= 4) return;

    Tile next = boardArray[playerCoord.x+1][playerCoord.y];

    boardArray[playerCoord.x][playerCoord.y] = Empty;
    playerCoord.x++;
    boardArray[playerCoord.x][playerCoord.y] = Player;

    enemyMove();

    if (next == BlackJackTile || next == RouletteTile || next == SlotsTile) foundDanger(next);
    else if (next == Relic) foundRelic();
    else if (next == Well) health++;
}

void GameBoard::foundDanger(Tile next) {
    if (next == BlackJackTile) gameState = BlackJack;
    else if (next == RouletteTile) gameState = Roulette;
    else if (next == SlotsTile) gameState = Slots;

    random = std::rand() % 6 + 1;
    Item newItem = (random == 1) ? InstaBlackJack : (random == 2) ? ShowRouletteNumber : Jackpot;

    for (int i = 0; i < 3; i++) {
        if (inventory[i] == EmptyItem) {
            inventory[i] = newItem;
            break;
        }
    }
}

void GameBoard::takeDamage() {
    health--;
    if (health <= 0) loseGame();
}

void GameBoard::loseGame() {
    gameState = Loss;
}

void GameBoard::winGame() {
    difficulty++;
    gameState = Win;
}

void GameBoard::setState(GameState newState) {
    gameState = newState;
}

GameState GameBoard::getState() const {
    return gameState;
}

int GameBoard::getHealth() const {
    return health;
}

void GameBoard::setHealth(int newHealth) {
    health = newHealth;
}

int GameBoard::getRelicsFound() const {
    return relicsFound;
}

void GameBoard::foundRelic() {
    relicsFound++;
    if (relicsFound >= relicsAmount) winGame();
}

int GameBoard::getDifficulty() const {
    return difficulty;
}

char GameBoard::getItem(int index) const {
    if (inventory[index] == InstaBlackJack) return 'B';
    else if (inventory[index] == ShowRouletteNumber) return 'R';
    else if (inventory[index] == Jackpot) return 'S';
    return ' ';
}

void GameBoard::setItem(int index, Item newItem) {
    if (index > 2) return;

    inventory[index] = newItem;
}

void GameBoard::enemyMove() {
    boardArray[enemyCoord.x][enemyCoord.y] = (enemyTile != Enemy) ? enemyTile : Empty;

    if(std::rand() % 2 == 0) {
        if (enemyCoord.x < playerCoord.x) enemyCoord.x++;
        else if (enemyCoord.x > playerCoord.x) enemyCoord.x--;
    } else {
        if (enemyCoord.y < playerCoord.y) enemyCoord.y++;
        else if (enemyCoord.y > playerCoord.y) enemyCoord.y--;
    }

    enemyTile = boardArray[enemyCoord.x][enemyCoord.y];
    boardArray[enemyCoord.x][enemyCoord.y] = Enemy;

    if (enemyCoord.x == playerCoord.x && enemyCoord.y == playerCoord.y) gameState = Loss;
}
