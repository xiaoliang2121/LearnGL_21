cmake_minimum_required(VERSION 2.8)

project(LearnGL_21)

if(CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Add search path for include and lib files
aux_source_directory(. SRC_FILE)
if(WINDOWS)
    set(FILE_PATH "E:/BookExamp/SB4/examples/src/shared")
    INCLUDE_DIRECTORIES(${FILE_PATH})
    LINK_DIRECTORIES(${FILE_PATH})

    set(SRC_FILE ${SRC_FILE} ${FILE_PATH}/math3d.cpp ${FILE_PATH}/gltools.cpp ${FILE_PATH}/GLee.c ${FILE_PATH}/TriangleMesh.cpp)
    add_executable(${PROJECT_NAME} ${SRC_FILE})
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_link_libraries(${PROJECT_NAME} freeglutd)
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        target_link_libraries(${PROJECT_NAME} freeglut)
    endif()

elseif(LINUX)
    set(SHARD_PATH ~/studyRes/BookEps/SB4/examples/src/shared)
    set(INC_PATH /usr/include /usr/local/include/GL ${SHARD_PATH} /usr/include/GL)
    include_directories(${INC_PATH})
    link_directories(/usr/local/lib)

    set(SRC_FILE ${SRC_FILE} ${SHARD_PATH}/math3d.cpp ${SHARD_PATH}/gltools.cpp ${SHARD_PATH}/GLee.c ${SHARD_PATH}/TriangleMesh.cpp)
    add_executable(${PROJECT_NAME} ${SRC_FILE})
    target_link_libraries(${PROJECT_NAME} glut GL GLU m)

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
