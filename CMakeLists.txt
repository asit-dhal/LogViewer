project(LogViewer CXX)

cmake_minimum_required(VERSION 3.2.2)

set(PROJECT_NAME "LogViewer")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        set(GUI_TYPE WIN32)
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

set(SRCS
    main.cpp
    mainwindow.cpp
    logmodel.cpp
    searchlogmodel.cpp
    settingsdialog.cpp
)
set(UIS
    mainwindow.ui
    settingsdialog.ui
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)



add_executable(${PROJECT_NAME} ${SRCS} ${UIS})

target_link_libraries(${PROJECT_NAME}
                    Qt5::Widgets
                    Qt5::Core
                    Qt5::Gui
                    Qt5::Network
                    )
