cmake_minimum_required(VERSION 2.6)
project(newclient)

find_package(Protobuf REQUIRED)
if(EXISTS ${PROTOBUF_PROTOC_EXECUTABLE})
	message(STATUS "Found PROTOBUF Compiler: ${PROTOBUF_PROTOC_EXECUTABLE}")
else()
	message(FATAL_ERROR "Could not find PROTOBUF Compiler")
endif()

include_directories(
	${PROTOBUF_INCLUDE_DIRS}
)

add_subdirectory(ssl-vision)

set(SRCS
	main.cpp
	client.cpp
	client.h
)

include_directories(ssl-vision/src/shared/net)


add_executable(newclient ${SRCS})
target_link_libraries(newclient ${PROTOBUF_LIBRARIES})

install(TARGETS newclient RUNTIME DESTINATION bin)
