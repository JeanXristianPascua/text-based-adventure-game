#include "CommandExecutor.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Player.hpp"
#include "GameState.hpp"
#include "InputParser.hpp"
#include "Room.hpp"
#include "WorldObject.hpp"
#include "Knight.hpp"
#include "Exit.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Direction.hpp"
#include "MessageFormatter.hpp"

CommandExecutor::CommandExecutor(Player* player, GameState* gameState,
                                 InputParser* inputParser)
    : player(player), gameState(gameState), inputParser(inputParser) {}

void CommandExecutor::executeCommand(const InputParser::Command& cmd) {
    if (cmd.action.empty()) {
        return;
    }

    // Movement commands
    if (cmd.action == "go" && !cmd.arguments.empty()) {
        executeMovement(cmd.arguments[0]);
    } else if (cmd.action == "n" || cmd.action == "north") {
        executeMovement("north");
    } else if (cmd.action == "s" || cmd.action == "south") {
        executeMovement("south");
    } else if (cmd.action == "e" || cmd.action == "east") {
        executeMovement("east");
    } else if (cmd.action == "w" || cmd.action == "west") {
        executeMovement("west");
    } else if (cmd.action == "look" || cmd.action == "l") {
        executeLook();
    } else if (cmd.action == "take" || cmd.action == "get" ||
               cmd.action == "pick") {
        executeTake(cmd.arguments);
    } else if (cmd.action == "use") {
        executeUse(cmd.arguments);
    } else if (cmd.action == "drop" || cmd.action == "d") {
        executeDrop(cmd.arguments);
    } else if (cmd.action == "interact" || cmd.action == "touch" ||
               cmd.action == "examine" || cmd.action == "search") {
        executeInteract(cmd.arguments);
    } else if (cmd.action == "talk" || cmd.action == "speak") {
        executeTalk(cmd.arguments);
    } else if (cmd.action == "answer") {
        executeAnswer(cmd.arguments);
    } else if (cmd.action == "inventory" || cmd.action == "i" ||
               cmd.action == "inv") {
        executeInventory();
    } else if (cmd.action == "help" || cmd.action == "h") {
        executeHelp();
    } else if (cmd.action == "quit" || cmd.action == "q" ||
               cmd.action == "exit") {
        executeQuit();
    } else {
        std::cout << MessageFormatter::unknownCommand() << std::endl;
    }
}

void CommandExecutor::executeMovement(const std::string& direction) {
    if (direction == "north" || direction == "n") {
        player->moveTo(NORTH);
    } else if (direction == "south" || direction == "s") {
        player->moveTo(SOUTH);
    } else if (direction == "east" || direction == "e") {
        player->moveTo(EAST);
    } else if (direction == "west" || direction == "w") {
        player->moveTo(WEST);
    } else {
        std::cout << MessageFormatter::invalidDirection() << std::endl;
    }
}

void CommandExecutor::executeLook() {
    player->look();
}

void CommandExecutor::executeTake(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << MessageFormatter::takeWhat() << std::endl;
    } else {
        std::string itemName = inputParser->combineArgs(args);
        player->pickUpItem(itemName);
    }
}

void CommandExecutor::executeUse(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << MessageFormatter::useItemUsage() << std::endl;
    } else {
        std::string target = args.back();
        std::vector<std::string> itemArgs(args.begin(), args.end() - 1);
        std::string itemName = inputParser->combineArgs(itemArgs);
        player->useItem(itemName, target);
    }
}

void CommandExecutor::executeDrop(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << MessageFormatter::dropWhat() << std::endl;
    } else {
        std::string itemName = inputParser->combineArgs(args);
        player->dropItem(itemName);
    }
}

