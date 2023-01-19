cmake_minimum_required(VERSION 3.20)

project(SmartCalcv1.0 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

file(GLOB_RECURSE SMARTCALC_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SMARTCALC_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE LIBRARY_SOURCES ${PROJECT_SOURCE_DIR}/../*.o)

add_library(lib_calc STATIC ${LIBRARY_SOURCES})

set(PROJECT_SOURCES
        ${SMARTCALC_SOURCES}
        ${SMARTCALC_HEADERS}
        ${CUSTOMPLOT_HEADERS}
        ${CUSTOMPLOT_SOURCES}
        ../main.cpp
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../backend)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets lib_calc)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::PrintSupport)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Test)
endif()
