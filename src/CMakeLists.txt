cmake_minimum_required(VERSION 2.8)

project(variorum C CXX)

option(BUILD_SHARED_LIBS   "Build shared libraries"      ON)
option(BUILD_DOCS          "Build documentation"         ON)
option(BUILD_TESTING       "Test build"                  ON)
option(ENABLE_TESTS        "Build tests"                 ON)
option(VARIORUM_WITH_INTEL "Support Intel architectures" ON)
option(VARIORUM_WITH_AMD   "Support AMD architectures"   ON)
option(VARIORUM_WITH_IBM   "Support IBM architectures"   ON)
option(VARIORUM_WITH_GPU   "Support GPU architectures"   ON)

include(CMake/CMakeBasics.cmake)

include(CMake/Setup3rdParty.cmake)

include(CMake/SetupTests.cmake)

### Necessary for ExternalProject_Add
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include(CMake/SetupExternalProjects.cmake)

add_subdirectory(thirdparty_builtin)

### Add our libs
add_subdirectory(variorum)

### Add our tests
if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()

### Add our examples
add_subdirectory(examples)

### Add documentation targets
if(BUILD_DOCS)
    include(CMake/SetupDocs.cmake)
    add_subdirectory(docs)
endif()

### Create CMake importable exports
install(EXPORT variorum DESTINATION cmake)