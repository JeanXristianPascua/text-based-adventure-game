#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>
#include <vector>

class Room;

class Environment {
 protected:
    std::vector<Room*> rooms;
    std::string description;

 public:
    Environment(const std::string& description);
    virtual ~Environment();

    void addRoom(Room* room);
    std::vector<Room*> getRooms() const { return rooms; }
    std::string getDescription() const { return description; }

    virtual void generateRooms() = 0;
    Room* getRoomByName(const std::string& name) const;
};

// CastleMain - main castle area
class CastleMain : public Environment {
 public:
    CastleMain();
    void generateRooms() override;
};

// CastleDungeon - dungeon area
class CastleDungeon : public Environment {
 public:
    CastleDungeon();
    void generateRooms() override;
};

// CastleCourtyard - courtyard area
class CastleCourtyard : public Environment {
 public:
    CastleCourtyard();
    void generateRooms() override;
};

#endif  // ENVIRONMENT_HPP
