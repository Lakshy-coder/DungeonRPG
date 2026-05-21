#include "Dungeon.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Dungeon::Dungeon(int w, int h, int level)
    : width(w), height(h), currentLevel(level), boss(nullptr), bossDefeated(false),
      bossX(-1), bossY(-1) {
    map.resize(height, std::vector<TileType>(width, TileType::EMPTY));
    generateLevel();
}

Dungeon::~Dungeon() {
    for (auto& pair : enemyLocations) {
        delete pair.second;
    }
    if (boss) delete boss;
}

void Dungeon::generateLevel() {
    // Clear previous data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            map[y][x] = TileType::EMPTY;
        }
    }
    enemyLocations.clear();
    
    placeTiles();
    placeEnemies();
    placeBoss();
}

void Dungeon::placeTiles() {
    // Place walls (creates a dungeon-like structure)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                map[y][x] = TileType::WALL;
            }
        }
    }
    
    // Place some interior walls randomly
    for (int i = 0; i < width * height / 20; ++i) {
        int x = 2 + rand() % (width - 4);
        int y = 2 + rand() % (height - 4);
        if (x > 1 && x < width - 2 && y > 1 && y < height - 2) {
            map[y][x] = TileType::WALL;
        }
    }
    
    // Place treasures and shrines
    for (int i = 0; i < 3; ++i) {
        int x = 2 + rand() % (width - 4);
        int y = 2 + rand() % (height - 4);
        if (map[y][x] == TileType::EMPTY) {
            map[y][x] = (rand() % 2 == 0) ? TileType::TREASURE : TileType::HEAL_SHRINE;
        }
    }
    
    // Place exit
    int exitX = 2 + rand() % (width - 4);
    int exitY = 2 + rand() % (height - 4);
    while (map[exitY][exitX] != TileType::EMPTY) {
        exitX = 2 + rand() % (width - 4);
        exitY = 2 + rand() % (height - 4);
    }
    map[exitY][exitX] = TileType::EXIT;
}

void Dungeon::placeEnemies() {
    int enemyCount = 3 + (currentLevel * 2);
    
    for (int i = 0; i < enemyCount; ++i) {
        int x = 2 + rand() % (width - 4);
        int y = 2 + rand() % (height - 4);
        
        if (map[y][x] == TileType::EMPTY && enemyLocations.find({x, y}) == enemyLocations.end()) {
            Enemy* newEnemy = new Enemy(Enemy::createRandomEnemy(currentLevel));
            enemyLocations[{x, y}] = newEnemy;
            map[y][x] = TileType::ENEMY;
        }
    }
}

void Dungeon::placeBoss() {
    if (boss) delete boss;
    boss = new Enemy(Enemy::createRandomEnemy(currentLevel + 2));
    
    int bossPlaced = false;
    while (!bossPlaced) {
        bossX = 2 + rand() % (width - 4);
        bossY = 2 + rand() % (height - 4);
        
        if (map[bossY][bossX] == TileType::EMPTY && !(bossX == 1 && bossY == 1)) {
            map[bossY][bossX] = TileType::BOSS;
            bossPlaced = true;
        }
    }
}

bool Dungeon::isValidPosition(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height && map[y][x] != TileType::WALL;
}

TileType Dungeon::getTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return map[y][x];
    }
    return TileType::WALL;
}

bool Dungeon::canMoveTo(int x, int y) const {
    return isValidPosition(x, y);
}

TileType Dungeon::checkTile(int x, int y) const {
    return getTile(x, y);
}

Enemy* Dungeon::getEnemyAt(int x, int y) {
    auto it = enemyLocations.find({x, y});
    if (it != enemyLocations.end()) {
        return it->second;
    }
    return nullptr;
}

void Dungeon::removeEnemyAt(int x, int y) {
    auto it = enemyLocations.find({x, y});
    if (it != enemyLocations.end()) {
        delete it->second;
        enemyLocations.erase(it);
        map[y][x] = TileType::EMPTY;
    }
}

void Dungeon::displayMap(int playerX, int playerY) const {
    std::cout << "\n#";
    for (int x = 0; x < width; ++x) std::cout << "#";
    std::cout << "#\n";
    
    for (int y = 0; y < height; ++y) {
        std::cout << "#";
        for (int x = 0; x < width; ++x) {
            if (playerX == x && playerY == y) {
                std::cout << "@";
            } else {
                switch (map[y][x]) {
                    case TileType::WALL:
                        std::cout << "#";
                        break;
                    case TileType::ENEMY:
                        std::cout << "E";
                        break;
                    case TileType::TREASURE:
                        std::cout << "$";
                        break;
                    case TileType::HEAL_SHRINE:
                        std::cout << "+";
                        break;
                    case TileType::BOSS:
                        std::cout << "B";
                        break;
                    case TileType::EXIT:
                        std::cout << "X";
                        break;
                    default:
                        std::cout << " ";
                }
            }
        }
        std::cout << "#\n";
    }
    
    std::cout << "#";
    for (int x = 0; x < width; ++x) std::cout << "#";
    std::cout << "#\n";
}

void Dungeon::displayLegend() const {
    std::cout << "\nLegend: @ Player | E Enemy | $ Treasure | + Shrine | B Boss | X Exit\n";
}