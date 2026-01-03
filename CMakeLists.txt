cmake_minimum_required(VERSION 3.18.1)

project("racing_engine")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine source files
file(GLOB_RECURSE ENGINE_SOURCES
    "engine/core/*.cpp"
    "engine/graphics/*.cpp"
    "engine/physics/*.cpp"
)

# Create shared library
add_library(racing_engine SHARED
    ${ENGINE_SOURCES}
)

# Find required libraries
find_library(log-lib log)
find_library(android-lib android)
find_library(GLESv3-lib GLESv3)
find_library(EGL-lib EGL)

# Link libraries
target_link_libraries(racing_engine
    ${log-lib}
    ${android-lib}
    ${GLESv3-lib}
    ${EGL-lib}
)

# Include directories
target_include_directories(racing_engine PRIVATE
    ${CMAKE_SOURCE_DIR}/engine
    ${CMAKE_SOURCE_DIR}/engine/core
    ${CMAKE_SOURCE_DIR}/engine/graphics
    ${CMAKE_SOURCE_DIR}/engine/physics
    ${CMAKE_SOURCE_DIR}/engine/math
)