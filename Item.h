#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    HEALTH_POTION,
    MANA_POTION,
    STRENGTH_BOOST,
    ARMOR_BOOST
};

class Item {
private:
    ItemType type;
    std::string name;
    std::string description;
    int value;

public:
    Item(ItemType type, const std::string& name, const std::string& desc, int val);
    
    ItemType getType() const { return type; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    int getValue() const { return value; }
    
    static Item createHealthPotion();
    static Item createManaPotion();
    static Item createStrengthBoost();
    static Item createArmorBoost();
};

#endif // ITEM_H