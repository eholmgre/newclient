cmake_minimum_required(VERSION 2.6)
project(newclient)

find_package(Protobuf REQUIRED)
if(EXISTS ${PROTOBUF_PROTOC_EXECUTABLE})
	message(STATUS "Found PROTOBUF Compiler: ${PROTOBUF_PROTOC_EXECUTABLE}")
else()
	message(FATAL_ERROR "Could not find PROTOBUF Compiler")
endif()

include_directories(
	ssl-vision/src/shared/net
	ssl-vision/src/shared/util
	ssl-vision/build
	${PROJECT_BINARY_DIR}
	${PROTOBUF_INCLUDE_DIRS}
)

add_subdirectory(ssl-vision)
#add_subdirectory(grSim)

set(SRCS
	main.cpp
	client.cpp
	client.h
)

set (libs ${PROTOBUF_LIBRARIES} sslvision)
add_executable(newclient ${SRCS})
target_link_libraries(newclient ${libs})


install(TARGETS newclient RUNTIME DESTINATION bin)
