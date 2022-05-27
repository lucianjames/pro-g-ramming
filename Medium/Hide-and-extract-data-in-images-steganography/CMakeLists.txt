cmake_minimum_required(VERSION 3.23.1) # Set based on the current version im using, will probably work on lots of other versions too

project( Stegonography )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS} )

add_custom_command(TARGET main POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory # The command being used and stuff 
                       ${CMAKE_SOURCE_DIR}/testImages/ $<TARGET_FILE_DIR:main>/testImages/) # The source and target