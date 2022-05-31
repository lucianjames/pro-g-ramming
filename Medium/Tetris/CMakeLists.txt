cmake_minimum_required(VERSION 3.23.1) # Set based on the current version im using, will probably work on lots of other versions too

# Set the project name
project(TETRIS-NCURSES)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add the executable
add_executable(tetris tetris.cpp)
target_link_libraries(tetris ${CURSES_LIBRARIES})