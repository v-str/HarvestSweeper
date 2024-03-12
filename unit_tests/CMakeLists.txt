message("-- ${Blue}CMake unit-tests module${ColorReset}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/coverage)

add_subdirectory(gtest)
include_directories(gtest/googlemock/include)
link_directories(${CMAKE_BINARY_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/sources)

file(GLOB SOURCES_TEST *.cpp)
file(GLOB HEADERS_TEST *.hpp)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/sources/*.cpp)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/sources/*.hpp)

list(REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/sources/main.cpp)

list(APPEND SOURCES_ALL ${SOURCES_TEST} ${SOURCES})
list(APPEND HEADERS_ALL ${HEADERS_TEST} ${HEADERS})

add_executable(${PROJECT_NAME}_unit_test ${SOURCES_ALL} ${HEADERS_ALL})
target_link_libraries(${PROJECT_NAME}_unit_test
                        ${Boost_PROGRAM_OPTIONS_LIBRARY}
                        gmock
                        gcov)

add_custom_target(coverage
    COMMAND ${PROJECT_NAME}_unit_test 
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR}
            --html --html-details
            --exclude ${CMAKE_SOURCE_DIR}/unit_test/*
            -o coverage_report.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    COMMENT "Generate coverage report..."
)