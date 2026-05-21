#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include <string>

class Player {
private:
    std::string name;
    int level;
    int experience;
    int experienceToLevel;
    
    int maxHealth;
    int currentHealth;
    int maxMana;
    int currentMana;
    
    int baseAttack;
    int baseDefense;
    int attackBonus;
    int defenseBonus;
    
    int x, y;  // Position in dungeon
    Inventory inventory;
    
    static const int BASE_EXP_REQUIREMENT = 100;

public:
    Player(const std::string& playerName);
    
    // Getters
    std::string getName() const { return name; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    int getExperienceToLevel() const { return experienceToLevel; }
    int getCurrentHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }
    int getCurrentMana() const { return currentMana; }
    int getMaxMana() const { return maxMana; }
    int getAttack() const { return baseAttack + attackBonus; }
    int getDefense() const { return baseDefense + defenseBonus; }
    int getX() const { return x; }
    int getY() const { return y; }
    Inventory& getInventory() { return inventory; }
    
    // Setters for position
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    
    // Health management
    bool takeDamage(int damage);
    void heal(int amount);
    bool isAlive() const { return currentHealth > 0; }
    
    // Mana management
    void useMana(int amount);
    void restoreMana(int amount);
    
    // Experience and leveling
    void gainExperience(int exp);
    bool levelUp();
    
    // Boost management
    void applyAttackBoost(int bonus) { attackBonus += bonus; }
    void applyDefenseBoost(int bonus) { defenseBonus += bonus; }
    void clearBonuses() { attackBonus = 0; defenseBonus = 0; }
    
    // Display
    void displayStats() const;
    void displayStatus() const;
    void addItem(const Item& item) { inventory.addItem(item); }
};

#endif // PLAYER_H