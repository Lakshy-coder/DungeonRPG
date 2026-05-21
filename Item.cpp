#include "Item.h"

Item::Item(ItemType type, const std::string& name, const std::string& desc, int val)
    : type(type), name(name), description(desc), value(val) {}

Item Item::createHealthPotion() {
    return Item(ItemType::HEALTH_POTION, "Health Potion", "Restores 50 HP", 50);
}

Item Item::createManaPotion() {
    return Item(ItemType::MANA_POTION, "Mana Potion", "Restores 30 Mana", 30);
}

Item Item::createStrengthBoost() {
    return Item(ItemType::STRENGTH_BOOST, "Strength Elixir", "Increases attack by 5 for next battle", 5);
}

Item Item::createArmorBoost() {
    return Item(ItemType::ARMOR_BOOST, "Armor Tonic", "Increases defense by 3 for next battle", 3);
}