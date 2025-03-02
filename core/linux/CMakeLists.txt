cmake_minimum_required(VERSION 3.10)
project(webapp)
 
# 设置 C 语言标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
 
# 查找 GTK4 和 WebKitGTK 6.0（确保 pkg-config 可以找到这些库）
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4>=4.0)
pkg_check_modules(WEBKITGTK REQUIRED webkitgtk-6.0)
 
# 包含当前目录，以便编译器可以找到头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GTK4_INCLUDE_DIRS})
include_directories(${WEBKITGTK_INCLUDE_DIRS})
 
# 创建 webapp 共享库
add_library(webapp SHARED api.c icon.c)
 
# 链接 GTK4 和 WebKitGTK 到 webapp 库
target_link_libraries(webapp PRIVATE ${GTK4_LIBRARIES} ${WEBKITGTK_LIBRARIES})
 