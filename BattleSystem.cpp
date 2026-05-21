#include "BattleSystem.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <thread>

BattleSystem::BattleSystem(Player& p, Enemy& e)
    : player(p), enemy(e), turnCount(0), playerDefending(0), enemyDefending(0) {}

void BattleSystem::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void BattleSystem::displayBattleHeader() const {
    std::cout << "\n##########################################\n";
    std::cout << "#             BATTLE START                 #\n";
    std::cout << "############################################\n";
}

void BattleSystem::displayBattleStatus() const {
    std::cout << "\n" << std::string(40, '#') << "\n";
    std::cout << "TURN " << turnCount << "\n";
    std::cout << std::string(40, '#') << "\n";
    
    std::cout << "\n[YOUR STATUS]\n";
    std::cout << player.getName() << " HP: [";
    int healthBarLength = 20;
    int filledLength = (player.getCurrentHealth() * healthBarLength) / player.getMaxHealth();
    for (int i = 0; i < healthBarLength; ++i) {
        std::cout << (i < filledLength ? "#" : "#");
    }
    std::cout << "] " << player.getCurrentHealth() << "/" << player.getMaxHealth() << "\n";
    
    std::cout << "\n[ENEMY STATUS]\n";
    std::cout << enemy.getName() << " HP: [";
    filledLength = (enemy.getCurrentHealth() * healthBarLength) / enemy.getMaxHealth();
    for (int i = 0; i < healthBarLength; ++i) {
        std::cout << (i < filledLength ? "#" : "#");
    }
    std::cout << "] " << enemy.getCurrentHealth() << "/" << enemy.getMaxHealth() << "\n";
    std::cout << std::string(40, '#') << "\n";
}

void BattleSystem::displayBattleMenu() const {
    std::cout << "\n[YOUR TURN] Choose an action:\n";
    std::cout << "  [1] Attack\n";
    std::cout << "  [2] Defend\n";
    std::cout << "  [3] Use Item\n";
    std::cout << "  [4] View Stats\n";
    std::cout << "  [5] Escape\n";
    std::cout << "Enter choice (1-5): ";
}

CombatAction BattleSystem::getPlayerAction() {
    displayBattleMenu();
    
    int choice;
    while (true) {
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Try again: ";
            continue;
        }
        
        switch (choice) {
            case 1:
                return CombatAction::ATTACK;
            case 2:
                return CombatAction::DEFEND;
            case 3:
                return CombatAction::USE_ITEM;
            case 4:
                player.displayStats();
                displayBattleMenu();
                continue;
            case 5:
                return CombatAction::ESCAPE;
            default:
                std::cout << "Invalid choice. Try again: ";
        }
    }
}

int BattleSystem::getInventoryChoice() {
    player.getInventory().displayInventory();
    
    if (player.getInventory().getItemCount() == 0) {
        std::cout << "No items to use!\n";
        return -1;
    }
    
    std::cout << "Select item (1-" << player.getInventory().getItemCount() << "), or 0 to cancel: ";
    int choice;
    std::cin >> choice;
    
    if (choice < 1 || choice > player.getInventory().getItemCount()) {
        return -1;
    }
    
    return choice - 1;
}

void BattleSystem::playerAttack() {
    int damage = player.getAttack() + (rand() % 8 - 2);
    damage = std::max(1, damage);
    
    std::cout << "\n>>> " << player.getName() << " attacks for " << damage << " damage!\n";
    
    if (enemyDefending > 0) {
        damage = damage / 2;
        std::cout << ">>> Enemy defended! Damage reduced to " << damage << "!\n";
        enemyDefending = 0;
    }
    
    if (!enemy.takeDamage(damage)) {
        std::cout << ">>> Critical hit! " << enemy.getName() << " has been defeated!\n";
    }
}

void BattleSystem::playerDefend() {
    playerDefending = 1;
    std::cout << "\n>>> " << player.getName() << " takes a defensive stance!\n";
    std::cout << ">>> Next attack will deal 50% less damage!\n";
}

void BattleSystem::playerHeal() {
    if (player.getCurrentHealth() == player.getMaxHealth()) {
        std::cout << "\n>>> " << player.getName() << " is already at full health!\n";
        return;
    }
    
    int healAmount = 40 + (rand() % 20);
    player.heal(healAmount);
    std::cout << "\n>>> " << player.getName() << " uses magic to restore " << healAmount << " HP!\n";
    player.useMana(30);
}

