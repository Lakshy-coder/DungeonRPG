#include "Player.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Player::Player(const std::string& playerName)
    : name(playerName), level(1), experience(0), experienceToLevel(BASE_EXP_REQUIREMENT),
      maxHealth(100), currentHealth(100), maxMana(50), currentMana(50),
      baseAttack(10), baseDefense(5), attackBonus(0), defenseBonus(0),
      x(0), y(0), inventory(10) {}

bool Player::takeDamage(int damage) {
    int actualDamage = std::max(1, damage - (baseDefense + defenseBonus) / 2);
    currentHealth -= actualDamage;
    
    if (currentHealth <= 0) {
        currentHealth = 0;
        return false;
    }
    return true;
}

void Player::heal(int amount) {
    currentHealth = std::min(currentHealth + amount, maxHealth);
}

void Player::useMana(int amount) {
    currentMana = std::max(0, currentMana - amount);
}

void Player::restoreMana(int amount) {
    currentMana = std::min(currentMana + amount, maxMana);
}

void Player::gainExperience(int exp) {
    experience += exp;
    
    while (experience >= experienceToLevel) {
        experience -= experienceToLevel;
        levelUp();
    }
}

bool Player::levelUp() {
    level++;
    maxHealth += 10;
    currentHealth = maxHealth;
    maxMana += 5;
    currentMana = maxMana;
    baseAttack += 3;
    baseDefense += 2;
    experienceToLevel = BASE_EXP_REQUIREMENT * level;
    
    std::cout << "\n##################### ####################\n";
    std::cout << "#           *** LEVEL UP! ***          #\n";
    std::cout << "#   You are now level " << std::setw(2) << level << "!              #\n";
    std::cout << "#   Stats increased!                    #\n";
    std::cout << "#########################################\n";
    
    return true;
}

void Player::displayStats() const {
    std::cout << "\n##########################################\n";
    std::cout << "#           CHARACTER STATS              #\n";
    std::cout << "##########################################\n";
    std::cout << "# Name:        " << std::left << std::setw(23) << name << "#\n";
    std::cout << "# Level:       " << std::left << std::setw(23) << level << "#\n";
    std::cout << "# Experience:  " << std::left << std::setw(10) << experience 
              << " / " << std::left << std::setw(10) << experienceToLevel << "#\n";
    std::cout << "##########################################\n";
    std::cout << "# Health:      " << std::left << std::setw(10) << currentHealth 
              << " / " << std::left << std::setw(10) << maxHealth << "#\n";
    std::cout << "# Mana:        " << std::left << std::setw(10) << currentMana 
              << " / " << std::left << std::setw(10) << maxMana << "#\n";
    std::cout << "# Attack:      " << std::left << std::setw(23) << (baseAttack + attackBonus) << "#\n";
    std::cout << "# Defense:     " << std::left << std::setw(23) << (baseDefense + defenseBonus) << "#\n";
    std::cout << "##########################################\n";
}

void Player::displayStatus() const {
    std::cout << "\n[" << name << "] Level " << level << " - HP: " << currentHealth << "/" << maxHealth 
              << " - Mana: " << currentMana << "/" << maxMana << " - XP: " << experience 
              << "/" << experienceToLevel << "\n";
}