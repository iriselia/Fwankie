project( HGEHELPERS )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE HGEHELPERS_SOURCES ${HGEHELPERS_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HGEHELPERS_HEADERS ${HGEHELPERS_SOURCE_DIR}/include/*.h)

set (HGEHELPERS_INCLUDE_DIRS "")
foreach (_headerFile ${HGEHELPERS_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND HGEHELPERS_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES HGEHELPERS_INCLUDE_DIRS)

#------ additional includes ------
include_directories( ${HGEHELPERS_INCLUDE_DIRS} )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/Box2D )

#------ link directories listed ------
link_directories( ${FWANKIE_SOURCE_DIR}/lib )

#------ precompiled headers support (not done for now) ------
## if (MSVC)
##     set( PRECOMP_FILENAME "precompiled_headers" )
##     set_source_files_properties( ${PRECOMP_FILENAME}.cpp PROPERTIES COMPILE_FLAGS "/Yc${PRECOMP_FILENAME}.h" )
##     foreach( src_file ${HGEHELPERS_SRC} )
##         set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yu${PRECOMP_FILENAME}.h" )
##     endforeach( src_file ${HGEHELPERS_SRC} )
##     list( APPEND HGEHELPERS_SRC ${PRECOMP_FILENAME}.cpp ${PRECOMP_FILENAME}.h )
## endif (MSVC)

#------ target -----
add_library( hgehelpers STATIC ${HGEHELPERS_SOURCES} ${HGEHELPERS_HEADERS} )

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET hgehelpers		PROPERTY FOLDER "HGE")
endif()
