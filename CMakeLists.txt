cmake_minimum_required(VERSION 3.10)
# set(CMAKE_C_COMPILER "clang")

project(SolarSystem)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Adding the compilation flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -march=native")
# -fsanitize=address

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Looking for SDL2 et SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Adding the sources
file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "include/*.h")

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

add_custom_target(
    clang-tidy
    COMMAND ${CMAKE_COMMAND} -E echo "Running clang-tidy on C source and header files..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-tidy on C source and header files"
)

foreach(FILE ${SOURCES} ${HEADERS})
    get_filename_component(FILE_NAME ${FILE} NAME)
    add_custom_command(
        TARGET clang-tidy PRE_LINK
        COMMAND clang-tidy
            -p ${CMAKE_BINARY_DIR}
            --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
            ${FILE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Processing ${FILE_NAME} with clang-tidy"
        VERBATIM
    )
endforeach()
