cmake_minimum_required(VERSION 3.0)
project(liang)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

find_package(Threads REQUIRED)
include(ExternalProject)
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
include_directories("${source_dir}/googletest/include")
include_directories("src/")

file(GLOB_RECURSE PROJECT_HEADERS src/core/*.h
                                  src/shapes/*.h)
file(GLOB_RECURSE PROJECT_SOURCES src/core/*.cpp
                                  src/shapes/*.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("include" FILES ${PROJECT_HEADERS})
source_group("src" FILES ${PROJECT_SOURCES})

add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_library(liang_lib STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})

add_executable(liang_exe src/main.cpp)
set_target_properties(liang_exe PROPERTIES OUTPUT_NAME liang
    RUNTIME_OUTPUT_DIRECTORY /${CMAKE_BINARY_DIR}/bin/)
target_link_libraries(liang_exe liang_lib)

file(GLOB TEST_SOURCES src/tests/*.cpp)
file(GLOB TEST_HEADERS src/tests/*.h)
add_executable(liang_test ${TEST_SOURCES} ${TEST_HEADERS})
set_target_properties(liang_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY /${CMAKE_BINARY_DIR}/bin/)
target_link_libraries (liang_test liang_lib pthread libgtest)
