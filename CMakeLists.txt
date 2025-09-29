cmake_minimum_required(VERSION 3.10)
project(momentum)

# ------------------------------
# Set C++ standard
# ------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# MacOS specific settings
# ------------------------------
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGL_SILENCE_DEPRECATION")
    set(GLFW_USE_CHDIR OFF CACHE BOOL "" FORCE)
    find_package(OpenGL REQUIRED)
endif()

# ------------------------------
# Include directories
# ------------------------------
include_directories(
    ${PROJECT_SOURCE_DIR}/include        # glad + KHR
    ${PROJECT_SOURCE_DIR}                # root (for glad.c)
    ${PROJECT_SOURCE_DIR}/src            # src headers
    ${PROJECT_SOURCE_DIR}/src/rend       # Renderer.hpp
    /opt/homebrew/include                # Homebrew includes for GLFW/Eigen (Intel Mac: /usr/local/include)
    /opt/homebrew/include/eigen3         # Eigen headers
    ${CMAKE_SOURCE_DIR}/ext/imGui        # ImGui headers directory
    ${CMAKE_SOURCE_DIR}/ext              # For imGui/ prefixed includes
)

# ------------------------------
# Gather ImGui sources
# ------------------------------
set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/ext/imGui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/ext/imGui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/ext/imGui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/ext/imGui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/ext/imGui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/ext/imGui/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/ext/imGui/imgui_impl_opengl3.cpp
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
# Create the executable (include ImGui sources and glad.c)
# ------------------------------
add_executable(momentum
    ${SOURCES}
    ${IMGUI_SOURCES}
    ${PROJECT_SOURCE_DIR}/glad.c
    ${PROJECT_SOURCE_DIR}/Main.cpp
)

# ------------------------------
# Link libraries
# ------------------------------
if(APPLE)
    # Find GLFW package
    find_package(glfw3 3.3 REQUIRED)
    
    # Link against frameworks
    target_link_libraries(momentum
        PRIVATE
        glfw
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()
