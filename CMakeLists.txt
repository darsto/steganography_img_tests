cmake_minimum_required(VERSION 3.6)
project(steganography_image)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(STB_IMAGE_FILE "${PROJECT_SOURCE_DIR}/src/stb_image.h")

if (NOT EXISTS "${STB_IMAGE_FILE}")
    file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" "${STB_IMAGE_FILE}")
endif()

set(SOURCE_FILES ${STB_IMAGE_FILE} src/main.c src/Image.h src/Image.c src/ImageBitCrypt.c src/ImageBitCrypt.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} m)