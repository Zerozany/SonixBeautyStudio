# 查找源文件和头文件
file(GLOB SRCFILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

# 为每个子目录添加头文件目录
file(GLOB INCLUDEDIR
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

foreach(HEADERDIR ${INCLUDEDIR})
        if(IS_DIRECTORY ${HEADERDIR})
                target_include_directories(${PROJECT_NAME}
                        PUBLIC
                        ${HEADERDIR}
                )
        endif()
endforeach()

target_include_directories(${PROJECT_NAME}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# 将源文件和头文件加入到目标中
target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRCFILES}
)
