cmake_minimum_required(VERSION 3.19)
project(SimplifiedOpenGL)

set(CMAKE_CXX_STANDARD 14)


add_executable(SimplifiedOpenGL main.cpp tgaimage.cpp)

target_link_libraries(SimplifiedOpenGL -lOpenGl32 -lfreeGLUT -lglfw3)