void BattleSystem::playerUseItem() {
    int itemIndex = getInventoryChoice();
    
    if (itemIndex == -1) {
        return;
    }
    
    Item item = player.getInventory().useItem(itemIndex);
    std::cout << "\n>>> " << player.getName() << " uses " << item.getName() << "!\n";
    
    switch (item.getType()) {
        case ItemType::HEALTH_POTION:
            player.heal(item.getValue());
            std::cout << ">>> Restored " << item.getValue() << " HP!\n";
            break;
        case ItemType::MANA_POTION:
            player.restoreMana(item.getValue());
            std::cout << ">>> Restored " << item.getValue() << " Mana!\n";
            break;
        case ItemType::STRENGTH_BOOST:
            player.applyAttackBoost(item.getValue());
            std::cout << ">>> Attack increased by " << item.getValue() << "!\n";
            break;
        case ItemType::ARMOR_BOOST:
            player.applyDefenseBoost(item.getValue());
            std::cout << ">>> Defense increased by " << item.getValue() << "!\n";
            break;
    }
}

void BattleSystem::enemyTurn() {
    if (!enemy.isAlive()) return;
    
    std::cout << "\n--- " << enemy.getName() << "'s turn ---\n";
    
    int actionChoice = rand() % 100;
    
    if (enemy.getCurrentHealth() < enemy.getMaxHealth() / 3) {
        enemyDefending = 1;
        std::cout << ">>> " << enemy.getName() << " is in danger and defends!\n";
    } else if (actionChoice < 30 && enemy.getCurrentHealth() < enemy.getMaxHealth() / 2) {
        enemyDefending = 1;
        std::cout << ">>> " << enemy.getName() << " takes a defensive stance!\n";
    } else {
        int damage = enemy.calculateDamage();
        std::cout << ">>> " << enemy.getName() << " attacks for " << damage << " damage!\n";
        
        if (playerDefending > 0) {
            damage = damage / 2;
            std::cout << ">>> You defended! Damage reduced to " << damage << "!\n";
            playerDefending = 0;
        }
        
        player.takeDamage(damage);
    }
}

bool BattleSystem::isBattleOver() const {
    return !player.isAlive() || !enemy.isAlive();
}

void BattleSystem::handleVictory() {
    std::cout << "\n##########################################\n";
    std::cout << "#         *** VICTORY! ***               #\n";
    std::cout << "##########################################\n";
    
    std::cout << "\nYou have defeated " << enemy.getName() << "!\n";
    
    int expGain = enemy.getExperienceReward();
    std::cout << "You gained " << expGain << " experience points!\n";
    player.gainExperience(expGain);
    
    // Random item drop
    if ((rand() % 100) < enemy.getDropChance()) {
        int itemRoll = rand() % 4;
        Item droppedItem = Item::createHealthPotion();
        
        switch (itemRoll) {
            case 0:
                droppedItem = Item::createHealthPotion();
                break;
            case 1:
                droppedItem = Item::createManaPotion();
                break;
            case 2:
                droppedItem = Item::createStrengthBoost();
                break;
            case 3:
                droppedItem = Item::createArmorBoost();
                break;
        }
        
        if (player.getInventory().addItem(droppedItem)) {
            std::cout << "The enemy dropped: " << droppedItem.getName() << "!\n";
        }
    }
    
    player.clearBonuses();
}

void BattleSystem::handleDefeat() {
    std::cout << "\n##########################################\n";
    std::cout << "#         *** DEFEAT! ***                #\n";
    std::cout << "##########################################\n";
    std::cout << "\nYou have been defeated by " << enemy.getName() << "!\n";
}

BattleResult BattleSystem::startBattle() {
    clearScreen();
    displayBattleHeader();
    enemy.displayInfo();
    
    std::cout << "Press Enter to start battle...";
    std::cin.ignore();
    std::cin.ignore();
    
    turnCount = 0;
    playerDefending = 0;
    enemyDefending = 0;
    
    while (player.isAlive() && enemy.isAlive()) {
        turnCount++;
        clearScreen();
        displayBattleStatus();
        
        CombatAction action = getPlayerAction();
        clearScreen();
        
        switch (action) {
            case CombatAction::ATTACK:
                playerAttack();
                break;
            case CombatAction::DEFEND:
                playerDefend();
                break;
            case CombatAction::HEAL:
                playerHeal();
                break;
            case CombatAction::USE_ITEM:
                playerUseItem();
                break;
            case CombatAction::ESCAPE: {
                int escapeChance = 50 - (enemy.getLevel() * 5);
                if (rand() % 100 < escapeChance) {
                    std::cout << "\nYou successfully escaped from battle!\n";
                    return BattleResult::ESCAPED;
                } else {
                    std::cout << "\nEscape failed!\n";
                }
                break;
            }
        }
        
        if (isBattleOver()) break;
        
        enemyTurn();
        
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.ignore();
    }
    
    clearScreen();
    
    if (player.isAlive() && !enemy.isAlive()) {
        handleVictory();
        return BattleResult::PLAYER_VICTORY;
    } else {
        handleDefeat();
        return BattleResult::PLAYER_DEFEAT;
    }
}