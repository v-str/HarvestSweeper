cmake_minimum_required(VERSION 3.25)

cmake_host_system_information(RESULT OS_NAME
                              QUERY OS_NAME)

if (NOT ${OS_NAME} MATCHES "Linux")
    message(FATAL_ERROR "Сборка возможна только в Linux-like системах")
endif()

project (harvest_sweeper)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})