#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include <iostream>
#include <string>

class Player;

class WorldObject {
 private:
    std::string name;
    std::string description;

 public:
    WorldObject(const std::string& name, const std::string& description)
        : name(name), description(description) {}
    virtual ~WorldObject() = default;
    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
    virtual std::string interact(const Player& player) = 0;
};

#endif  // WORLDOBJECT_HPP
