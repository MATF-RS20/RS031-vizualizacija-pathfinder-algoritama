cmake_minimum_required(VERSION 3.10.2)

project(vizualizacija VERSION 1.0.0 LANGUAGES CXX)
include_directories(headers)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
    sources/main.cpp 
    sources/mainwindow.cpp 
    sources/algoritmi.cpp 
    sources/popup.cpp 
    sources/qrightclickbutton.cpp
)
set(HEADERS
        headers/mainwindow.h 
        headers/algoritmi.h 
        headers/qrightclickbutton.h 
        headers/popup.h
)
set(FORMS
        forms/mainwindow.ui 
        forms/popup.ui
)

qt5_wrap_ui(UI_HEADERS ${FORMS})
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${FORMS})
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)
