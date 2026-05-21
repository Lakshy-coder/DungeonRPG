#ifndef ENEMY_H
#define ENEMY_H

#include <string>

enum class EnemyType {
    GOBLIN,
    ORC,
    SKELETON,
    DRAGON,
    TROLL,
    SHADOW_BEAST,
    DARK_LORD  // Boss
};

class Enemy {
protected:
    std::string name;
    EnemyType type;
    int level;
    
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
    
    int experienceReward;
    int goldReward;
    int dropChance;  // Percentage chance to drop item

public:
    Enemy(const std::string& name, EnemyType type, int level);
    virtual ~Enemy() = default;
    
    // Getters
    std::string getName() const { return name; }
    EnemyType getType() const { return type; }
    int getLevel() const { return level; }
    int getCurrentHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getExperienceReward() const { return experienceReward; }
    int getGoldReward() const { return goldReward; }
    int getDropChance() const { return dropChance; }
    
    // Combat
    int calculateDamage() const;
    bool takeDamage(int damage);
    bool isAlive() const { return currentHealth > 0; }
    
    // Display
    void displayInfo() const;
    
    // Factory method
    static Enemy createRandomEnemy(int dungeonLevel);
};

#endif // ENEMY_H