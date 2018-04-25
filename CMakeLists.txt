cmake_minimum_required(VERSION 3.6)
project(MinesweeperBot)
find_package(XP-CMake) #we need advanced cmake modules

set(CMAKE_CXX_STANDARD 11)
Compiler_AutoBuildType()
find_package(StdPlusPlus REQUIRED)

add_executable(MinesweeperBot src/main.cpp src/MainWindow.hpp src/MainWindow.cpp)
target_link_libraries(MinesweeperBot Std++ Std++Static)