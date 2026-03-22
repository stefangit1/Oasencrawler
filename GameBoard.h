#ifndef OASENCRAWLER_GAMEBOARD_H
#define OASENCRAWLER_GAMEBOARD_H
#include "Coordinate.h"
#include "GameState.h"
#include "Tile.h"
#include "Item.h"


class GameBoard {
public:
    GameBoard();

    void printTile(Tile tile) const;
    void printBoard() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void foundDanger(Tile next);
    void foundRelic();
    void takeDamage();

    void resetBoard();
    void winGame();
    void loseGame();

    GameState getState() const;
    void setState(GameState newState);

    int getHealth() const;
    void setHealth(int newHealth);

    int getRelicsFound() const;
    int getDifficulty() const;

    char getItem(int index) const;
    void setItem(int index, Item newItem);

    void enemyMove();

private:
    Tile boardArray[5][5];
    Item inventory[3];

    int difficulty;
    int random;
    bool includesRelic;
    GameState gameState;

    Coordinate enemyCoord;
    Tile enemyTile;

    Coordinate playerCoord;
    int relicsFound;
    int health;
    int relicsAmount;
};


#endif //OASENCRAWLER_GAMEBOARD_H