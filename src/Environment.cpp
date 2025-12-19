#include "Environment.hpp"

#include <algorithm>
#include <string>

#include "Direction.hpp"
#include "Exit.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "WorldObjectFactory.hpp"
#include "NPCFactory.hpp"

Environment::Environment(const std::string& description)
    : description(description) {}

Environment::~Environment() {
    for (Room* room : rooms) {
        delete room;
    }
}

void Environment::addRoom(Room* room) {
    if (room) {
        rooms.push_back(room);
    }
}

Room* Environment::getRoomByName(const std::string& name) const {
    auto it =
        std::find_if(rooms.begin(), rooms.end(), [&name](const Room* room) {
            return room->getName() == name;
        });
    return (it != rooms.end()) ? *it : nullptr;
}

// CastleMain Implementation
CastleMain::CastleMain() : Environment("The main castle halls and chambers") {}

void CastleMain::generateRooms() {
    // Room #4: Library (bottom left of main castle)
    Room* library = new Room("Library",
                             "Towering bookshelves filled with ancient tomes. "
                             "Dust motes dance in shafts of light.");

    // Add Book Pile WorldObject
    WorldObject* bookPile = WorldObjectFactory::createWorldObject("BookPile");
    library->addWorldObject(bookPile);

    // Add Mysterious Book WorldObject (deadly!)
    WorldObject* mysteriousBook =
        WorldObjectFactory::createWorldObject("MysteriousBook");
    library->addWorldObject(mysteriousBook);

    // Room #5: Courtyard (center of main castle)
    Room* courtyard = new Room("Courtyard",
                              "A large open courtyard paved with cobblestones. "
                              "A guard stands watch here, "
                              "looking somewhat distressed. "
                              "Training dummies and weapon "
                              "racks line one wall.");

    // Add Guard NPC
    NPC* guard = NPCFactory::createNPC("Guard");
    courtyard->addWorldObject(guard);

    // Room #7: Armory (top left of main castle)
    Room* armory = new Room("Armory",
                            "Racks of gleaming weapons and "
                            "suits of armor line the walls. "
                            "The scent of oiled metal fills the air. "
                            "A knight stands guard over the weapons.");

    // Add Knight NPC (will give sword after riddle)
    NPC* knight = NPCFactory::createNPC("Knight");
    armory->addWorldObject(knight);

    // Room #8: Throne Room (top center of main castle)
    Room* throneRoom =
        new Room("Throne Room",
                 "An impressive chamber with a raised throne at the far end. "
                 "Tapestries depicting ancient battles line the walls. "
                 "The King sits upon his throne, watching your every move.");

    // Add King NPC
    NPC* king = NPCFactory::createNPC("King");
    throneRoom->addWorldObject(king);

    // Room #9: Secret Chamber (top right of main castle)
    Room* secretChamber = new Room("Secret Chamber",
                                   "A hidden chamber behind a "
                                   "false wall in the throne room. "
                                   "Ancient treasures and mysterious "
                                   "artifacts glint in the torchlight. "
                                   "You have discovered the "
                                   "castle's greatest secret!");

    // Connect rooms according to PDF map

    // Library (#4) connections
    library->addExit(Direction::NORTH,
        armory, new Exit(armory, Direction::NORTH));
    library->addExit(Direction::EAST,
        courtyard, new Exit(courtyard, Direction::EAST));

    // Courtyard (#5) connections - CENTER HUB
    courtyard->addExit(Direction::WEST,
        library, new Exit(library, Direction::WEST));
    courtyard->addExit(Direction::NORTH,
        throneRoom, new Exit(throneRoom, Direction::NORTH));

    // Armory (#7) connections
    armory->addExit(Direction::SOUTH,
        library, new Exit(library, Direction::SOUTH));

    // Throne Room (#8) connections
    throneRoom->addExit(Direction::WEST,
        armory, new Exit(armory, Direction::WEST));
    throneRoom->addExit(Direction::SOUTH,
        courtyard, new Exit(courtyard, Direction::SOUTH));
    throneRoom->addExit(Direction::EAST, secretChamber,
                       new Exit(secretChamber, Direction::EAST,
                            true, "poison_sword",
                            "The King won't let you past.."));

    // Secret Chamber (#9) connections
    secretChamber->addExit(Direction::WEST,
        throneRoom, new Exit(throneRoom, Direction::WEST));

    // Add rooms to environment
    addRoom(library);
    addRoom(courtyard);
    addRoom(armory);
    addRoom(throneRoom);
    addRoom(secretChamber);
}

// CastleDungeon Implementation
CastleDungeon::CastleDungeon()
    : Environment("The dark dungeons beneath the castle") {}

void CastleDungeon::generateRooms() {
    // Room #6: Prison (right side of middle row)
    Room* prison = new Room("Prison",
                           "Rows of iron-barred cells line the dank corridor. "
                           "Most are empty, but one contains a weary prisoner. "
                           "The air is cold and smells of mildew.");

    // Add Prisoner NPC
    NPC* prisoner = NPCFactory::createNPC("Prisoner");
    prison->addWorldObject(prisoner);

    // Add room to environment
    addRoom(prison);
}

// CastleCourtyard Implementation (Outer area - bottom row)
CastleCourtyard::CastleCourtyard()
    : Environment("The outer courtyard and gardens") {}

void CastleCourtyard::generateRooms() {
    // Room #1: Garden (bottom left)
    Room* garden = new Room("Garden",
                            "An overgrown garden with "
                            "wild roses and tangled ivy. "
                            "A stone fountain sits at the center, "
                            "surrounded by lush greenery. "
                            "The air is fragrant with the scent of flowers.");

    // Add Fountain WorldObject (gives Poison Flower when interacted with)
    WorldObject* fountain = WorldObjectFactory::createWorldObject("Fountain");
    garden->addWorldObject(fountain);

    // Room #2: Main Gate (bottom center - START)
    Room* mainGate =
        new Room("Main Gate",
                 "The castle's imposing main entrance looms before you. "
                 "Heavy iron gates stand open, as if inviting you in. "
                 "Stone walls tower overhead, "
                 "and you can see the castle courtyard beyond.");

    // Room #3: Stables (bottom right)
    Room* stables = new Room("Stables",
                            "You enter the stables. "
                            "The smell of hay and horses fills the air. "
                            "A powerful war horse stands in one of "
                            "the stalls, eyeing you warily.");

    // Add Horse WorldObject (causes death if interacted with)
    WorldObject* horse = WorldObjectFactory::createWorldObject("Horse");
    stables->addWorldObject(horse);

    // Connect outer courtyard rooms (bottom row)

    // Garden (#1) connections
    garden->addExit(Direction::EAST,
        mainGate, new Exit(mainGate, Direction::EAST));

    // Main Gate (#2) connections - CENTER OF BOTTOM ROW
    mainGate->addExit(Direction::WEST,
        garden, new Exit(garden, Direction::WEST));
    mainGate->addExit(Direction::EAST,
        stables, new Exit(stables, Direction::EAST));

    // Stables (#3) connections
    stables->addExit(Direction::WEST,
        mainGate, new Exit(mainGate, Direction::WEST));

    // Add rooms to environment
    addRoom(garden);
    addRoom(mainGate);
    addRoom(stables);
}
