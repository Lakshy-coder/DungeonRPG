# 🏰 Dungeon RPG - Terminal-Based RPG Game

A fully playable terminal-based Dungeon RPG built using **C++** and Object-Oriented Programming principles.

Explore dangerous dungeons, battle powerful enemies, collect loot, level up your character, and defeat bosses across multiple dungeon levels.

---

# 🚀 Features

## 🎮 Core Gameplay

- ASCII-based dungeon exploration
- Turn-based combat system
- Multiple enemy types and boss battles
- Experience and leveling system
- Health and mana mechanics
- Inventory and item system
- Random dungeon generation
- Healing shrines and treasure chests
- Multi-level progression system

---

# 🧠 DSA & Programming Concepts Used

This project demonstrates several important programming and DSA concepts:

- Object-Oriented Programming (OOP)
- 2D Grid / Matrix Handling
- Vectors (Dynamic Arrays)
- Maps / Associative Containers
- Game Loops & State Management
- Dynamic Memory Allocation
- Randomized procedural generation
- Input validation and control flow

I also explored concepts like **BFS, DFS, and tree-based logic** with the help of AI tools while learning how advanced game systems and traversal algorithms work internally.

---

# 🏗️ Project Architecture

The game follows a modular multi-file structure using separate classes for each major system.

## Main Components

### Player
Handles:
- Player stats
- Health and mana
- Inventory
- Experience and leveling

### Enemy
Handles:
- Enemy generation
- Enemy stats
- Scaling difficulty
- Combat behavior

### Dungeon
Handles:
- Dungeon map generation
- Tile placement
- Enemy positioning
- Collision and movement

### BattleSystem
Handles:
- Turn-based combat
- Damage calculations
- Battle actions
- Victory/defeat flow

### Inventory
Handles:
- Item storage
- Item usage
- Inventory display

### GameManager
Handles:
- Main game loop
- Menus
- Input handling
- Overall game orchestration

---

# 📂 Project Structure

```txt
DungeonRPG/
├── main.cpp
├── Player.h / Player.cpp
├── Enemy.h / Enemy.cpp
├── Dungeon.h / Dungeon.cpp
├── BattleSystem.h / BattleSystem.cpp
├── Inventory.h / Inventory.cpp
├── Item.h / Item.cpp
├── GameManager.h / GameManager.cpp
├── Makefile
└── README.md
```

---

# 🛠️ Tech Stack

- C++17
- STL (Standard Template Library)
- VS Code
- g++
- Makefile

---

# 🎮 Controls

| Key | Action |
|------|---------|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
| I | Open Inventory |
| C | Character Stats |
| H | Help |
| Q | Quit Game |

---

# 🗺️ Map Symbols

| Symbol | Meaning |
|--------|---------|
| @ | Player |
| E | Enemy |
| B | Boss |
| $ | Treasure |
| + | Healing Shrine |
| X | Exit |
| # | Wall |

---

# ⚔️ Combat System

When encountering enemies, the player can:

- Attack
- Defend
- Heal
- Use Items
- Escape

The combat system includes:
- Randomized damage
- Defense mechanics
- Item effects
- Enemy AI behavior

---

# 📈 Progression System

## Player Progression

- Gain XP by defeating enemies
- Level up to increase stats
- Improve attack and defense
- Unlock tougher dungeon levels

## Enemy Scaling

Enemies become stronger as dungeon levels increase.

Enemy Types:
- Goblin
- Orc
- Skeleton
- Troll
- Shadow Beast
- Dragon
- Dark Lord (Boss)

---

# 🎁 Item System

Available items include:

- Health Potion
- Mana Potion
- Strength Elixir
- Armor Tonic

Items provide temporary or permanent advantages during battles.

---

# ▶️ How to Run

## Compile

```bash
g++ *.cpp -o game
```

## Run

### Windows

```bash
.\game.exe
```

### Linux/macOS

```bash
./game
```

---

# 🔥 Future Improvements

Potential future features:

- Better enemy AI
- Procedural map generation
- Save/Load system
- Multiple character classes
- Equipment system
- Colored terminal graphics
- Advanced combat abilities
- Quest system

---

# 📚 Learning Outcome

This project helped me understand:

- How real game systems are structured
- Practical usage of DSA concepts
- Modular software architecture
- Game loop implementation
- State management
- OOP design in large projects

It was a great experience combining problem-solving, DSA, and practical game development together.

---

# 👨‍💻 Author

Lakshya Rana

---

# 📌 Note

This project was built for learning and portfolio purposes to demonstrate how DSA and Object-Oriented Programming concepts can be applied in real-world game development using C++.
