#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <map>
#include <string>
#include <vector>
#include "Item.hpp"  // ljackson: include full definition instead of forward declaration

class Inventory {
 private:
    std::map<std::string, Item> items;  // map <itemid, item>

    // Check for item combinations and perform them
    std::string checkAndCombineItems();

 public:
    bool addItem(const Item& item);
    // ljackson: make itemId const since it's not modified
    bool hasItem(const std::string& itemId) const;
    Item& getItem(const std::string& itemId);
    // ljackson: access items by name
    bool hasItemByName(const std::string& itemName) const;
    Item* getItemByName(const std::string& itemName);
    bool removeItem(const std::string& itemId);

    // ljackson: new methods for inventory display
    bool isEmpty() const;
    std::vector<Item*> getAllItems();
    int getItemCount() const;

    // Called after adding items to check for combinations
    std::string processCombinations();
};

#endif
