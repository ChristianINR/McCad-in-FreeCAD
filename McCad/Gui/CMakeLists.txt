include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${COIN3D_INCLUDE_DIRS}
    ${QT_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
)

set(McCadGui_LIBS
    McCad
    FreeCADGui
)

set(McCadGui_MOC_HDRS
    MaterialWindow.hpp
)

fc_wrap_cpp(McCadGui_MOC_SRCS ${McCadGui_MOC_HDRS})
SOURCE_GROUP("Moc" FILES ${McCadGui_MOC_SRCS})

qt4_add_resources(McCadGui_QRC_SRCS Resources/McCad.qrc)

set(McCadGui_UIC_SRCS
    MaterialWindow.ui
)

qt4_wrap_ui(McCadGui_UIC_HDRS ${McCadGui_UIC_SRCS})

SET(McCadGui_SRCS
    ${McCadGui_QRC_SRCS}
    #${McCad_UIC_HDRS}
    AppMcCadGui.cpp
    Command.cpp
    McCadUtils.cpp
    McCadUtils.h
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
    MaterialWindow.cpp
    MaterialWindow.hpp
    MaterialWindow.ui
)

SET(McCadGui_DLGS_SRCS
    MaterialWindow.ui
)
SOURCE_GROUP("Dialogs" FILES ${McCadGui_DLGS_SRCS})

add_library(McCadGui SHARED ${McCadGui_SRCS})
target_link_libraries(McCadGui ${McCadGui_LIBS})

fc_target_copy_resource(McCadGui
    ${CMAKE_SOURCE_DIR}/src/Mod/McCad
    ${CMAKE_BINARY_DIR}/Mod/McCad
    InitGui.py)

SET_BIN_DIR(McCadGui McCadGui /Mod/McCad)
SET_PYTHON_PREFIX_SUFFIX(McCadGui)

install(TARGETS McCadGui DESTINATION ${CMAKE_INSTALL_LIBDIR})


SET(McCadGuiIcon_SVG
    Resources/icons/kit.svg
)

fc_copy_sources(McCadGui "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/Mod/McCad" ${McCadGuiIcon_SVG})

INSTALL(FILES ${McCadGuiIcon_SVG} DESTINATION "${CMAKE_INSTALL_DATADIR}/Mod/McCad/Resources/icons")

