#include "InputParser.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Item.hpp"
#include "Room.hpp"
#include "StringUtils.hpp"

std::string InputParser::toLower(const std::string& str) {
    return StringUtils::toLower(str);
}

std::vector<std::string> InputParser::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream stream(input);
    std::string token;

    while (stream >> token) {
        // Convert to lowercase
        tokens.push_back(toLower(token));
    }

    return tokens;
}

InputParser::Command InputParser::parseCommand(const std::string& input) {
    Command cmd;
    std::vector<std::string> tokens = tokenize(input);

    if (tokens.empty()) {
        cmd.action = "";
        return cmd;
    }

    cmd.action = tokens[0];

    // Add remaining tokens as arguments
    for (size_t i = 1; i < tokens.size(); ++i) {
        cmd.arguments.push_back(tokens[i]);
    }

    return cmd;
}

std::string InputParser::combineArgs(const std::vector<std::string>& args,
                                     size_t startIndex) {
    return StringUtils::join(args, " ", startIndex);
}

std::string InputParser::findBestItemMatch(const std::vector<std::string>& args,
                                           Room* room) {
    if (args.empty() || !room) {
        return "";
    }

    // Try full phrase first (e.g., "rusty key")
    std::string fullPhrase = combineArgs(args);

    // Try progressively shorter phrases
    for (size_t len = args.size(); len > 0; --len) {
        std::string phrase;
        for (size_t i = 0; i < len; ++i) {
            if (i > 0) phrase += " ";
            phrase += args[i];
        }

        if (len == args.size()) {
            return phrase;  // Return full phrase for exact match attempt
        }
    }

    return fullPhrase;
}

void InputParser::displayHelp() {
    std::cout << R"(
        Available commands:
        look / l          - Look around the current room
        go <direction>    - Move in a direction (north, south, east, west)
        n / s / e / w     - Shortcuts for moving north/south/east/west
        take <item>       - Pick up an item (e.g., 'take sword')
        
        interact <object> - Interact with objects/NPCs (e.g., 'interact fountain')
        talk <npc>        - Talk to an NPC (e.g., 'talk guard')
        search <object>   - Search objects (e.g., 'search pile of books')
        answer <answer>   - Answer a riddle (e.g., 'answer pencil')
        
        use <item> <target> - Use an item on something (e.g., 'use key east')
        drop <item>       - Drop an item on the ground
        inventory / i     - Show your inventory
        help / h          - Display this help message
        quit / q          - Quit the game
    )" << std::endl;
}
