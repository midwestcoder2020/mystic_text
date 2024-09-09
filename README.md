# mystic_text


**mystic_text** is a customizable C++ framework for creating text-based RPGs and escape room games. It's designed for storytellers and game developers who want a versatile platform to build interactive narratives, puzzles, and adventures using straightforward C++ code.

## Features

- **Interactive Storytelling:** Create branching storylines and dialogue options.
- **Puzzle Mechanics:** Easily integrate custom puzzles and challenges.
- **Modular Design:** Add new levels, characters, and items with minimal coding.
- **Save and Load:** Built-in save/load functionality for players to resume their progress.
- **Cross-Platform:** Compatible with Windows, Linux, and macOS.

## Getting Started

### Prerequisites

- C++ compiler (e.g., GCC, Clang, MSVC)
- [CMake](https://cmake.org/) (optional, for building the project)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/TextQuest.git
    cd TextQuest
    ```

2. Build the project:

    - **Using C++ compiler:**

    ```bash
    g++ -o TextQuest game.cpp
    ```

3. Run the game:

    ```bash
    ./TextQuest
    ```

## Usage

To create your own adventure, modify the data.txt file. Use the provided templates to design your own rooms, puzzles, and characters.

### Example

```
# required items
# 1- title
# 2- setting
# 3- objective
# 4- list of locations which make up the main game loop
#
#
title:Test The Text based game Framework
setting:You are in a testing room and need to escape to pass the test.
objective:Explore the room to find a key, use the key and open the door to escape and win!.
#
# 
# format for locations
# <room/location name>|<locked status ie locked/unlocked>|<item required to open it>|
# list of items and their descriptions delimited by '_' and the item+descriptions separated by '-' |
#  <is it the end/final room ie yes/no> | <end game message>
#
#
location:test room|unlocked|n/a|key1-a key, which may be useful?|no|n/a
location:test hall|unlocked|n/a|flashlight-illuminates your surroundings!|no|n/a
location:test door|locked|key1|key2-might be useful!|no|door unlocked!
location:test end|locked|key1|none|no|the path is open now!
location:test escape|locked|key1|none|yes|congrats your made it!
```
