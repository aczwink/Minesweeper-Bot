cmake_minimum_required(VERSION 3.6)
project(MinesweeperBot)

set(CMAKE_CXX_STANDARD 11)

#debug or release
if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-D_DEBUG)
else()
    message(FATAL_ERROR "Unknown build type. Must be either 'Debug' or 'Release'")
endif()

find_package(StdPlusPlus REQUIRED)

#find_library(STDPLUSPLUS_LIBRARY NAMES Std++_d)
#find_library(STDPLUSPLUSSTATIC_LIBRARY NAMES Std++Static_d)

#set(LIBS ${STDPLUSPLUS_LIBRARY} ${STDPLUSPLUSSTATIC_LIBRARY})

add_executable(MinesweeperBot src/main.cpp src/MainWindow.hpp src/MainWindow.cpp)
target_link_libraries(MinesweeperBot ${LIBS})