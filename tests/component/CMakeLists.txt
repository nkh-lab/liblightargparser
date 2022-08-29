add_executable(SimpleAppTest
    SimpleAppTest.cpp)

target_link_libraries(SimpleAppTest
    PRIVATE lightargparser
    )