cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(lightargparser)

option(${PROJECT_NAME}_BUILD_CTESTS "Build component tests" off)
option(${PROJECT_NAME}_BUILD_UTESTS "Build unit tests" off)

add_subdirectory(liblightargparser)
add_subdirectory(tests)
