#ifndef MESSAGE_FORMATTER_HPP
#define MESSAGE_FORMATTER_HPP

#include <string>
#include <vector>

class Item;
class WorldObject;

class MessageFormatter {
 public:
    // Game messages
    static std::string welcomeMessage() {
        return "\nYou find yourself at the gates of a mysterious castle.\n"
               "Your goal: defeat the tyrannical King and escape!\n"
               "\nType 'help' for available commands.\n";
    }

    static std::string victoryBanner() {
        return "\nYou have defeated the King "
               "and discovered the secret chamber!\n"
               "The kingdom is finally free from tyranny."
               "You win!";
    }

    static std::string gameOverBanner() {
        return "\nYour adventure has come to an unfortunate end..."
               "You lose.";
    }

    // Room messages
    static std::string roomHeader(const std::string& roomName) {
        return "\n=== " + roomName + " ===\n";
    }

    static std::string itemsListHeader() {
        return "\nItems here:\n";
    }

    static std::string worldObjectsListHeader() {
        return "\nYou can see:\n";
    }

    static std::string exitsListHeader() {
        return "\nExits:\n";
    }

    static std::string itemEntry(const std::string& itemName) {
        return "  - " + itemName + "\n";
    }

    static std::string worldObjectEntry(const std::string& name,
                                        const std::string& description) {
        return "  - " + name + ": " + description + "\n";
    }

    static std::string exitEntry(const std::string& direction, bool locked) {
        std::string result = "  - " + direction;
        if (locked) {
            result += " (locked)";
        }
        return result + "\n";
    }

    // Player action messages
    static std::string pickupSuccess(const std::string& itemName) {
        return "You picked up the " + itemName + ".";
    }

    static std::string pickupAlreadyHave() {
        return "You already have that item.";
    }

    static std::string pickupNotFound(const std::string& itemName) {
        return "There is no " + itemName + " here.";
    }

    static std::string dropSuccess(const std::string& itemName) {
        return "You dropped the " + itemName + ".";
    }

    static std::string dropNotFound(const std::string& itemName) {
        return "You don't have a " + itemName + ".";
    }

    // Movement messages
    static std::string cannotGoThatWay() {
        return "You cannot go that way.";
    }

    static std::string exitLocked() {
        return "This exit is locked. ";
    }

    static std::string needKeyToUnlock() {
        return "You need something to unlock it.";
    }

    static std::string unlockSuccess(const std::string& itemName) {
        return "You unlock the exit with the " + itemName + ".";
    }

    static std::string unlockAlreadyUnlocked() {
        return "This exit is already unlocked.";
    }

    static std::string unlockWrongItem() {
        return "That item doesn't work here.";
    }

    // Inventory messages
    static std::string inventoryHeader() {
        return "\n=== Your Inventory ===";
    }

    static std::string inventoryEmpty() {
        return "Your inventory is empty.";
    }

    static std::string inventoryTotal(int count) {
        return "\nTotal items: " + std::to_string(count);
    }

    static std::string inventoryItemEntry(const std::string& name,
                                          const std::string& description) {
        return "  - " + name + "\n    " + description;
    }

    // Item combination messages
    static std::string itemCombinationSuccess(const std::string& item1,
                                             const std::string& item2,
                                             const std::string& result) {
        return "The poison from the flower seeps into the blade...\n"
               "Your " + item1 + " and " + item2 +
               " have combined into a " + result + "!\n"
               "This deadly weapon might be "
               "powerful enough to defeat the King.\n";
    }

    // Command error messages
    static std::string unknownCommand() {
        return "Unknown command. Type 'help' for available commands.";
    }

    static std::string invalidDirection() {
        return "Invalid direction. Use north, south, east, or west.";
    }

    static std::string takeWhat() {
        return "Take what?";
    }

    static std::string dropWhat() {
        return "Drop what?";
    }

    static std::string useItemUsage() {
        return "Usage: use <item> <target>";
    }

    static std::string interactWhat() {
        return "What do you want to interact with?";
    }

    static std::string notFound(const std::string& objectName) {
        return "There is no " + objectName + " here.";
    }

    static std::string youAreNowhere() {
        return "You are nowhere.";
    }

    static std::string noExitInDirection() {
        return "There is no exit in that direction.";
    }

    static std::string notSureHowToUse() {
        return "You're not sure how to use that.";
    }

    // Quit confirmation
    static std::string quitConfirmation() {
        return "Are you sure you want to quit? (y/n): ";
    }

 private:
    MessageFormatter() = delete;  // Utility class - no instantiation
};

#endif  // MESSAGE_FORMATTER_HPP
