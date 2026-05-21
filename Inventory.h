#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<Item> items;
    int maxCapacity;

public:
    Inventory(int capacity = 10);
    
    bool addItem(const Item& item);
    bool removeItem(int index);
    Item* getItem(int index);
    void displayInventory() const;
    int getItemCount() const { return items.size(); }
    int getMaxCapacity() const { return maxCapacity; }
    bool hasSpace() const { return items.size() < maxCapacity; }
    
    Item useItem(int index);
    void clear() { items.clear(); }
};

#endif // INVENTORY_H