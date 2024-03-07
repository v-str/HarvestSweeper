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