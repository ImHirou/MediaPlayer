cmake_minimum_required(VERSION 3.16)
project(MediaPlayer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE QML_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.qml")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick Qml Multimedia)

set(SOURCES
    src/main.cpp
    src/TrackImageProvider.cpp
    src/TrackModel.cpp
    src/TrackInfo.cpp
    src/Config.cpp
    src/MediaPlayer.cpp
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
)

qt_add_qml_module(${PROJECT_NAME}
    URI app
    VERSION 1.0
    RESOURCE_PREFIX /qml
    QML_FILES ${QML_FILES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Quick
    Qt6::Qml
    Qt6::Multimedia
    Qt6::Gui
)
