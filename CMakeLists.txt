cmake_minimum_required(VERSION 3.5)

if ("${RACK_SDK}" STREQUAL "")
  message(FATAL_ERROR "Path to Rack SDK missing! Add -DRACK_SDK=<path to Rack SDK> to the cmake call.")
endif ()

message(STATUS "Use Rack SDK: ${RACK_SDK}")

# set this to the plugin slug!
set(PLUGIN_NAME CaptainsSounds)

project(VCVRack${PLUGIN_NAME}Plugin)

set(CMAKE_CXX_STANDARD 14)

# Do not change the LIB_NAME!
set(LIB_NAME plugin)

include_directories("${RACK_SDK}/include" "${RACK_SDK}/dep/include")
link_directories(${RACK_SDK})

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE SRC_SOURCES src/*.cpp)

add_library(${LIB_NAME} MODULE ${SOURCES} ${SRC_SOURCES})

add_definitions(-DARCH_WIN)
target_include_directories(${LIB_NAME} PRIVATE include)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${LIB_NAME} "Rack")

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")

file(GLOB LICENSE LICENSE*)
file(INSTALL plugin.json res ${LICENSE} DESTINATION dist/${PLUGIN_NAME})
install(DIRECTORY ${PROJECT_BINARY_DIR}/lib/ DESTINATION ${PROJECT_BINARY_DIR}/dist/${PLUGIN_NAME} OPTIONAL)
install(DIRECTORY ${PROJECT_BINARY_DIR}/dist/${PLUGIN_NAME}/ DESTINATION ${PLUGIN_NAME})

# Enable ExternalProject CMake module
include(ExternalProject)

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/vendor)

# Add gtest
ExternalProject_Add(
    googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
    SVN_REVISION -r 660
    TIMEOUT 10
    PATCH_COMMAND svn patch ${CMAKE_SOURCE_DIR}/gtest.patch ${CMAKE_BINARY_DIR}/ThirdParty/src/googletest
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

# Add test executable target
add_executable(MainTest ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Create dependency of MainTest on googletest
add_dependencies(MainTest googletest)

# Specify MainTest's link libraries
ExternalProject_Get_Property(googletest binary_dir)
if(MSVC)
  set(Suffix ".lib")
else()
  set(Suffix ".a")
  set(Pthread "-pthread")
endif()
target_link_libraries(
    MainTest
    debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    ${Pthread})