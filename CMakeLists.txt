# qTagger Cmake build script
cmake_minimum_required( VERSION 2.6 )

# set project's name
project( QTAGGER )

message(STATUS "System: " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

find_package( Qt4 REQUIRED )
include( "${QT_USE_FILE}" )
if (UNIX)
include(FindPkgConfig)
endif (UNIX)
# ------ version defination --------------------------


set(QTAGGER_VERSION "0.99.0")
add_definitions( -DVERSION="${QTAGGER_VERSION}")

# ------ build type ------------------------

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
  add_definitions(-DNDEBUG)
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif(${CMAKE_BUILD_TYPE} MATCHES "Release")

# ------ install prefix --------------------------

set(CMAKE_INSTALL_PREFIX "/usr")

add_definitions( -DPREFIX="${CMAKE_INSTALL_PREFIX}")

message(STATUS "Install prefix: " ${CMAKE_INSTALL_PREFIX})

# ------ files --------------------------

set(QTAGGER_SRC
    src/main.cpp
    src/aboutdialog.cpp
    src/config.cpp
    src/configdialog.cpp
    src/qtagger.cpp
    src/tag.cpp
    src/tagaudio.cpp
    src/mainwindow.cpp
    src/trackfileitem.cpp
    src/trackmodel.cpp
)

set(QTAGGER_MOC
    src/aboutdialog.h
    src/configdialog.h
    src/qtagger.h
    src/mainwindow.h
    src/trackmodel.h
)

set(QTAGGER_UI
    src/aboutdialog.ui
    src/configdialog.ui
    src/mainwindow.ui
)

# Qt resource file
set( QTAGGER_QRC qtagger.qrc )

  # this will run uic on .ui files:
qt4_wrap_ui(QTAGGER_UI_H ${QTAGGER_UI} )

# genereate moc headers
qt4_wrap_cpp(QTAGGER_MOC_CPP ${QTAGGER_MOC} )

# genereating resource cpp
qt4_add_resources( QRC_SOURCES ${QTAGGER_QRC} )

#------- includes -------------

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(NOT UNIX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/common/include)
endif(NOT UNIX)

# ------ taglib --------------------

if(UNIX)
pkg_check_modules(TAGLIB taglib)
endif(UNIX)

if(WIN32)
set (TAGLIB_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/common/taglib-1.6.1-bin/lib)
find_library(TAGLIB_LIBRARIES tag)
set(${TAGLIB_LIBRARIES})
endif(WIN32)

link_directories(${TAGLIB_LIBRARY_DIRS})

#------- distclean target [unix] ----------

if(UNIX)
add_custom_target(distclean @echo cleaning for source distribution)

add_custom_command(
    COMMENT "distribution clean"
    COMMAND make
    ARGS -C ${CMAKE_CURRENT_BINARY_DIR} clean
    COMMAND find
    ARGS ${CMAKE_CURRENT_BINARY_DIR} -name "CMakeCache.txt" | xargs rm -rf
    COMMAND find
    ARGS ${CMAKE_CURRENT_BINARY_DIR} -name "CMakeFiles" | xargs rm -rf
    COMMAND find
    ARGS ${CMAKE_CURRENT_BINARY_DIR} -name "Makefile" | xargs rm -rf
    COMMAND find
    ARGS ${CMAKE_CURRENT_BINARY_DIR} -name \"*.cmake\" | xargs rm -rf
    COMMAND find
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/localize -name "*.qm" | xargs rm -rf
    COMMAND rm
    ARGS -rf ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt
    TARGET  distclean
)
endif(UNIX)

#------- find lrelease & create qms ------------

# find lrelease binary
if(NOT QT_LRELEASE_EXECUTABLE)
find_program(QT_LRELEASE_EXECUTABLE
    NAMES lrelease
    PATHS ${QT_BINARY_DIR}
    NO_DEFAULT_PATH
)
endif(NOT QT_LRELEASE_EXECUTABLE)

# debian hack
if(EXISTS ${QT_BINARY_DIR}/lrelease-qt4)
set(QT_LRELEASE_EXECUTABLE ${QT_BINARY_DIR}/lrelease-qt4)
endif(EXISTS ${QT_BINARY_DIR}/lrelease-qt4)

if(QT_LRELEASE_EXECUTABLE)
message(STATUS "Found lrelease executable: " ${QT_LRELEASE_EXECUTABLE})
message(STATUS "Generating localize ...")
execute_process(COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/localize -name *.ts COMMAND xargs ${QT_LRELEASE_EXECUTABLE} -silent)
else(QT_LRELEASE_EXECUTABLE)
message(FATAL_ERROR "Could NOT find lrelease executable")
endif(QT_LRELEASE_EXECUTABLE)

#------- add icon & trmove console in win32 (mingw) ----------

if(WIN32)
    if(NOT MSVC)

        find_program(WINDRES
        NAMES windres.exe
        PATHS ${PATH}
        NO_DEFAULT_PATH
        )

        add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/qtaggerrc.o
        COMMAND ${WINDRES} -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/qtagger.rc
        -o ${CMAKE_CURRENT_BINARY_DIR}/qtaggerrc.o )

        set(QTAGGER_SRC ${QTAGGER_SRC} ${CMAKE_CURRENT_BINARY_DIR}/qtaggerrc.o)
    endif(NOT MSVC)
endif(WIN32)

#------- crating executable -----------

add_executable(qtagger ${QTAGGER_SRC} ${QTAGGER_MOC_CPP} ${QTAGGER_UI_H} ${QRC_SOURCES})

if (UNIX)
target_link_libraries( qtagger ${QT_LIBRARIES} ${TAGLIB_LDFLAGS} ${TAGLIB_CFLAGS} )
endif (UNIX)

if(WIN32)
    if(NOT MSVC)

        set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-mwindows")
        target_link_libraries( qtagger ${QT_LIBRARIES} ${TAGLIB_LIBRARIES} )

    endif(NOT MSVC)
endif(WIN32)

#------- installs unix -----------

if(UNIX AND NOT APPLE)
    INSTALL(TARGETS qtagger RUNTIME DESTINATION bin)
    INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/docs/" DESTINATION share/doc/qtagger)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/img/qtagger.png" DESTINATION share/pixmaps)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/qtagger.desktop" DESTINATION share/applications)
    INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/localize/" DESTINATION share/qtagger/localize FILES_MATCHING PATTERN "*.qm")


endif(UNIX AND NOT APPLE)
