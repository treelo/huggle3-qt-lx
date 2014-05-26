# This is a build file for huggle (used with cmake)
# you will need to update it by hand
cmake_minimum_required (VERSION 2.8.9)
PROJECT(huggle)
#  cmake <folder> -DQT5_BUILD=true
option(QT5_BUILD "Build huggle using the Qt5 framework" FALSE)
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(QT_USE_QTNETWORK TRUE)
SET(QT_USE_QTXML TRUE)
SET(QT_USE_QTWEBKIT TRUE)
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
#### Qt 4 and 5 ####
if(QT5_BUILD)
  find_package(Qt5Core REQUIRED)
  find_package(Qt5Gui REQUIRED)
  find_package(Qt5WebKit REQUIRED)
  find_package(Qt5Xml REQUIRED)
  find_package(Qt5Widgets REQUIRED)
  find_package(Qt5Network REQUIRED)
  set(QT_INCLUDES
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${Qt5WebKit_INCLUDE_DIRS}
    ${Qt5Xml_INCLUDE_DIRS}
    ${Qt5Svg_INCLUDE_DIRS}
  )
  include_directories(${QT_INCLUDES})
else()
  find_package(Qt4 REQUIRED)
endif()

file(GLOB srcx
    "*.cpp"
)
file (GLOB resx
    "*.qrc"
)
file (GLOB uixx
    "*.ui"
)

SET(huggle_SOURCES ${srcx})
SET(huggle_FORMS ${uixx})
SET(huggle_RESOURCES ${resx})
if(QT5_BUILD)
    QT5_WRAP_CPP(huggle_HEADERS_MOC ${huggle_HEADERS})
    QT5_WRAP_UI(huggle_FORMS_HEADERS ${huggle_FORMS})
    QT5_ADD_RESOURCES(huggle_RESOURCES_RCC ${huggle_RESOURCES})
else()
    QT4_WRAP_CPP(huggle_HEADERS_MOC ${huggle_HEADERS})
    QT4_WRAP_UI(huggle_FORMS_HEADERS ${huggle_FORMS})
    QT4_ADD_RESOURCES(huggle_RESOURCES_RCC ${huggle_RESOURCES})
endif()
if (NOT QT5_BUILD)
  INCLUDE(${QT_USE_FILE})
endif()
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_EXECUTABLE(huggle ${huggle_SOURCES} ${huggle_HEADERS_MOC} ${huggle_FORMS_HEADERS} ${huggle_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(huggle ${QT_LIBRARIES})
if (QT5_BUILD)
    qt5_use_modules(huggle Core Gui Widgets WebKitWidgets WebKit Network Xml)
endif()
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INSTALL(FILES ${CMAKE_SOURCE_DIR}/man/huggle.1 DESTINATION share/man/man1)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/build/huggle.desktop DESTINATION share/applications)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/Resources/huggle3_newlogo.png DESTINATION share/huggle)
INSTALL(TARGETS huggle DESTINATION bin)