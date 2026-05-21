#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Dungeon.h"
#include "BattleSystem.h"

enum class GameState {
    RUNNING,
    PLAYER_WON,
    PLAYER_LOST
};

class GameManager {
private:
    Player player;
    Dungeon dungeon;
    GameState gameState;
    int currentDungeonLevel;
    
    void displayMainMenu();
    void displayGameUI() const;
    void handlePlayerInput();
    void handleTileInteraction(TileType tile);
    void handleTreasure();
    void handleShrine();
    void handleExit();
    void handleBoss();
    
    void clearScreen() const;
    void printWelcomeMessage() const;
    void printGameOverMessage() const;
    void printWinMessage() const;

public:
    GameManager();
    
    void start();
    void run();
    bool isGameRunning() const { return gameState == GameState::RUNNING; }
};

#endif // GAMEMANAGER_H