
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

qt4_add_resources(McCad_QRC_SRCS Resources/McCad.qrc)

SET(McCadGui_SRCS
    ${McCad_QRC_SRCS}
    AppMcCadGui.cpp
    Command.cpp
    McCadUtils.cpp
    McCadUtils.h
    PreCompiled.cpp
    PreCompiled.h
    Workbench.cpp
    Workbench.h
)

add_library(McCadGui SHARED ${McCadGui_SRCS})
target_link_libraries(McCadGui ${McCadGui_LIBS})

fc_target_copy_resource(McCadGui 
    ${CMAKE_SOURCE_DIR}/src/Mod/McCad
    ${CMAKE_BINARY_DIR}/Mod/McCad
    InitGui.py)

SET_BIN_DIR(McCadGui McCadGui /Mod/McCad)
SET_PYTHON_PREFIX_SUFFIX(McCadGui)
    
install(TARGETS McCadGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
