#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "Player.h"
#include "Enemy.h"

enum class CombatAction {
    ATTACK,
    DEFEND,
    HEAL,
    USE_ITEM,
    ESCAPE
};

enum class BattleResult {
    PLAYER_VICTORY,
    PLAYER_DEFEAT,
    ESCAPED
};

class BattleSystem {
private:
    Player& player;
    Enemy& enemy;
    int turnCount;
    int playerDefending;
    int enemyDefending;
    
    void displayBattleHeader() const;
    void displayBattleStatus() const;
    void displayBattleMenu() const;
    
    CombatAction getPlayerAction();
    int getInventoryChoice();
    
    void playerAttack();
    void playerDefend();
    void playerHeal();
    void playerUseItem();
    void enemyTurn();
    
    void handleVictory();
    void handleDefeat();

public:
    BattleSystem(Player& p, Enemy& e);
    
    BattleResult startBattle();
    bool isBattleOver() const;
    void clearScreen() const;
};

#endif // BATTLESYSTEM_H