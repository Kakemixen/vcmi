cmake_minimum_required(VERSION 3.16.3)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(helloworld
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)

message(STATUS ${SDL2_LIBRARY})

target_link_libraries(helloworld Qt5::Widgets vcmi ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_TTF_LIBRARY} ${FFMPEG_LIBRARIES} ${FFMPEG_EXTRA_LINKING_OPTIONS})

target_include_directories(helloworld
	PUBLIC	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC	${SDL2_INCLUDE_DIR}
	PRIVATE ${SDL2_TTF_INCLUDE_DIR}
	PRIVATE ${SDL2_MIXER_INCLUDE_DIR}
	PRIVATE ${SDL2_IMAGE_INCLUDE_DIR}
	PRIVATE ${FFMPEG_INCLUDE_DIRS}
)

include_directories(../client)
