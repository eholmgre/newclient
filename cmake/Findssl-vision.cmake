add_subdirectory(${PROJECT_SOURCE_DIR}/external/ssl-vision)

set(SSL_VISION_SRC_SHARED_UTIL
        ${PROJECT_SOURCE_DIR}/external/ssl-vision/src/shared/util)
set(SSL_VISION_SRC_SHARED_NET
        ${PROJECT_SOURCE_DIR}/external/ssl-vision/src/shared/net)

include_directories(
        ${PROJECT_BINARY_DIR}/external/ssl-vision
)
