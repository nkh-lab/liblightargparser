if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

file(GLOB SRC_FILES "src/*.cpp")

add_library(${PROJECT_NAME} STATIC 
    ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC include)
