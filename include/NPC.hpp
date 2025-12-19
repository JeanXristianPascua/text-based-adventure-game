#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include "Inventory.hpp"
#include "WorldObject.hpp"

class NPC : public WorldObject {
 private:
    Inventory npcInventory;

 public:
    NPC(const std::string& name, const std::string& description)
        : WorldObject(name, description) {}

    bool addItem(const Item& item) {
        return npcInventory.addItem(item);
    }

    bool hasItem(const std::string& itemId) const {
        return npcInventory.hasItem(itemId);
    }

    Item& getItem(const std::string& itemId) { // get item by id
        return npcInventory.getItem(itemId);
    }

    bool removeItem(const std::string& itemId) { // remove item by id
        return npcInventory.removeItem(itemId);
    }

    std::string interact(const Player& player) override {
        return "Looks at you with curiosity.";
    }
};

#endif  // NPC_HPP
