cmake_minimum_required(VERSION 3.20)
project (harvest_sweeper)

cmake_host_system_information(RESULT OS_NAME
                              QUERY OS_NAME)

if (NOT ${OS_NAME} MATCHES "Linux")
    message(FATAL_ERROR "Сборка возможна только в Linux-based системах")
endif()

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(sources)
add_subdirectory(unit_tests)

# file(GLOB_RECURSE SOURCES sources/*.cpp)
# file(GLOB_RECURSE HEADERS sources/*.hpp)

# file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
# file(GLOB_RECURSE TEST_HEADERS tests/*.hpp)

# add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
# add_executable(${PROJECT_NAME}_test ${TEST_SOURCES} ${TEST_HEADERS})