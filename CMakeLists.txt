cmake_minimum_required(VERSION 3.0)

#------------------------------------------------------------------------------
# CMake Policies
#------------------------------------------------------------------------------

if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()


#------------------------------------------------------------------------------
# Hunter & Project
#
# Note: I am using the Hunter package manager for cmake
# This is an external project that I am using exclusively
# as a utility for my cmake build file. For those interested,
# it can be found at https://github.com/ruslo/hunter
#------------------------------------------------------------------------------

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
    SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

project(EightMinuteEmpire)

#Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


#------------------------------------------------------------------------------
# Hunter Packages
#------------------------------------------------------------------------------

#Boost serialization and graph
hunter_add_package(Boost COMPONENTS filesystem graph serialization system)
find_package(Boost CONFIG REQUIRED filesystem graph serialization system)


#------------------------------------------------------------------------------
# Other dependencies
#------------------------------------------------------------------------------

# In case we use graphviz.
# NOTE: this dependency is not handled by hunter and needs to be installed manually on your computer
# check it out here: https://graphviz.gitlab.io/download/

# GraphViz
#include("cmake/FindGraphViz.cmake")
#
#if (NOT GRAPHVIZ_FOUND)
#    message(FATAL_ERROR "GraphViz must be installed on the system!!")
#endif()
#
#include_directories(${GRAPHVIZ_INCLUDE_DIRS})


#------------------------------------------------------------------------------
# Doxygen
#------------------------------------------------------------------------------

# In case we use doxygen for our documentation
#find_package(Doxygen)
#if (DOXYGEN_FOUND)
#
#    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
#    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
#
#    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#    message("Doxygen build started")
#
#    add_custom_target(doc
#        ALL
#        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        COMMENT "Generating documentation with Doxygen"
#        VERBATIM
#    )
#
#    add_custom_target(doc-clean
#        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/doc/
#        COMMENT "Cleaning up documentation"
#        VERBATIM
#    )
#
#else(DOXYGEN_FOUND)
#    message("Doxygen must be installed in order to generate the documentation")
#endif(DOXYGEN_FOUND)


#------------------------------------------------------------------------------
# Binaries
# Every part will be a library that we link to the executable,
# Makes things cleaner.
#------------------------------------------------------------------------------

# Map
add_library(Map
    src/Utils/SerializationUtils.hpp
    src/Map/Map.h
    src/Map/Map.cpp
)
target_include_directories(Map PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Map
    Boost::boost
    Boost::filesystem
    Boost::graph
    Boost::serialization
    Boost::system # Needs to be last
)

# Map Driver
add_executable(MapGenerator
    src/Map/MapDriver.cpp
)
target_include_directories(MapGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(MapGenerator Map)

# Map Loader
add_library(MapLoader
    src/Map/MapLoader.h
    src/Map/MapLoader.cpp
)
target_include_directories(MapLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(MapLoader Map)

# Map Loader Driver
add_executable(MapLoaderDriver
    src/Map/MapLoaderDriver.cpp
)
target_include_directories(MapLoaderDriver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(MapLoaderDriver MapLoader)

# Player
add_library(Player
    src/Player/Player.h
    src/Player/Player.cpp
)
target_include_directories(Player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# BidingFacility
add_library(BidingFacility
    src/Player/BidingFacility.h
    src/Player/BidingFacility.cpp
)
target_include_directories(BidingFacility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# BidingFacility Driver
add_executable(BidingFacilityDriver
    src/Player/BidingFacilityDriver.cpp
)
target_include_directories(BidingFacilityDriver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(BidingFacilityDriver BidingFacility Player)