void CommandExecutor::executeInteract(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << MessageFormatter::interactWhat() << std::endl;
        return;
    }

    std::string objectName = inputParser->combineArgs(args);
    Room* currentRoom = player->getCurrentRoom();
    if (!currentRoom) {
        return;
    }

    WorldObject* obj = currentRoom->getWorldObjectByName(objectName);
    if (obj) {
        std::string result = obj->interact(*player);
        handleInteractionResult(result);
    } else {
        std::cout << MessageFormatter::notFound(objectName) << std::endl;
    }
}

void CommandExecutor::executeTalk(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Talk to whom?" << std::endl;
        return;
    }

    std::string npcName = inputParser->combineArgs(args);
    Room* currentRoom = player->getCurrentRoom();
    if (!currentRoom) {
        return;
    }

    WorldObject* obj = currentRoom->getWorldObjectByName(npcName);
    if (obj) {
        std::string result = obj->interact(*player);
        handleInteractionResult(result);
    } else {
        std::cout << MessageFormatter::notFound(npcName) << std::endl;
    }
}

void CommandExecutor::executeAnswer(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Answer what?" << std::endl;
        return;
    }

    Room* currentRoom = player->getCurrentRoom();
    if (!currentRoom) {
        return;
    }

    WorldObject* knightObj = currentRoom->getWorldObjectByName("knight");
    if (!knightObj) {
        std::cout << "There's no riddle to answer here." << std::endl;
        return;
    }

    Knight* knight = dynamic_cast<Knight*>(knightObj);
    if (!knight) {
        std::cout << "There's no riddle to answer here." << std::endl;
        return;
    }

    std::string answer = inputParser->combineArgs(args);
    if (knight->solveRiddle(answer)) {
        std::cout << "\nThe knight's eyes light up!\n\n"
                  << "\"Correct! You are indeed wise.\"\n"
                  << std::endl;
        std::cout << knight->interact(*player) << std::endl;
        gameState->incrementPuzzlesSolved();
    } else {
        std::cout << "\nThe knight shakes his head.\n\n"
                  << "\"That is not the answer I seek.\n"
                  << "Think carefully and try again.\""
                  << std::endl;
    }
}

void CommandExecutor::executeInventory() {
    Inventory* inv = player->getInventory();
    std::cout << MessageFormatter::inventoryHeader() << std::endl;

    if (inv->isEmpty()) {
        std::cout << MessageFormatter::inventoryEmpty() << std::endl;
    } else {
        std::vector<Item*> items = inv->getAllItems();
        for (Item* item : items) {
            std::cout << MessageFormatter::inventoryItemEntry(
                item->getName(), item->examine()) << std::endl;
        }
        std::cout << MessageFormatter::inventoryTotal(inv->getItemCount())
                  << std::endl;
    }
}

void CommandExecutor::executeHelp() {
    inputParser->displayHelp();
}

void CommandExecutor::executeQuit() {
    std::cout << MessageFormatter::quitConfirmation();
    std::string confirm;
    std::getline(std::cin, confirm);
    if (confirm == "y" || confirm == "yes") {
        gameState->stop();
    }
}

void CommandExecutor::handleInteractionResult(const std::string& result) {
    // Check for death
    if (result.substr(0, 6) == "DEATH:") {
        std::string deathMessage = result.substr(6);
        std::cout << deathMessage << std::endl;
        gameState->setPlayerDeath(deathMessage);
        return;
    }

    // Check for victory
    if (result.substr(0, 8) == "VICTORY:") {
        std::string victoryMessage = result.substr(8);
        std::cout << victoryMessage << std::endl;
        unlockSecretChamberIfVictory();
        return;
    }

    // Normal interaction
    std::cout << result << std::endl;
}

void CommandExecutor::unlockSecretChamberIfVictory() {
    Room* currentRoom = player->getCurrentRoom();
    if (!currentRoom) {
        return;
    }

    Exit* secretExit = currentRoom->getExit(EAST);
    if (!secretExit) {
        return;
    }

    Inventory* inv = player->getInventory();
    if (inv->hasItem("poison_sword")) {
        Item& poisonSword = inv->getItem("poison_sword");
        secretExit->unlock(poisonSword);
    }
}
