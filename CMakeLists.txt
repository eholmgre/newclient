cmake_minimum_required(VERSION 2.6)
project(newclient)

add_subdirectory(ssl-vision)

set(SRCS
	main.cpp,
	client.cpp,
	client.h
)

add_executable(newclient ${SRCS})

install(TARGETS newclient RUNTIME DESTINATION bin)
