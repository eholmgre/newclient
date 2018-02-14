cmake_minimum_required(VERSION 3.0.0)
project("fc2_newclient")

include(ExternalProject)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)

set(${CMAKE_BUILD_TYPE} Debug)

find_package(Protobuf REQUIRED)
find_package(ssl-vision REQUIRED)
find_package(grSim REQUIRED)

message(STATUS "building in: ${CMAKE_BINARY_DIR}")
message(STATUS "building in: ${PROJECT_BINARY_DIR}")

include_directories(
        ${SSL_VISION_SRC_SHARED_NET}
        ${SSL_VISION_SRC_SHARED_UTIL}
        ${PROTOBUF_INCLUDE_DIRS}
        ${PROJECT_BINARY_DIR}/external/ssl-vision
	${PROJECT_BINARY_DIR}/external/grSim
        ${CMAKE_SOURCE_DIR}/lib/rf
)


set(SRCS
        src/main.cpp
        src/vision.cpp
        src/vision.h
        src/field.h
        src/field.cpp
        src/robot.h
        src/communication.cpp
        src/communication.h
        ${PROJECT_BINARY_DIR}/external/grSim/grSim_Commands.pb.cc 
        ${PROJECT_BINARY_DIR}/external/grSim/grSim_Commands.pb.h
        ${PROJECT_BINARY_DIR}/external/grSim/grSim_Packet.pb.cc
        ${PROJECT_BINARY_DIR}/external/grSim/grSim_Packet.pb.h
        ${PROJECT_BINARY_DIR}/external/grSim/grSim_Replacement.pb.cc
        ${PROJECT_BINARY_DIR}/external/grSim/grSim_Replacement.pb.h
)
        
add_library(nRF24L01P lib/rf/nRF24L01P.h lib/rf/nRF24L01P.cpp)
link_libraries(nRF24L01P ft4222)

add_library(stream lib/rf/stream.cpp lib/rf/stream.h)

set(libs ${PROTOBUF_LIBRARIES} sslvision ft4222 nRF24L01P stream)
add_executable(newclient ${SRCS})
target_link_libraries(newclient ${libs})


install(TARGETS newclient RUNTIME DESTINATION bin)