# Shapes War 🎮

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.6.1-8CC445?style=for-the-badge&logo=sfml&logoColor=white)

A modern arcade shooter built with C++ and SFML, featuring an Entity-Component System (ECS) architecture and fully config-driven gameplay.

---

## 📋 Table of Contents

- [🎥 Demo Video](#-demo-video)
- [✨ Features](#-features)
- [🛠️ Technologies Used](#-Technologies-Used)
- [📦 Prerequisites](#-prerequisites)
- [🚀 Setup & Installation](#-setup--installation)
- [🎮 How to Run](#-how-to-run)
- [⌨️ Controls](#-controls)
- [📂 Project Structure](#-project-structure)
- [🎯 Gameplay Mechanics](#-gameplay-mechanics)
- [📄 License](#-license)
- [🙏 Acknowledgments](#-acknowledgments)

---

## 🎥 Demo Video

> **Note**: A full gameplay demonstration will be linked here soon.

[![Shapes War Demo](https://img.youtube.com/vi/VIDEO_ID/0.jpg)](https://github.com/amr10w/ShapesWar-SFML/blob/main/assets/78f27128-e9cc-45be-879a-2d1fe6cc0efe)

---

## ✨ Features

- **Custom ECS Engine**: Modular design using a custom Entity-Component System for high performance.
- **Dynamic Enemy System**: Randomly generated enemies with varying polygon shapes (3-8 sides) and randomized velocities.
- **Config-Driven Gameplay**: All balance parameters (speed, size, colors, spawn rates) are loaded from an external text file.
- **Special Weaponry**: High-score reward mechanics that unlock powerful radial blast attacks.
- **Smooth Collision Logic**: Circle-based bounding volumes for accurate hit detection between all game entities.
---

## 🛠️ Technologies Used

- **Language**: C++17
- **Graphics & Input**: SFML 2.6.1 (Simple and Fast Multimedia Library)
- **Build System**: CMake 3.14+
- **Compiler**: MinGW-w64 (GCC)

---

## 📦 Prerequisites

Ensure you have the following installed to build the project from source:

| Requirement | Purpose | Download Link |
| :--- | :--- | :--- |
| **Git** | Version Control | [git-scm.com](https://git-scm.com/) |
| **CMake** | Build Management | [cmake.org](https://cmake.org/) |
| **MinGW-w64** | C++ Compiler | [winlibs.com](https://winlibs.com/) |
| **VS Code** | Development IDE | [code.visualstudio.com](https://code.visualstudio.com/) |

> **Note**: SFML is automatically downloaded and configured by CMake using `FetchContent`, so you don't need to install it manually.
-- 
### Verifying Installation

After installation, verify each tool is accessible from the command line:

```bash
git --version
cmake --version
g++ --version
mingw32-make --version
```

---

## 🚀 Setup & Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/amr10w/ShapesWar-SFML.git
   cd ShapesWar-SFML
   ```

2. **Open in VS Code**:
   - Launch VS Code and open the project folder
   - Ensure you have the **C++** and **CMake Tools** extensions installed

3. **Configure the Project**:
   - Press `Ctrl + Shift + P` and type **CMake: Configure**
   - Select your MinGW kit from the list (e.g., GCC 13.x.x)

---

## 🎮 How to Run

1. **Build**: Press `F7` or click the **Build** button in the status bar

2. **Run**: Press `Ctrl + F5` or click the **Play** button in the status bar

> The build system automatically copies DLLs and assets into the output folder for you.

**Alternatively**, run from terminal:
```bash
.\build\ShapeWar.exe
```

---

## 🎮 Controls

| Input | Action |
|-------|--------|
| `W` | Move Up |
| `A` | Move Left |
| `S` | Move Down |
| `D` | Move Right |
| `Left Mouse Button` | Shoot Bullet (towards cursor) |
| `Right Mouse Button` | Fire Special Weapon (radial blast) |
| `P` | Pause/Resume Game |
| `ESC` | Exit Game |

---

## 📂 Project Structure

```
ShapesWar-SFML/
│
├── assets/                      # Game assets
│   ├── config.txt              # Gameplay configuration file
│   └── KillerTech.ttf          # Font for UI text
│
├── src/                         # Source code
│   ├── main.cpp                # Entry point
│   ├── Game.h / Game.cpp       # Core game loop and systems
│   ├── Entity.h / Entity.cpp   # Entity class definition
│   ├── EntityManager.h / .cpp  # ECS entity management
│   ├── Components.h / .cpp     # Component definitions (Transform, Shape, Collision, etc.)
│   └── vec2.h / vec2.cpp       # 2D vector math library
│
├── CMakeLists.txt              # CMake build configuration
├── .gitignore                  # Git ignore rules
├── LICENSE                     # MIT License
└── README.md                   # This file
```

---

## 🎯 Gameplay Mechanics

### Enemy System

- **Randomized Spawning**: Enemies spawn at random intervals with varying polygon shapes (3-8 sides)
- **Speed Variation**: Each enemy has randomized speed within configured min/max ranges
- **Fragmentation**: Large enemies break into smaller enemies when destroyed
- **Scoring**: Each enemy kill awards points based on the number of vertices

### Weapon Systems

#### Standard Bullets
- Fire towards mouse cursor position
- Limited lifespan (auto-despawn after configurable frames)
- Kill enemies on collision

#### Special Weapon
- Radial blast centered on the player
- Fires bullets in all directions (360° coverage)
- Limited usage based on player configuration

### Physics & Movement

- **Custom Vector Math**: Dedicated `vec2` class for position, velocity, and direction calculations
- **Collision Detection**: Circle-based bounding volumes for all shapes
- **Boundary Constraints**: Player is confined to window boundaries

### Configuration System

All gameplay parameters are loaded from `assets/config.txt`:

- Window dimensions and framerate
- Player attributes (size, speed, fire rate, colors)
- Enemy properties (spawn rate, speed range, vertex count)
- Bullet characteristics (speed, lifespan, size)
- Font and UI settings

**Example config.txt:**
```
Window 1200 720 60 0
Font Assets/KillerTech.ttf 24 255 255 255
Player 32 32 5 5 5 5 255 0 0 4 8 90
Enemy 32 32 3 5 255 255 255 2 3 8 90 90 100 200
Bullet 10 10 8 255 255 255 255 255 255 2 20 90
```

---

## ⚙️ Configuration

You can customize the game by editing `assets/config.txt`. Here's what each parameter means:

### Window Configuration
```
Window <width> <height> <framerate> <fullscreen>
```

### Player Configuration
```
Player <shapeRadius> <collisionRadius> <speed> <fillR> <fillG> <fillB> <outlineR> <outlineG> <outlineB> <outlineThickness> <vertices> <specialWeaponCooldown>
```

### Enemy Configuration
```
Enemy <shapeRadius> <collisionRadius> <speedMin> <speedMax> <outlineR> <outlineG> <outlineB> <outlineThickness> <minVertices> <maxVertices> <smallLifespan> <spawnInterval> <scoreMultiplier> <smallEnemyScore>
```

### Bullet Configuration
```
Bullet <shapeRadius> <collisionRadius> <speed> <fillR> <fillG> <fillB> <outlineR> <outlineG> <outlineB> <outlineThickness> <vertices> <lifespan>
```

---

## 📄 License

This project is licensed under the **MIT License**.

```
MIT License

Copyright (c) 2026 Amr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🙏 Acknowledgments

- **SFML Team** for the excellent multimedia library
- **Dave Churchill** for ECS architecture inspiration
- Font: **[Killer Tech](https://www.dafont.com/killer-tech.font)** by GemFonts

---

## � Author

**GitHub**: [@amr10w](https://github.com/amr10w)

---

**Enjoy playing Shapes War!** 🎮✨
