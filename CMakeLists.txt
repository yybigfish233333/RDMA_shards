cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)
project(HtableRDMA)

set(INCLUDE_BASE ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_BASE})

#查找log4cplus库
find_package(log4cplus REQUIRED)

set(COMMON_SRC ${PROJECT_SOURCE_DIR}/src)
set(SOURCES ${COMMON_SRC}/Htable.cc)

add_executable(HtableExecutable ${SOURCES})

# 包含log4cplus的头文件路径
include_directories(${LOG4CPLUS_INCLUDE_DIRS})

# 链接log4cplus库
target_link_libraries(HtableExecutable ${LOG4CPLUS_LIBRARIES})