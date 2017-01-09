
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${OCC_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${XercesC_INCLUDE_DIRS}
)

set(McCad_LIBS
    FreeCADApp
)

SET(McCad_SRCS
    AppMcCad.cpp
    PreCompiled.cpp
    PreCompiled.h
)

add_library(McCad SHARED ${McCad_SRCS})
target_link_libraries(McCad ${McCad_LIBS})


fc_target_copy_resource(McCad 
    ${CMAKE_SOURCE_DIR}/src/Mod/McCad
    ${CMAKE_BINARY_DIR}/Mod/McCad
    Init.py)

SET_BIN_DIR(McCad McCad /Mod/McCad)
SET_PYTHON_PREFIX_SUFFIX(McCad)

install(TARGETS McCad DESTINATION ${CMAKE_INSTALL_LIBDIR})
