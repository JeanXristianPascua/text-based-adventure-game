#ifndef INPUTPARSER_HPP
#define INPUTPARSER_HPP

#include <string>
#include <vector>

class Room;

class InputParser {
 private:
    std::vector<std::string> tokenize(const std::string& input);
    std::string toLower(const std::string& str);

 public:
    struct Command {
        std::string action;
        std::vector<std::string> arguments;
    };

    Command parseCommand(const std::string& input);
    void displayHelp();

    // Item matching helpers
    std::string findBestItemMatch(const std::vector<std::string>& args,
                                  Room* room);
    std::string combineArgs(const std::vector<std::string>& args,
                            size_t startIndex = 0);
};

#endif
