set( PROJECT_NAME
hgehelpers
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${CURRENT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/hge/core/include
${CMAKE_SOURCE_DIR}/3rdParty/Box2D
)

#------ link directories listed ------
link_directories( ${CMAKE_SOURCE_DIR}/lib )

#------ target -----
add_library (${PROJECT_NAME} STATIC ${MY_SRC} ${MY_HEADERS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET ${PROJECT_NAME}		PROPERTY FOLDER "HGE")
endif()


#------ precompiled headers support (not done for now) ------
## if (MSVC)
##     set( PRECOMP_FILENAME "precompiled_headers" )
##     set_source_files_properties( ${PRECOMP_FILENAME}.cpp PROPERTIES COMPILE_FLAGS "/Yc${PRECOMP_FILENAME}.h" )
##     foreach( src_file ${HGEHELPERS_SRC} )
##         set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yu${PRECOMP_FILENAME}.h" )
##     endforeach( src_file ${HGEHELPERS_SRC} )
##     list( APPEND HGEHELPERS_SRC ${PRECOMP_FILENAME}.cpp ${PRECOMP_FILENAME}.h )
## endif (MSVC)
