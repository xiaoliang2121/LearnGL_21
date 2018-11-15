cmake_minimum_required(VERSION 2.8)

project(LearnGL_21)

if(CMAKE_HOST_WIN32)
    set(WINDOWS 1)
endif()

# Add search path for include and lib files
set(FILE_PATH "E:/BookExamp/SB4/examples/src/shared")
INCLUDE_DIRECTORIES(${FILE_PATH})
LINK_DIRECTORIES(${FILE_PATH})

set(SRC_FILE main.cpp ${FILE_PATH}/math3d.cpp ${FILE_PATH}/gltools.cpp ${FILE_PATH}/GLee.c)
add_executable(${PROJECT_NAME} ${SRC_FILE})
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_link_libraries(${PROJECT_NAME} freeglutd)
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    target_link_libraries(${PROJECT_NAME} freeglut)
endif()

# 拷贝dll文件到程序输出目录
if(WINDOWS)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FILE_PATH}/freeglutd.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FILE_PATH}/freeglut.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
endif()
