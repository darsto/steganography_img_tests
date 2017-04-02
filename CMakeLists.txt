cmake_minimum_required(VERSION 3.6)
project(steganography_image C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Wextra -Werror \
    -Wno-missing-braces -Wno-missing-field-initializers -Wno-unused-variable -Wno-unused-parameter \
    -Wformat=2 -Wswitch-default -Wswitch-enum -Wcast-align -Wpointer-arith \
    -Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline \
    -Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code \
    -Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls \
    -Wold-style-definition")

set(STB_IMAGE_FILE "${PROJECT_SOURCE_DIR}/ext/stb_image.h")
set(STB_IMAGE_WRITE_FILE "${PROJECT_SOURCE_DIR}/ext/stb_image_write.h")

if (NOT EXISTS "${STB_IMAGE_FILE}")
    file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" "${STB_IMAGE_FILE}")
endif()

if (NOT EXISTS "${STB_IMAGE_WRITE_FILE}")
    file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h" "${STB_IMAGE_WRITE_FILE}")
endif()

set(SOURCE_FILES src/main.c src/Image.h src/Image.c src/ImageBitCrypt.c src/ImageBitCrypt.h src/ImageRecurrentBitCrypt.h src/ImageRecurrentBitCrypt.c)
find_package(GMP REQUIRED)
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/ext")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} m gmp)