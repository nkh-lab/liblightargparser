if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

find_package(GTest REQUIRED)

file(GLOB SRC_FILES "*.cpp")

add_executable(LightArgParserUnitTests
    ${SRC_FILES})

target_link_libraries(LightArgParserUnitTests
    PRIVATE ${PROJECT_NAME}
    PRIVATE ${GTEST_LIBRARIES}
    PRIVATE GTest::Main
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    )
