#include "GameManager.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

GameManager::GameManager()
    : player("Adventurer"), dungeon(25, 15, 1), gameState(GameState::RUNNING), currentDungeonLevel(1) {
    srand(static_cast<unsigned>(time(nullptr)));
    player.setPosition(1, 1);
}

void GameManager::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void GameManager::printWelcomeMessage() const {
    std::cout << "\n";
    std::cout << "##############################################################\n";
    std::cout << "#                                                            #\n";
    std::cout << "#            WELCOME TO DUNGEON RPG                          #\n";
    std::cout << "#                                                            #\n";
    std::cout << "#  Embark on an epic adventure through dark dungeons,        #\n";
    std::cout << "#  battle fearsome creatures, and become a legendary hero!   #\n";
    std::cout << "#                                                            #\n";
    std::cout << "##############################################################\n";
}

void GameManager::displayMainMenu() {
    clearScreen();
    printWelcomeMessage();
    
    std::cout << "\n##########################################\n";
    std::cout << "#           MAIN MENU                    #\n";
    std::cout << "##########################################\n";
    std::cout << "# [1] Start New Game                     #\n";
    std::cout << "# [2] View Instructions                  #\n";
    std::cout << "# [3] Exit                               #\n";
    std::cout << "##########################################\n";
    std::cout << "\nEnter choice (1-3): ";
    
    int choice;
    while (true) {
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Try again: ";
            continue;
        }
        
        if (choice >= 1 && choice <= 3) break;
        std::cout << "Invalid choice. Try again: ";
    }
    
    clearScreen();
    
    switch (choice) {
        case 1:{
            // Get player name
            std::cout << "Enter your character name: ";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            player = Player(name.empty() ? "Adventurer" : name);
            player.setPosition(1, 1);
            break;
        }
        case 2:{
            std::cout << "\n##########################################\n";
            std::cout << "#          HOW TO PLAY                   #\n";
            std::cout << "##########################################\n";
            std::cout << "# Move: WASD keys                        #\n";
            std::cout << "# Explore the dungeon to find enemies    #\n";
            std::cout << "# Battle enemies in turn-based combat    #\n";
            std::cout << "# Gain XP to level up and get stronger   #\n";
            std::cout << "# Collect items and treasures            #\n";
            std::cout << "# Defeat the boss to win the game        #\n";
            std::cout << "#                                        #\n";
            std::cout << "# Map Legend:                            #\n";
            std::cout << "#   @ = You                              #\n";
            std::cout << "#   E = Enemy                            #\n";
            std::cout << "#   B = Boss                             #\n";
            std::cout << "#   $ = Treasure                         #\n";
            std::cout << "#   + = Healing Shrine                   #\n";
            std::cout << "#   X = Dungeon Exit                     #\n";
            std::cout << "##########################################\n";
            std::cout << "\nPress Enter to return to menu...";
            std::cin.ignore();
            std::cin.ignore();
            displayMainMenu();
            break;
        }
        case 3:{
            exit(0);
        }
    }
}

void GameManager::displayGameUI() const {
    clearScreen();
    
    std::cout << "\n##########################################\n";
    std::cout << "# Dungeon Level: " << std::setw(3) << currentDungeonLevel 
              << "         | "<< player.getName() << "\n";
    std::cout << "##########################################\n";
    
    dungeon.displayMap(player.getX(), player.getY());
    dungeon.displayLegend();
    
    player.displayStatus();
    
    std::cout << "\n[CONTROLS] W/A/S/D to move | I = Inventory | C = Character | H = Help | Q = Quit\n";
}

void GameManager::handleTreasure() {
    std::cout << "\n##########################################\n";
    std::cout << "#     You found a treasure chest!        #\n";
    std::cout << "##########################################\n";
    
    int treasureRoll = rand() % 3;
    Item treasureItem = Item::createHealthPotion();
    
    switch (treasureRoll) {
        case 0:
            treasureItem = Item::createHealthPotion();
            break;
        case 1:
            treasureItem = Item::createStrengthBoost();
            break;
        case 2:
            treasureItem = Item::createArmorBoost();
            break;
    }
    
    if (player.getInventory().addItem(treasureItem)) {
        std::cout << "\nYou obtained: " << treasureItem.getName() << "\n";
    } else {
        std::cout << "\nYour inventory is full! Item left behind.\n";
    }
}

void GameManager::handleShrine() {
    std::cout << "\n##########################################\n";
    std::cout << "#   You found a healing shrine!          #\n";
    std::cout << "##########################################\n";
    
    int healAmount = 50;
    player.heal(healAmount);
    std::cout << "\nThe shrine restores " << healAmount << " HP!\n";
    std::cout << "Current Health: " << player.getCurrentHealth() << "/" << player.getMaxHealth() << "\n";
}

void GameManager::handleExit() {
    if (!dungeon.isBossDefeated()) {
        std::cout << "\n##########################################\n";
        std::cout << "#   The exit is sealed!                  #\n";
        std::cout << "#   You must defeat the boss first.      #\n";
        std::cout << "##########################################\n";
        return;
    }
    
    std::cout << "\n##########################################\n";
    std::cout << "#        YOU ESCAPED THE DUNGEON!        #\n";
    std::cout << "##########################################\n";
    
    if (currentDungeonLevel < 5) {
        std::cout << "\nNext level awaits... Descending deeper...\n";
        currentDungeonLevel++;
        dungeon = Dungeon(25, 15, currentDungeonLevel);
        player.setPosition(1, 1);
        player.clearBonuses();
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.ignore();
    } else {
        gameState = GameState::PLAYER_WON;
        printWinMessage();
    }
}

