cmake_minimum_required(VERSION 3.22.0)
project(computing_at_scale CXX)

find_package(Catch2 3 REQUIRED)

add_subdirectory(mathlibrary)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC mathlibrary)

add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(unit_tests)