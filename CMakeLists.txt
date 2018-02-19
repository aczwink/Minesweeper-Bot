cmake_minimum_required(VERSION 3.6)
project(MinesweeperBot)

set(CMAKE_CXX_STANDARD 11)

#debug or release
if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-D_DEBUG)
else()
    message(FATAL_ERROR "Unknown build type. Must be either 'Debug' or 'Release'")
endif()

find_library(ACSTDLIB_LIBRARY NAMES ACStdLib_d)
find_library(ACSTDLIBSTATIC_LIBRARY NAMES ACStdLibStatic_d)

set(LIBS ${ACSTDLIB_LIBRARY} ${ACSTDLIBSTATIC_LIBRARY})

add_executable(MinesweeperBot src/main.cpp src/MainWindow.hpp src/MainWindow.cpp)
target_link_libraries(MinesweeperBot ${LIBS})