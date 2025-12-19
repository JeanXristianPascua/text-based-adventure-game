#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
class WorldObject;
class Exit;

class Item {
 private:
    std::string id;
    std::string name;
    std::string description;

 public:
    Item(std::string id, std::string name, std::string description);
    bool use(WorldObject*);
    bool use(Exit*);
    std::string examine();  // returns description i think
    std::string getId() const;
    std::string getName() const;
};

#endif
