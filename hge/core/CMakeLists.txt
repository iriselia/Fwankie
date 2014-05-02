project( HGECORE )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE HGECORE_SOURCES ${HGECORE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HGECORE_HEADERS ${HGECORE_SOURCE_DIR}/include/*.h)

set (HGECORE_INCLUDE_DIRS "")
foreach (_headerFile ${HGECORE_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND HGECORE_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES HGECORE_INCLUDE_DIRS)

#------ additional includes ------
include_directories( ${HGECORE_INCLUDE_DIRS} )
include_directories( ${FWANKIE_SOURCE_DIR}/hge/helpers/include )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/libPNG )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/zlib-1.2.5 )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/zlib-1.2.5/contrib/minizip )
## include_directories( ${HGE_SOURCE_DIR}/src )

include_directories( ${DIRECTX_SDK_DIR}/include )

#------ link directories listed ------
link_directories( ${FWANKIE_SOURCE_DIR}/lib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x86 ${DIRECTX_SDK_DIR}/lib/x64 )
if( ${HGE_DIRECTX_VER} MATCHES "8" )
    link_libraries( d3d8 d3dx8 )
endif()
if( ${HGE_DIRECTX_VER} MATCHES "9" )
    link_libraries( d3d9 d3dx9 )
endif()
link_libraries( winmm )
link_libraries( zlib hgehelpers )

#------ precompiled headers support (not done for now) ------
## if (MSVC)
##     set( PRECOMP_FILENAME "precompiled_headers" )
##     set_source_files_properties( ${PRECOMP_FILENAME}.cpp PROPERTIES COMPILE_FLAGS "/Yc${PRECOMP_FILENAME}.h" )
##     foreach( src_file ${HGECORE_SRC} )
##         set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yu${PRECOMP_FILENAME}.h" )
##     endforeach( src_file ${HGECORE_SRC} )
##     list( APPEND HGECORE_SRC ${PRECOMP_FILENAME}.cpp ${PRECOMP_FILENAME}.h )
## endif (MSVC)

#------ target (for creating HGE.DLL) -----
add_library( hge SHARED ${HGECORE_SOURCES} ${HGECORE_HEADERS})
add_dependencies( hge hgezlib )



#------ target (for creating static HGE.LIB) -----
add_library( hge-static STATIC ${HGECORE_SOURCES} ${HGECORE_HEADERS} )

if( MSVC )
    SET_TARGET_PROPERTIES( hge PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET hge		PROPERTY FOLDER "HGE")
	SET_PROPERTY(TARGET hge-static		PROPERTY FOLDER "HGE")
endif()
