cmake_minimum_required(VERSION 3.31.0)
project(computing_at_scale CXX)

find_package(Catch2 3 REQUIRED)

#add_subdirectory(mathlibrary)

#add_executable(main main.cpp)
#target_link_libraries(main PUBLIC mathlibrary)

#add_executable(virtual virtual.cpp)

add_executable(unit_test unit_test.cpp)
target_link_libraries(unit_test PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(unit_test)
