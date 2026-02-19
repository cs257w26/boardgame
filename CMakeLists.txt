cmake_minimum_required(VERSION 3.14)
project(boardgame)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Board library (can be consumed by other projects via FetchContent)
add_library(board_lib src/board.cpp src/menu.cpp)
set_target_properties(board_lib PROPERTIES CXX_STANDARD 17)
target_include_directories(board_lib PUBLIC src)
target_link_libraries(board_lib PUBLIC raylib)

# Doxygen documentation target
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

# Demo executable (uses main.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PUBLIC board_lib)
