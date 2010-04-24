# qTagger Cmake build script
cmake_minimum_required( VERSION 2.6 )

# set project's name
project( QTAGGER )

message(STATUS "System: " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

find_package( Qt4 REQUIRED )
include( "${QT_USE_FILE}" )
include(FindPkgConfig)

# -------------------------------------------

# add version define
set(QTAGGER_VERSION "0.93")
add_definitions( -DVERSION="${QTAGGER_VERSION}")

# -------------------------------------------

# build type
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# -------------------------------------------

# installl prefix
set(CMAKE_INSTALL_PREFIX "/usr")

add_definitions( -DPREFIX="${CMAKE_INSTALL_PREFIX}")

message(STATUS "Indtall prefix: " ${CMAKE_INSTALL_PREFIX})

# -------------------------------------------

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# -------------------------------------------

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
#set( QTAGGER_QRC qtagger.qrc )

  # this will run uic on .ui files:
qt4_wrap_ui(QTAGGER_UI_H ${QTAGGER_UI} )

# genereate moc headers
qt4_wrap_cpp(QTAGGER_MOC_CPP ${QTAGGER_MOC} )

# genereating resource cpp
#qt4_add_resources( QRC_SOURCES ${QTAGGER_QRC} )


# --- TODO - add docs section

#---------------------------

# taglib
pkg_check_modules(TAGLIB taglib)

include_directories(${TAGLIB_INCLUDE_DIRS})
link_directories(${TAGLIB_LIBRARY_DIRS})

#-------------------------------------

#add_executable(qtagger ${QTAGGER_SRC} ${QTAGGER_MOC_CPP} ${QTAGGER_UI_H} ${QRC_SOURCES})
add_executable(qtagger ${QTAGGER_SRC} ${QTAGGER_MOC_CPP} ${QTAGGER_UI_H} )

target_link_libraries( qtagger ${QT_LIBRARIES} ${TAGLIB_LDFLAGS} ${TAGLIB_CFLAGS} )
