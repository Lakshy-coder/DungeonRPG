#include "Inventory.h"
#include <iostream>
#include <iomanip>

Inventory::Inventory(int capacity) : maxCapacity(capacity) {}

bool Inventory::addItem(const Item& item) {
    if (items.size() < maxCapacity) {
        items.push_back(item);
        return true;
    }
    return false;
}

bool Inventory::removeItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
        return true;
    }
    return false;
}

Item* Inventory::getItem(int index) {
    if (index >= 0 && index < items.size()) {
        return &items[index];
    }
    return nullptr;
}

Item Inventory::useItem(int index) {
    if (index >= 0 && index < items.size()) {
        Item item = items[index];
        items.erase(items.begin() + index);
        return item;
    }
    return Item(ItemType::HEALTH_POTION, "None", "Empty", 0);
}

void Inventory::displayInventory() const {
    if (items.empty()) {
        std::cout << "\n#######################################\n";
        std::cout << "             INVENTORY (EMPTY)          \n";
        std::cout << "#######################################\n";
        return;
    }
    
    std::cout << "\n#######################################\n";
    std::cout << std::left << std::setw(40) << "INVENTORY (" + std::to_string(items.size()) + "/" + std::to_string(maxCapacity) + ")" << "\n";
    std::cout << "#######################################\n";
    
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << std::left << std::setw(20) << items[i].getName();
        std::cout << "- " << items[i].getDescription() << "\n";
    }
    
    std::cout << "#######################################\n";
}