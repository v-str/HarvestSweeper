message(STATUS "inside tests...")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(gtest)

include_directories(gtest/googlemock/include)
link_directories(${CMAKE_BINARY_DIR}/lib)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)

add_executable(${PROJECT_NAME}_unit_test ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}_unit_test gmock)