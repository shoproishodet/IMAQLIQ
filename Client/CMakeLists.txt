cmake_minimum_required(VERSION 3.18)
set(PROJECT_NAME "Client")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(Source)