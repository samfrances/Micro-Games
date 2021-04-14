cmake_minimum_required(VERSION 3.13)

# set the project name
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

# # add the executable
add_executable(
    Starship-Takeoff
    main.cpp
    game.cpp
)

# Testing

enable_testing()

add_executable(
  tests
  test.cpp
  game.cpp
)
target_link_libraries(
  tests
  gtest
  pthread
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
