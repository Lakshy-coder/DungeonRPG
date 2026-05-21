#ifndef DUNGEON_H
#define DUNGEON_H

#include "Enemy.h"
#include <vector>
#include <map>

enum class TileType {
    EMPTY,
    WALL,
    ENEMY,
    TREASURE,
    HEAL_SHRINE,
    BOSS,
    EXIT
};

class Dungeon {
private:
    int width;
    int height;
    int currentLevel;
    std::vector<std::vector<TileType>> map;
    std::map<std::pair<int, int>, Enemy*> enemyLocations;
    
    int bossX, bossY;
    Enemy* boss;
    bool bossDefeated;
    
    void generateLevel();
    void placeTiles();
    void placeEnemies();
    void placeBoss();
    bool isValidPosition(int x, int y) const;
    TileType getTile(int x, int y) const;

public:
    Dungeon(int w, int h, int level);
    ~Dungeon();
    
    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getCurrentLevel() const { return currentLevel; }
    bool isBossDefeated() const { return bossDefeated; }
    
    // Movement and interaction
    bool canMoveTo(int x, int y) const;
    TileType checkTile(int x, int y) const;
    Enemy* getEnemyAt(int x, int y);
    void removeEnemyAt(int x, int y);
    
    // Boss management
    Enemy* getBoss() const { return boss; }
    bool isBossLocation(int x, int y) const { return x == bossX && y == bossY; }
    void defeatedBoss() { bossDefeated = true; }
    
    // Display
    void displayMap(int playerX, int playerY) const;
    void displayLegend() const;
};

#endif // DUNGEON_H