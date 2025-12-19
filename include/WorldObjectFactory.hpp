#ifndef WORLD_OBJECT_FACTORY_HPP
#define WORLD_OBJECT_FACTORY_HPP

#include <string>

#include "BookPile.hpp"
#include "Fountain.hpp"
#include "Horse.hpp"
#include "MysteriousBook.hpp"
#include "WorldObject.hpp"

class WorldObjectFactory {
 public:
    static WorldObject* createWorldObject(const std::string& type);
};

#endif  // WORLD_OBJECT_FACTORY_HPP
