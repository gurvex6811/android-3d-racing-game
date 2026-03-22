cmake_minimum_required(VERSION 3.22.1)

project("racing_engine")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine source files
file(GLOB ENGINE_CORE_SOURCES "${CMAKE_SOURCE_DIR}/engine/core/*.cpp")
file(GLOB ENGINE_GRAPHICS_SOURCES "${CMAKE_SOURCE_DIR}/engine/graphics/*.cpp")
file(GLOB ENGINE_PHYSICS_SOURCES "${CMAKE_SOURCE_DIR}/engine/physics/*.cpp")
file(GLOB ENGINE_ASSETS_SOURCES "${CMAKE_SOURCE_DIR}/engine/assets/*.cpp")
file(GLOB ENGINE_AUDIO_SOURCES "${CMAKE_SOURCE_DIR}/engine/audio/*.cpp")

# Add JNI bridge
set(JNI_BRIDGE_SOURCE "${CMAKE_SOURCE_DIR}/app/src/main/cpp/jni_bridge.cpp")

# Create shared library
add_library(racing_engine SHARED
    ${ENGINE_CORE_SOURCES}
    ${ENGINE_GRAPHICS_SOURCES}
    ${ENGINE_PHYSICS_SOURCES}
    ${ENGINE_ASSETS_SOURCES}
    ${ENGINE_AUDIO_SOURCES}
    ${JNI_BRIDGE_SOURCE}
)

# Find required Android libraries
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
    ${CMAKE_SOURCE_DIR}/engine/assets
    ${CMAKE_SOURCE_DIR}/engine/audio
)

# Set output directory for .so files
set_target_properties(racing_engine PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
)
