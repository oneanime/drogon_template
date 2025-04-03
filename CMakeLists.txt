cmake_minimum_required(VERSION 3.30)
project(drogon_template)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/build/${PROJECT_NAME})
#设置执行文件输出的目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/bin)
#设置编译后的库输出的目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/lib)

#创建日志文件夹
set(LOG_OUTPUT_DIR ${BUILD_OUTPUT_DIR}/logs)
file(MAKE_DIRECTORY ${LOG_OUTPUT_DIR})

#创建配置文件安放的文件夹，并把配置文件拷贝到这个目录下
set(CONFIG_SOURCE_DIR ${CMAKE_SOURCE_DIR}/config)
set(CONFIG_OUTPUT_DIR ${BUILD_OUTPUT_DIR}/config)
file(MAKE_DIRECTORY ${CONFIG_OUTPUT_DIR})
file(GLOB CONFIG_FILES "${CONFIG_SOURCE_DIR}/config.json")
foreach(CONFIG_FILE ${CONFIG_FILES})
    get_filename_component(FILE_NAME ${CONFIG_FILE} NAME)
    configure_file(${CONFIG_FILE} ${CONFIG_OUTPUT_DIR}/${FILE_NAME} COPYONLY)
endforeach()

#生成启动脚本
file(WRITE "${BUILD_OUTPUT_DIR}/start.bat"
        "@echo off
bin\\${PROJECT_NAME}.exe
")
file(WRITE "${BUILD_OUTPUT_DIR}/start.sh"
        "#!/usr/bin/env bash

cd \"\$(dirname \"\$0\")\"/bin || exit 1

if [[ -x \"./drogon_template\" ]]; then
    exec ./drogon_template \"\$@\"
else
    echo \"error: cannot find drogon_template\" >&2
    exit 1
fi
")



if(UNIX)
    file(CHMOD "${BUILD_OUTPUT_DIR}/start.sh"
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
endif()



#导入第三方库
find_package(Drogon CONFIG REQUIRED)
#find_package(yaml-cpp CONFIG REQUIRED)



file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            Drogon::Drogon
            #yaml-cpp::yaml-cpp
)


