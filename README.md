# Shapes War 🎮

A modern arcade shooter built with C++ and SFML, featuring an Entity-Component System (ECS) architecture and fully config-driven gameplay.

---

## 📋 Table of Contents

- [Demo](#-demo)
- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Prerequisites](#-prerequisites)
- [Setup & Installation](#-setup--installation)
- [Controls](#-controls)
- [Project Structure](#-project-structure)
- [Gameplay Mechanics](#-gameplay-mechanics)
- [Configuration](#-configuration)
- [License](#-license)

---

## 🎬 Demo

> **Video/GIF Placeholder**  
> _Add a demo video or animated GIF showcasing gameplay here_

---

## ✨ Features

- **Entity-Component System (ECS)**: Clean, modular architecture for scalable game development
- **Config-Driven Design**: All gameplay parameters are externalized in `config.txt` for easy tweaking
- **Dynamic Enemy Spawning**: Randomized enemy shapes with configurable spawn rates
- **Special Weapons System**: Powerful radial attacks for clearing the screen
- **Score Tracking**: Real-time score display with enemy elimination rewards
- **Smooth Physics**: Custom 2D vector mathematics for fluid movement
- **Lifespan Management**: Automatic cleanup of temporary entities (bullets, small enemies)
- **Collision Detection**: Circle-based collision system for accurate hit detection

---

## 🛠️ Technologies Used

| Technology | Description |
|-----------|-------------|
| **C++17** | Modern C++ standard with STL features |
| **SFML 2.6.1** | Simple and Fast Multimedia Library for graphics and input |
| **CMake 3.14+** | Cross-platform build system |
| **MinGW-w64** | GCC compiler for Windows |
| **Entity-Component System** | Custom-built ECS for game architecture |

---

## 📦 Prerequisites

Ensure you have the following tools installed on your system:

| Tool | Version | Purpose | Download Link |
|------|---------|---------|---------------|
| **Git** | Latest | Version control and cloning the repository | [git-scm.com](https://git-scm.com/downloads) |
| **CMake** | 3.14+ | Build configuration | [cmake.org](https://cmake.org/download/) |
| **MinGW-w64** | GCC 11.0+ | C++ compiler | [winlibs.com](https://winlibs.com/) or [mingw-w64.org](https://www.mingw-w64.org/) |
| **Make** | Latest | Build automation (usually comes with MinGW) | Included with MinGW |

> **Note**: SFML is automatically downloaded and configured by CMake using `FetchContent`, so you don't need to install it manually.

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

### 1. Clone the Repository

```bash
git clone https://github.com/amr10w/ShapesWar-SFML.git
cd ShapesWar-SFML
```

### 2. Configure the Project with CMake

Create a build directory and configure the project:

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
```

> **Important**: The `-G "MinGW Makefiles"` flag tells CMake to generate Makefiles compatible with MinGW.

### 3. Build the Project

Compile the source code:

```bash
mingw32-make
```

Alternatively, if you're using **Visual Studio Code**, you can use the built-in CMake tools:

- Press `Ctrl + Shift + P` → Type `CMake: Configure`
- Press `Ctrl + Shift + B` to build
- Or press `F7` to build with default tasks

### 4. Run the Game

After building, run the executable from the terminal:

```bash
.\build\ShapeWar.exe
```

Or in **Visual Studio Code**:

- Press `Ctrl + Shift + F5` to run without debugging
- Press `F5` to run with debugging

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

## 📧 Contact

For questions or feedback, feel free to reach out:

- **GitHub**: [@amr10w](https://github.com/amr10w)

---

**Enjoy playing Shapes War!** 🎮✨
