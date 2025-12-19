#ifndef GAME_HPP
#define GAME_HPP

#include <string>

class Player;
class GameState;
class InputParser;
class GameMap;
class CommandExecutor;

class Game {
 private:
    Player* player;
    GameMap* gameMap;
    GameState* gameState;
    InputParser* inputParser;
    CommandExecutor* commandExecutor;

    void initializeWorld();
    void gameLoop();
    void checkEndConditions();

 public:
    Game();
    ~Game();
    void start();
};

#endif  // GAME_HPP
