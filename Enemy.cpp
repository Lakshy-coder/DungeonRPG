#include "Enemy.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(const std::string& name, EnemyType type, int level)
    : name(name), type(type), level(level) {
    
    // Scale stats based on type and level
    switch (type) {
        case EnemyType::GOBLIN:
            maxHealth = 20 + (level * 5);
            attack = 8 + (level * 2);
            defense = 2 + (level);
            experienceReward = 25 * level;
            goldReward = 10 * level;
            dropChance = 30;
            break;
            
        case EnemyType::ORC:
            maxHealth = 35 + (level * 7);
            attack = 12 + (level * 3);
            defense = 4 + (level * 1.5);
            experienceReward = 40 * level;
            goldReward = 20 * level;
            dropChance = 35;
            break;
            
        case EnemyType::SKELETON:
            maxHealth = 25 + (level * 6);
            attack = 10 + (level * 2.5);
            defense = 3 + (level * 1);
            experienceReward = 35 * level;
            goldReward = 15 * level;
            dropChance = 40;
            break;
            
        case EnemyType::TROLL:
            maxHealth = 50 + (level * 10);
            attack = 15 + (level * 4);
            defense = 6 + (level * 2);
            experienceReward = 60 * level;
            goldReward = 30 * level;
            dropChance = 45;
            break;
            
        case EnemyType::SHADOW_BEAST:
            maxHealth = 40 + (level * 8);
            attack = 14 + (level * 3.5);
            defense = 5 + (level * 1.5);
            experienceReward = 50 * level;
            goldReward = 25 * level;
            dropChance = 50;
            break;
            
        case EnemyType::DRAGON:
            maxHealth = 80 + (level * 15);
            attack = 20 + (level * 5);
            defense = 8 + (level * 3);
            experienceReward = 100 * level;
            goldReward = 50 * level;
            dropChance = 60;
            break;
            
        case EnemyType::DARK_LORD:
            maxHealth = 150 + (level * 20);
            attack = 25 + (level * 6);
            defense = 10 + (level * 3);
            experienceReward = 200 * level;
            goldReward = 100 * level;
            dropChance = 80;
            break;
    }
    
    currentHealth = maxHealth;
}

int Enemy::calculateDamage() const {
    int variance = rand() % 6 - 2;  // -2 to +3
    return std::max(1, attack + variance);
}

bool Enemy::takeDamage(int damage) {
    int actualDamage = std::max(1, damage - defense / 2);
    currentHealth -= actualDamage;
    
    if (currentHealth <= 0) {
        currentHealth = 0;
        return false;
    }
    return true;
}

void Enemy::displayInfo() const {
    std::cout << "\n##########################################\n";
    std::cout << "# Enemy Encountered!                     #\n";
    std::cout << "##########################################\n";
    std::cout << "# " << std::left << std::setw(37) << name << "#\n";
    std::cout << "# Level: " << std::left << std::setw(31) << level << "#\n";
    std::cout << "# Health: " << std::left << std::setw(30) << (std::to_string(currentHealth) + "/" + std::to_string(maxHealth)) << "#\n";
    std::cout << "# Attack: " << std::left << std::setw(30) << attack << "#\n";
    std::cout << "# Defense: " << std::left << std::setw(29) << defense << "#\n";
    std::cout << "##########################################\n";
}

Enemy Enemy::createRandomEnemy(int dungeonLevel) {
    int enemyRoll = rand() % 100;
    EnemyType selectedType;
    
    // Probability increases for harder enemies as dungeon level increases
    if (dungeonLevel < 3) {
        if (enemyRoll < 50) selectedType = EnemyType::GOBLIN;
        else if (enemyRoll < 85) selectedType = EnemyType::SKELETON;
        else selectedType = EnemyType::ORC;
    } else if (dungeonLevel < 6) {
        if (enemyRoll < 30) selectedType = EnemyType::ORC;
        else if (enemyRoll < 60) selectedType = EnemyType::TROLL;
        else if (enemyRoll < 85) selectedType = EnemyType::SHADOW_BEAST;
        else selectedType = EnemyType::DRAGON;
    } else {
        if (enemyRoll < 20) selectedType = EnemyType::SHADOW_BEAST;
        else if (enemyRoll < 80) selectedType = EnemyType::DRAGON;
        else selectedType = EnemyType::DARK_LORD;
    }
    
    std::string enemyName;
    switch (selectedType) {
        case EnemyType::GOBLIN:
            enemyName = "Goblin Warrior";
            break;
        case EnemyType::ORC:
            enemyName = "Orc Barbarian";
            break;
        case EnemyType::SKELETON:
            enemyName = "Skeleton Knight";
            break;
        case EnemyType::TROLL:
            enemyName = "Stone Troll";
            break;
        case EnemyType::SHADOW_BEAST:
            enemyName = "Shadow Beast";
            break;
        case EnemyType::DRAGON:
            enemyName = "Red Dragon";
            break;
        case EnemyType::DARK_LORD:
            enemyName = "Dark Lord - BOSS";
            break;
        default:
            enemyName = "Unknown Enemy";
    }
    
    return Enemy(enemyName, selectedType, dungeonLevel);
}