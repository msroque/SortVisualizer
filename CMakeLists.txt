cmake_minimum_required(VERSION 3.16)             # Versions: CMake 3.0, Qt 3.5, Tutorial 3.16

if (WIN32)                                       # Configure build for Windows
    project(sort LANGUAGES CXX)
elseif(UNIX)                                     # Configure build for Linux and Mac
    project(sort)
endif()

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE) # build types: release, release w/ debug

#================ INCLUSION OF Qt ================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})                 # Finds Qt from PATH environment variable
find_package(Qt6Core REQUIRED)                     # Add libraries you want to use
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6OpenGL REQUIRED)
find_package(Qt6OpenGLWidgets REQUIRED)

#=========== INCLUSION OF Project Files ===========#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")         # for .ui files
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")     # for .h header files
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")          # for .cpp files

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"         # resource files
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

#===================== SETUP EXECUTABLE =====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add executable
if (WIN32)
    add_executable(sort WIN32 ${SOURCES})  # WIN32 stops console executions
    # add_executable(sort ${SOURCES})
elseif(UNIX)
    add_executable(sort ${SOURCES})
endif()

# Add the target includes for your project
target_include_directories(sort PRIVATE ${FORMS_DIR})
target_include_directories(sort PRIVATE ${INCLUDE_DIR})
target_include_directories(sort PRIVATE ${SOURCE_DIR})

#======================= LINKING LIBRARIES =======================#
target_link_libraries(sort Qt6::Widgets)
target_link_libraries(sort Qt6::Gui)
target_link_libraries(sort Qt6::OpenGL)
target_link_libraries(sort Qt6::OpenGLWidgets)