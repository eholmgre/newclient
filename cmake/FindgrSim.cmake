# NOTE!!! you will have to change the value of the app variable
add_subdirectory(${PROJECT_SOURCE_DIR}/external/grSim)

include_directories(
        ${PROJECT_BINARY_DIR}/external/grSim
)
