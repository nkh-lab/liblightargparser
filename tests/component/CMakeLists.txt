if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

add_executable(SimpleAppTest
    SimpleAppTest.cpp)

target_link_libraries(SimpleAppTest
    PRIVATE lightargparser
    )