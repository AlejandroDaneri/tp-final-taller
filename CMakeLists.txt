cmake_minimum_required(VERSION 3.0)
project(worms)

if (PATH)
set(CMAKE_INSTALL_PREFIX ${PATH})
endif(PATH)

configure_file(${PROJECT_SOURCE_DIR}/src/Editor/editor.glade ${PROJECT_SOURCE_DIR}/resources/Glade/editor.glade)

message("\n[INFO] Librerias necesarias:")
message("-Gtkmm version 3.0")
message("-SDL version 2\n")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)

find_package (Threads REQUIRED)
find_package (SDL2 REQUIRED)
find_package (SDL2_Mixer REQUIRED)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=c++11" )
add_definitions(-DROOT_PATH="${CMAKE_INSTALL_PREFIX}")

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2MIXER_INCLUDE_DIR})


MACRO(HEADER_DIRECTORIES src_dir return_list)
    FILE(GLOB_RECURSE new_list RELATIVE ${PROJECT_SOURCE_DIR} ${src_dir}/*.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(src/Common/ headers_common)
HEADER_DIRECTORIES(src/Client/ headers_client)
HEADER_DIRECTORIES(src/Server/ headers_server)
HEADER_DIRECTORIES(src/Editor/ headers_editor)
HEADER_DIRECTORIES(src/CommonUI/ headers_commonui)
HEADER_DIRECTORIES(src/Box2D/ headers_box2d)
HEADER_DIRECTORIES(src/Yaml/ headers_yaml)
set (headers_yaml ${headers_yaml} ${PROJECT_SOURCE_DIR}/src/Yaml/include)
set (headers ${PROJECT_SOURCE_DIR}/src/Defines)

file(GLOB_RECURSE CLIENT_SOURCES "src/Client/*.cpp")
file(GLOB_RECURSE SERVER_SOURCES "src/Server/*.cpp")
file(GLOB_RECURSE EDITOR_SOURCES "src/Editor/*.cpp")
file(GLOB_RECURSE COMMONUI_SOURCES "src/CommonUI/*.cpp")
file(GLOB_RECURSE COMMON_SOURCES "src/Common/*.cpp")
file(GLOB_RECURSE BOX2D_SOURCES "src/Box2D/*.cpp")
file(GLOB_RECURSE YAML_SOURCES "src/Yaml/*.cpp")

add_library(box2d ${BOX2D_SOURCES})
add_library(yaml ${YAML_SOURCES})
add_library(common ${COMMON_SOURCES})
add_library(commonui ${COMMONUI_SOURCES})


add_executable(client ${CLIENT_SOURCES})
add_executable(server ${SERVER_SOURCES})
add_executable(editor ${EDITOR_SOURCES})

include_directories(${headers})
target_include_directories(box2d PUBLIC ${headers_box2d} "src")
target_include_directories(yaml PUBLIC ${headers_yaml})
target_include_directories(common PUBLIC ${headers_common})
target_include_directories(commonui PUBLIC ${headers_commonui} ${headers_common})
target_include_directories(client PUBLIC ${headers_client} ${headers_common} ${headers_commonui})
target_include_directories(server PUBLIC ${headers_server} ${headers_common} ${headers_box2d} ${headers_yaml})
target_include_directories(editor PUBLIC ${headers_editor} ${headers_common} ${headers_commonui} ${headers_yaml})

target_link_libraries(client m commonui common ${GTKMM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${SDL2_LIBRARY} ${SDL2MIXER_LIBRARY})
target_link_libraries(editor m commonui common yaml ${GTKMM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(server m common box2d yaml ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS client server editor DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION .)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/config DESTINATION .)


