#include "Inventory.hpp"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "Item.hpp"

bool Inventory::addItem(const Item& item) {
    std::string id = item.getId();

    if (items.find(id) != items.end()) {
        return false;  // item already exists
    }
    // ljackson: use emplace to construct Item in place
    items.emplace(id, item);
    return true;
}

// ljackson: make itemId const (not modified
bool Inventory::hasItem(const std::string& itemId) const {
    return items.find(itemId) != items.end();
}

// ljackson: improved
Item& Inventory::getItem(const std::string& itemId) {
    return items.at(itemId);
}

// ljackson: access items by name
bool Inventory::hasItemByName(const std::string& itemName) const {
    return std::any_of(
        items.begin(), items.end(), [&itemName](const auto& pair) {
            return pair.second.getName() == itemName;
        });
}

Item* Inventory::getItemByName(const std::string& itemName) {
    for (auto& pair : items) {
        if (pair.second.getName() == itemName) {
            return &pair.second;
        }
    }
    return nullptr;
}

// ljackson: remove item
bool Inventory::removeItem(const std::string& itemId) {
    auto it = items.find(itemId);
    if (it != items.end()) {
        items.erase(it);
        return true;
    }
    return false;
}

// ljackson: new methods for inv display
bool Inventory::isEmpty() const {
    return items.empty();
}

std::vector<Item*> Inventory::getAllItems() {
    std::vector<Item*> itemList;
    for (auto& pair : items) {
        itemList.push_back(&pair.second);
    }
    return itemList;
}

int Inventory::getItemCount() const {
    return items.size();
}

// ljackson: new method to combine items
std::string Inventory::checkAndCombineItems() {
    // Check for Sword + Poison Flower combination
    if (hasItem("sword") && hasItem("poison_flower")) {
        // Remove both items
        removeItem("sword");
        removeItem("poison_flower");
        // Create the Poison Sword
        Item poisonSword("poison_sword",
                        "Poison Sword",
                        "A deadly blade coated with toxic poison. "
                        "This weapon could fell even a king.");
        addItem(poisonSword);
        return "The poison from the flower seeps into the blade...\n"
               "Your Sword and Poison Flower "
               "have combined into a POISON SWORD!\n"
               "This deadly weapon might be powerful "
               "enough to defeat the King.\n";
    }

    return "";  // No combination occurred
}

std::string Inventory::processCombinations() {
    return checkAndCombineItems();
}
