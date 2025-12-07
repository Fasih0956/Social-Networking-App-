cmake_minimum_required(VERSION 3.10)
project(Social-Networking-App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
)

# Create executable
add_executable(Social-Networking-App ${SOURCES})

# Copy assets folder to build directory
add_custom_command(TARGET Social-Networking-App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Copying assets folder to build directory"
)