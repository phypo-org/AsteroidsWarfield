cmake_minimum_required(VERSION 3.16)
project(AsteroidsWarfield VERSION 1.1 LANGUAGES CXX)

# Use C++20 as required by the project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Options ---
option(USE_SOUND "Enable sound support (OpenAL)" ON)

# --- Dependencies ---

# OpenGL
find_package(OpenGL REQUIRED)

# FLTK - Fast Light Tool Kit
# We search for FLTK. It usually provides a CMake config file or is found via FindFLTK.cmake.
find_package(FLTK REQUIRED)

# OpenAL - Professional 3D Audio
if(USE_SOUND)
    find_package(OpenAL REQUIRED 
        HINTS 
            "/home/phipo/Bin/openal"
            "/home/phipo/Bin/openal/include"
            "/home/phipo/Bin/openal/build"
    )
    add_compile_definitions(USE_SOUND)
endif()

# Threading support
find_package(Threads REQUIRED)

# --- Platform Specific Configuration ---

if(WIN32)
    # Windows specific definitions
    add_compile_definitions(WIN32)
    
    if(MINGW)
        # Static linking of runtime libraries as in the original Makefile
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
        # Add -mwindows to avoid opening a console window for a GUI application
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    endif()
    
    # Common threading/concurrency definitions
    add_compile_definitions(_REENTRANT _THREAD_SAFE)
else()
    # Linux / Unix specific definitions
    add_compile_definitions(_REENTRANT _POSIX_PTHREAD_SEMANTICS _LARGEFILE_SOURCE _LARGEFILE64_SOURCE _THREAD_SAFE)
    
    # X11 is often needed for FLTK on Linux
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
endif()

# --- Include Directories ---
include_directories(
    src
    .
    ${FLTK_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

if(USE_SOUND)
    include_directories(${OPENAL_INCLUDE_DIR})
endif()

# --- Source Files ---
# Helper to collect all source files from the subdirectories
# We use file(GLOB_RECURSE) to match the behavior of the original Makefile's wildcard searches
file(GLOB_RECURSE SOURCES 
    "src/Main/*.cpp"
    "src/O3d/*.cpp"
    "src/Space/*.cpp"
    "src/Sprite3d/*.cpp"
    "src/T3d/*.cpp"
    "src/U3d/*.cpp"
    "src/Utils/*.cpp"
)

# Collect header files for better IDE support (e.g. Visual Studio, CLion)
file(GLOB_RECURSE HEADERS 
    "src/Main/*.h"
    "src/O3d/*.h"
    "src/Space/*.h"
    "src/Sprite3d/*.h"
    "src/T3d/*.h"
    "src/U3d/*.h"
    "src/Utils/*.h"
)

# --- Executable ---
# Add the main executable target
add_executable(AWF ${SOURCES} ${HEADERS})

# --- Linking ---
# Link required libraries to the executable
target_link_libraries(AWF
    PRIVATE
    ${FLTK_LIBRARIES}
    ${OPENGL_LIBRARIES}
    Threads::Threads
)

if(USE_SOUND)
    target_link_libraries(AWF PRIVATE ${OPENAL_LIBRARY})
    
    # Check for libsndfile which was present in the original Makefile
    find_library(SNDFILE_LIB NAMES sndfile)
    if(SNDFILE_LIB)
        target_link_libraries(AWF PRIVATE ${SNDFILE_LIB})
    endif()
endif()

if(UNIX AND NOT APPLE)
    # On Linux, FLTK might need these additional libraries explicitly linked
    target_link_libraries(AWF PRIVATE X11::X11)
    
    # Explicitly link common dependencies if they are not picked up by FLTK_LIBRARIES
    foreach(lib Xext Xft Xinerama Xfixes Xcursor Xrender fontconfig freetype)
        find_library(${lib}_LIB NAMES ${lib})
        if(${lib}_LIB)
            target_link_libraries(AWF PRIVATE ${${lib}_LIB})
        endif()
    endforeach()
endif()

# --- Output Properties ---
set_target_properties(AWF PROPERTIES 
    OUTPUT_NAME "AWF"
    # Ensure the executable is placed in the top level of the build directory
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# --- Installation ---
# Basic installation rule (optional)
install(TARGETS AWF DESTINATION bin)
