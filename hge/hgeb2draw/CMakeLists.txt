project( HGEB2DRAW )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE HGEB2DRAW_SOURCES ${HGEB2DRAW_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HGEB2DRAW_HEADERS ${HGEB2DRAW_SOURCE_DIR}/include/*.h)

set (HGEB2DRAW_INCLUDE_DIRS "")
foreach (_headerFile ${HGEB2DRAW_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND HGEB2DRAW_INCLUDE_DIRS ${_dir})
endforeach()
#list(REMOVE_DUPLICATES HGEB2DRAW_INCLUDE_DIRS)
include_directories( ${HGEB2DRAW_INCLUDE_DIRS} )

#------ additional includes ------
include_directories(
${FWANKIE_SOURCE_DIR}/3rdParty/Box2D
${FWANKIE_SOURCE_DIR}/rpg/include
)

include_directories( ${HGEHELPERS_SOURCE_DIR}/include )
#include_directories( ${HGE_SOURCE_DIR}/include )

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/lib )
link_libraries( hge )
link_libraries( Box2D )

#------ target -----
add_library (hgeb2draw STATIC ${HGEB2DRAW_SOURCES} ${HGEB2DRAW_HEADERS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET hgeb2draw		PROPERTY FOLDER "HGE")
endif()
