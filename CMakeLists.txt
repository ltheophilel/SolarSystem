cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Adding the compilation flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Looking for SDL2 et SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Adding the sources
file(GLOB SOURCES "src/*.c")

# Creating the executable
add_executable(solarsystem ${SOURCES})

# Adding the folder include/ to the inclusion path
target_include_directories(solarsystem PRIVATE include)

# Adding SDL2 compilation flags (equivalent to sdl2-config --cflags)
target_include_directories(solarsystem PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(solarsystem PRIVATE ${SDL2TTF_INCLUDE_DIRS})

# Linking with libraries
target_link_libraries(solarsystem ${SDL2_LIBRARIES} m SDL2_ttf)

# Copying the fonts directory into build
add_custom_command( 
    TARGET solarsystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts
        ${CMAKE_BINARY_DIR}/fonts
)