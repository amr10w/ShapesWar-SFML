cmake_minimum_required(VERSION 3.14)
project(ShapeWar)

# Use C++17 for modern SFML features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. DOWNLOAD SFML AUTOMATICALLY
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)

# 2. DEFINE THE EXECUTABLE
# Includes all the files seen in your project structure
add_executable(ShapeWar 
    src/main.cpp 
    src/Game.cpp 
    src/Entity.cpp 
    src/EntityManager.cpp 
    src/vec2.cpp
)

# 3. LINK LIBRARIES
# We link the SFML modules you're using
target_link_libraries(ShapeWar PRIVATE sfml-graphics sfml-window sfml-system)

# 4. AUTOMATIC DLL & ASSET MANAGEMENT (The "Fix")
# This copies everything to the folder where ShapeWar.exe lives 
# so you don't have to do it manually every time you build.
add_custom_command(TARGET ShapeWar POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/config.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/KillerTech.ttf"
        $<TARGET_FILE_DIR:ShapeWar>
    COMMENT "Copying SFML DLLs and Assets to the build directory"
)

# Ensure the executable knows where to find headers
target_include_directories(ShapeWar PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")