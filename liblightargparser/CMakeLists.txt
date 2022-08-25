
file(GLOB SRC_FILES "src/*.cpp")

add_library(${PROJECT_NAME} STATIC 
    ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC include)
