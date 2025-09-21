cmake_minimum_required(VERSION 3.10)
project(PhysXineProject)

# ------------------------------
# Set C++ standard
# ------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# Include directories
# ------------------------------
include_directories(
    ${PROJECT_SOURCE_DIR}/include        # glad + KHR
    ${PROJECT_SOURCE_DIR}                # root (for glad.c)
    ${PROJECT_SOURCE_DIR}/src            # src headers
    ${PROJECT_SOURCE_DIR}/src/rend       # Renderer.hpp
    /opt/homebrew/include                # Homebrew includes for GLFW/Eigen (Intel Mac: /usr/local/include)
    /opt/homebrew/include/eigen3
    ${CMAKE_SOURCE_DIR}/ext/imGui        # ImGui headers
)

# ------------------------------
# Gather ImGui sources
# ------------------------------
set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/ext/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/ext/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/ext/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/ext/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/ext/imgui/imgui_widgets.cpp
)

# ------------------------------
# Gather all other source files
# ------------------------------
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)
list(FILTER SOURCES EXCLUDE REGEX ".*\\.ini")   # exclude config files

# ------------------------------
# Create the executable (include ImGui sources)
# ------------------------------
add_executable(PhysXine
    ${SOURCES}
    ${IMGUI_SOURCES}
)

# ------------------------------
# Link libraries (macOS)
# ------------------------------
target_link_libraries(PhysXine
    glfw
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
