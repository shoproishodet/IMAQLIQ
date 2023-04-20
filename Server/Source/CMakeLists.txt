cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/outputFiles)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/available_file_id.txt)
    message("available_file_id.txt exist!")
else ()
    message("Creating available_file_id.txt")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../available_file_id.txt ${CMAKE_CURRENT_BINARY_DIR})
endif ()


add_executable(${PROJECT_NAME}
        main.cpp
        ${INCLUDES}/Server.h
        Server.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${Boost_LIBRARIES_DIR})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${INCLUDES}
        )

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()
