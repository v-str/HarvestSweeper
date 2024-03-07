cmake_minimum_required(VERSION 3.20)
project (harvest_sweeper)

cmake_host_system_information(RESULT OS_NAME
                              QUERY OS_NAME)

if (NOT ${OS_NAME} MATCHES "Linux")
    message(FATAL_ERROR "Сборка возможна только в Linux-based системах")
endif()

file(GLOB_RECURSE SOURCES sources/*.cpp)
file(GLOB_RECURSE HEADERS sources/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})