find_package(GTest REQUIRED)

add_executable(LightArgParserTest
    LightArgParserTest.cpp)

target_link_libraries(LightArgParserTest
    PRIVATE ${PROJECT_NAME}
    PRIVATE ${GTEST_LIBRARIES}
    PRIVATE GTest::Main
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    )
