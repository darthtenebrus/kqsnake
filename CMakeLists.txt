cmake_minimum_required(VERSION 3.22)
project(kqsnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
endif()

find_package(Qt5 COMPONENTS
        Core
        REQUIRED)

find_package(KF5 COMPONENTS
        Config
        Crash
        ConfigWidgets
        I18n
        DocTools
        XmlGui
        REQUIRED)


set(RES_FILES images.qrc kqsnake.qrc)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
                main.cpp
                mainwindow.cpp
                mainwindow.h
                snakegame.cpp
                snakegame.h
                gameobject.cpp
                gameobject.h
                snake.cpp
                snake.h
                constants.h
                version.h
                configpagefirst.cpp
                configpagefirst.h
                configpagefirst.ui
                configpagesecond.cpp
                configpagesecond.h
                configpagesecond.ui
                myslider.cpp
                myslider.h
                ${RES_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOUIC_OPTIONS --tr i18n --idbased --include KLocalizedString)
kde_target_enable_exceptions(${PROJECT_NAME} PRIVATE)

kconfig_add_kcfg_files(${PROJECT_NAME} kqsnake.kcfgc)
kconfig_add_kcfg_files(${PROJECT_NAME}_SRCS GENERATE_MOC kqsnake.kcfgc)

target_link_libraries(${PROJECT_NAME}
        KF5::ConfigCore
        KF5::ConfigWidgets
        KF5::I18n
        KF5::Crash
        KF5::XmlGui
        )

install(TARGETS ${PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${PROJECT_NAME}.kcfg  DESTINATION  ${KDE_INSTALL_KCFGDIR})
install(FILES ${PROJECT_NAME}ui.rc  DESTINATION  ${KDE_INSTALL_KXMLGUI5DIR}/${PROJECT_NAME})

kdoctools_install(po)
ki18n_install(po)



