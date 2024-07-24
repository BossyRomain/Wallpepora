cmake_minimum_required(VERSION 3.22)

project(Wallpepora VERSION 1.0.0 LANGUAGES CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/includes)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(wallpepora ${SRC_FILES})
target_link_libraries(wallpepora ${OpenCV_LIBS} ${wxWidgets_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR}/tests)

list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE TESTS_SRC_FILES ${CMAKE_SOURCE_DIR}/tests/*.cpp)

add_executable(wallpeporaTests ${SRC_FILES} ${TESTS_SRC_FILES})
target_link_libraries(wallpeporaTests gtest gtest_main ${OpenCV_LIBS})