void GameManager::handleBoss() {
    std::cout << "\n##########################################\n";
    std::cout << "#    You have encountered the BOSS!      #\n";
    std::cout << "##########################################\n";
    
    Enemy* boss = dungeon.getBoss();
    BattleSystem battle(player, *boss);
    
    BattleResult result = battle.startBattle();
    
    if (result == BattleResult::PLAYER_VICTORY) {
        dungeon.defeatedBoss();
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.ignore();
    } else if (result == BattleResult::PLAYER_DEFEAT) {
        gameState = GameState::PLAYER_LOST;
    } else {
        // Escaped - shouldn't happen with boss but handle it
        std::cout << "\nYou managed to escape!\n";
    }
}

void GameManager::handleTileInteraction(TileType tile) {
    switch (tile) {
        case TileType::ENEMY: {
            Enemy* enemy = dungeon.getEnemyAt(player.getX(), player.getY());
            if (enemy) {
                BattleSystem battle(player, *enemy);
                BattleResult result = battle.startBattle();
                
                if (result == BattleResult::PLAYER_VICTORY) {
                    dungeon.removeEnemyAt(player.getX(), player.getY());
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.ignore();
                } else if (result == BattleResult::PLAYER_DEFEAT) {
                    gameState = GameState::PLAYER_LOST;
                }
            }
            break;
        }
        case TileType::TREASURE:
            handleTreasure();
            // Don't remove treasure yet - let player move away first
            break;
        case TileType::HEAL_SHRINE:
            handleShrine();
            break;
        case TileType::EXIT:
            handleExit();
            break;
        case TileType::BOSS:
            if (!dungeon.isBossDefeated()) {
                handleBoss();
            }
            break;
        default:
            break;
    }
}

void GameManager::handlePlayerInput() {
    char input;
    std::cin >> input;
    
    int newX = player.getX();
    int newY = player.getY();
    
    switch (tolower(input)) {
        case 'w':
            newY--;
            break;
        case 's':
            newY++;
            break;
        case 'a':
            newX--;
            break;
        case 'd':
            newX++;
            break;
        case 'i':
            player.getInventory().displayInventory();
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.ignore();
            return;
        case 'c':
            player.displayStats();
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.ignore();
            return;
        case 'h':
            std::cout << "\n[CONTROLS]\n";
            std::cout << "W/A/S/D - Move\n";
            std::cout << "I - Inventory\n";
            std::cout << "C - Character Stats\n";
            std::cout << "H - Help\n";
            std::cout << "Q - Quit Game\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.ignore();
            return;
        case 'q':
            gameState = GameState::PLAYER_LOST;
            return;
        default:
            return;
    }
    
    // Try to move
    if (dungeon.canMoveTo(newX, newY)) {
        player.setPosition(newX, newY);
        
        // Check for tile interaction
        TileType tileType = dungeon.checkTile(newX, newY);
        if (tileType != TileType::EMPTY && tileType != TileType::WALL) {
            handleTileInteraction(tileType);
        }
    } else {
        std::cout << "You cannot move into a wall!\n";
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.ignore();
    }
}

void GameManager::printGameOverMessage() const {
    std::cout << "\n##############################################################\n";
    std::cout << "#                                                            #\n";
    std::cout << "#                   GAME OVER                                #\n";
    std::cout << "#                                                            #\n";
    std::cout << "#  You have perished in the dungeon depths...                #\n";
    std::cout << "#                                                            #\n";
    std::cout << "#  Final Stats:                                              #\n";
    std::cout << "#    Level: " << std::setw(2) << player.getLevel() << "\n";
    std::cout << "#    Experience: " << std::setw(6) << player.getExperience() << "\n";
    std::cout << "#    Dungeon Level Reached: " << std::setw(2) << currentDungeonLevel << "\n";
    std::cout << "#                                                            #\n";
    std::cout << "##############################################################\n";
}

void GameManager::printWinMessage() const {
    std::cout << "\n##############################################################\n";
    std::cout << "#                                                            #\n";
    std::cout << "#                 YOU HAVE WON!                              #\n";
    std::cout << "#                                                            #\n";
    std::cout << "#  You have conquered all five dungeon levels and            #\n";
    std::cout << "#  defeated the Dark Lord! You are a legendary hero!         #\n";
    std::cout << "#                                                            #\n";
    std::cout << "#  Final Stats:                                              #\n";
    std::cout << "#    Level: " << std::setw(2) << player.getLevel() << "\n";
    std::cout << "#    Experience: " << std::setw(6) << player.getExperience() << "\n";
    std::cout << "#                                                            #\n";
    std::cout << "##############################################################\n";
}

void GameManager::start() {
    displayMainMenu();
}

void GameManager::run() {
    while (isGameRunning()) {
        displayGameUI();
        
        if (!player.isAlive()) {
            gameState = GameState::PLAYER_LOST;
            break;
        }
        
        handlePlayerInput();
    }
    
    clearScreen();
    
    if (gameState == GameState::PLAYER_LOST) {
        printGameOverMessage();
    } else if (gameState == GameState::PLAYER_WON) {
        printWinMessage();
    }
}