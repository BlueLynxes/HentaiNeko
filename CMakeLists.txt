cmake_minimum_required(VERSION 3.22.1)
project(HentaiNeko VERSION 0.8.2)

add_compile_definitions(APPLICATION_VERSION="0.0.1 nightly")

# Set C++ to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

find_package(Jsoncpp REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.24.1)
pkg_check_modules(GLIB2 glib-2.0)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
)

include_directories(
    ${GTKMM_INCLUDE_DIRS},
    ${JSONCPP_INCLUDE_DIRS},
    ${GLIB2_INCLUDE_DIRS}
)

# Add source files
file(GLOB_RECURSE hnSourceFiles
    "source/*.h"
    "source/*.hpp"
    "source/*.c"
    "source/*.cc"
    "source/*.cpp"
    "config/*" #  Just to be able to browse config files in IDEs
)

add_executable(HentaiNeko ${hnSourceFiles})

# Add and link libraries
target_link_libraries(HentaiNeko ${GTKMM_LIBRARIES} Jsoncpp_lib)

# Specify targets output directory
set_target_properties( HentaiNeko
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug/lib"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug/lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release/lib"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release/lib"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin"
    
)

# Copy resources

# Copy configs to binary
file(COPY config DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY ui DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Respect source code folder structure
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_property(TARGET HentaiNeko PROPERTY FOLDER "HentaiNeko")

# Source Code
file(GLOB_RECURSE hnSource
    "source/*.h"
    "source/*.hpp"
    "source/*.c"
    "source/*.cc"
    "source/*.cpp"
    "source/backend/*.h"
    "source/backend/*.hpp"
    "source/backend/*.c"
    "source/backend/*.cc"
    "source/backend/*.cpp"
    "source/gui/*.h"
    "source/gui/*.hpp"
    "source/gui/*.c"
    "source/gui/*.cc"
    "source/gui/*.cpp"
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" PREFIX "Source" FILES ${hnSource})

# Config files
file (GLOB hnConfig
    "config/*"
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/config/" PREFIX "Configuration Files" FILES ${hnConfig})