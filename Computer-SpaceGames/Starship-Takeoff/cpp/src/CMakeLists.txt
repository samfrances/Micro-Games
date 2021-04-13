cmake_minimum_required(VERSION 3.13)

# set the project name
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

# # add the executable
add_executable(Test Test.cpp)

# Testing

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  gtest
  pthread
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
