cmake_minimum_required(VERSION 3.18)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cash.txt ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../potter.txt ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
        main.cpp
        ${INCLUDES}/Client.h
        Client.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${Boost_LIBRARIES_DIR})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${INCLUDES}
        )

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()
