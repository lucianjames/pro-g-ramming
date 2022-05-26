cmake_minimum_required(VERSION 3.23.1) # Set based on the current version im using, will probably work on lots of other versions too

# Set the project name
project(ASCII-DIGITAL-CLOCK)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add the executable
add_executable(Clock Clock.cpp)
target_link_libraries(Clock ${CURSES_LIBRARIES})

# Copy char files over to the build directory
add_custom_command(TARGET Clock POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory # The command being used and stuff 
                       ${CMAKE_SOURCE_DIR}/ASCII/ $<TARGET_FILE_DIR:Clock>/ASCII/) # The source and target