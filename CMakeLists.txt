cmake_minimum_required(VERSION 3.17)
project(qt_inform7 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Widgets WebEngineWidgets WebChannel CONFIG REQUIRED)
set(CMAKE_AUTOMOC ON)

add_executable(qtinform7 WIN32 src/main.cpp
        src/i7project.cpp src/i7project.h
        src/i7syntax.cpp src/i7syntax.h
        src/launcherdialog.cpp src/launcherdialog.h
        src/projectwindow.cpp src/projectwindow.h
        src/config.cpp src/config.h
        src/informurlhandler.cpp src/informurlhandler.h
        "src/informbrowser.cpp" "src/informbrowser.h"
        )
target_link_libraries(qtinform7 Qt5::Widgets Qt5::WebEngineWidgets Qt5::WebChannel)