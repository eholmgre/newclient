cmake_minimum_required(VERSION 3.0.0)
project("fc2_newclient")

include(ExternalProject)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)

find_package(Protobuf REQUIRED)
find_package(ssl-vision REQUIRED)
find_package(grSim)

message(STATUS "building in: ${CMAKE_BINARY_DIR}")
message(STATUS "building in: ${PROJECT_BINARY_DIR}")

include_directories(
        ${SSL_VISION_SRC_SHARED_NET}
        ${SSL_VISION_SRC_SHARED_UTIL}
        ${PROJECT_BINARY_DIR}/external/ssl-vision
        ${PROTOBUF_INCLUDE_DIRS}
)


set(SRCS
        src/main.cpp
        src/vision.cpp
        src/vision.h
        )

set(libs ${PROTOBUF_LIBRARIES} sslvision)
add_executable(newclient ${SRCS})
target_link_libraries(newclient ${libs})


install(TARGETS newclient RUNTIME DESTINATION bin)
