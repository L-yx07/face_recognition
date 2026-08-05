cmake_minimum_required(VERSION 3.16)
project(face_recognition CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 让 compile_commands.json 直接写出完整 -I 参数，便于 VS Code IntelliSense 识别
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

# 本机 OpenCV（MinGW x64）安装目录；其他机器可用 -DOpenCV_DIR=... 覆盖
set(OpenCV_DIR "E:/OpenCV/OpenCV-MinGW-Build-OpenCV-4.1.0-x64")


find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs videoio objdetect highgui dnn)

# 自动收集 src 下的所有源文件；新增 .cpp 无需再改这里
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(face_recognition ${PROJECT_SOURCES})

target_include_directories(face_recognition PRIVATE src)

target_link_libraries(face_recognition PRIVATE ${OpenCV_LIBS})
