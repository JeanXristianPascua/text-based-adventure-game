# Template for CPSC2720 Major Project: Text Based Adventure Game
Last Updated: 2025-10-10 by Nicole Wilson [n.wilson@uleth.ca]

Notes:

* The Makefile and .gitlab-ci.yml files are set up to run on Ubuntu.
* The .gitlab-ci.yml file uses the targets in the Makefile.
* These are the tools/commands/apps used:
  * Compiler: g++ (C++ 14)
  * Style Check: cpplint
  * Static Check: cppcheck
  * Coverage Check: gcov/lcov
  * Memory Check: valgrind
  * Unit Test: gtest
  * Documentation: doxygen
* See the version report on the pipeline.

Certain assumptions have been made:
* One repo contains the files for one project.
* All unit testing files are found in <code>test/</code> including <code>main.cpp</code>.
* All header files for the project are found in <code>include/</code> and named <code>*.hpp</code>, every class must have a header file.
* All project source files for the project are named <code>*.cpp</code>.
  * Any needed source files that correspond to header files are found in <code>src/</code>.
  * There is a <code>main.cpp</code> found in <code>src/project/</code>.

### Team Contributions
- **Liam Jackson:** Implementation for core game logic - `Game`, `CommandExecutor`, `InputParser` etc. Module integration (Environment/Room, NPC, WorldObjects, etc). Unit tests.
- **Niko Stranzinger:** Implementation for `Inventory`, `Item`, and `NPC` logic. Design for game layout and team coordinator. Combined features.
- **Nick Tan:** Implementation for `Room`, `Exit`, and `Environment` (including derived classes). Assisted with game layout. Unit tests.
- **Jean Pascua:** Implementation for `WorldObject`, `Puzzle`, and both factory classes (`WorldObjectFactory`, `PuzzleFactory`). Debugged code. Unit tests.

