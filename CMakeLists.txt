cmake_minimum_required(VERSION 3.20)
project (harvest_sweeper)

cmake_host_system_information(RESULT OS_NAME
                              QUERY OS_NAME)

if (NOT ${OS_NAME} MATCHES "Linux")
    message(FATAL_ERROR "Сборка возможна только в Linux-based системах")
endif()

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.83 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_subdirectory(sources)
add_subdirectory(unit_tests)