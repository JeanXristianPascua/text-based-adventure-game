#ifndef COMMAND_EXECUTOR_HPP
#define COMMAND_EXECUTOR_HPP

#include <string>
#include <vector>
#include "InputParser.hpp"

class Player;
class GameState;
class InputParser;

class CommandExecutor {
 private:
    Player* player;
    GameState* gameState;
    InputParser* inputParser;

    // Command handlers
    void executeMovement(const std::string& direction);
    void executeLook();
    void executeTake(const std::vector<std::string>& args);
    void executeUse(const std::vector<std::string>& args);
    void executeDrop(const std::vector<std::string>& args);
    void executeInteract(const std::vector<std::string>& args);
    void executeTalk(const std::vector<std::string>& args);
    void executeAnswer(const std::vector<std::string>& args);
    void executeInventory();
    void executeHelp();
    void executeQuit();

    // Helper methods
    void handleInteractionResult(const std::string& result);
    void unlockSecretChamberIfVictory();

 public:
    CommandExecutor(Player* player, GameState* gameState,
                   InputParser* inputParser);

    void executeCommand(const InputParser::Command& cmd);
};

#endif  // COMMAND_EXECUTOR_HPP
