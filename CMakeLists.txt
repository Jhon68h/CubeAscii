cmake_minimum_required(VERSION 3.10)
project(rotate)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 11)

add_executable(rotate rotate.c)

# Link against the math library
target_link_libraries(rotate m)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
