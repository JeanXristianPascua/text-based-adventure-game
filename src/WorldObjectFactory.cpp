#include <string>
#include "WorldObjectFactory.hpp"

WorldObject* WorldObjectFactory::createWorldObject(const std::string& type) {
    if (type == "Fountain") {
        return new Fountain();
    } else if (type == "Horse") {
        return new Horse();
    } else if (type == "BookPile") {
        return new BookPile();
    } else if (type == "MysteriousBook") {
        return new MysteriousBook();
    } else {
        return nullptr;
    }
}
