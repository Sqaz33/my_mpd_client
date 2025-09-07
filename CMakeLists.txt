cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(mmpc CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(MPDCLIENT REQUIRED libmpdclient)
file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${MPDCLIENT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MPDCLIENT_LIBRARIES})


