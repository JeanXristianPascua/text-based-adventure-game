#include "Item.hpp"

#include <string>

Item::Item(std::string id, std::string name, std::string description)
    : id(id), name(name), description(description) {}

std::string Item::getId() const { return id; }

std::string Item::getName() const { return name; }

bool Item::use(WorldObject* worldObject) {
    // TODO(Niko): Implement use on WorldObject
    // ljackson: temporary workaround for incomplete implementation
    return false;
}

bool Item::use(Exit* exit) {
    // TODO(Niko): Implement use on Exit
    // ljackson: temporary workaround for incomplete implementation
    return false;
}

std::string Item::examine() {
    // TODO(Niko): Implement examine
    return description;
}
