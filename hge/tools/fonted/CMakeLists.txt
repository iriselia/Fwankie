project( HGE_FONTEDIT )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( HGE_FONTEDIT_SRC
    commands.cpp
    fonted.cpp
    fontlist.cpp
    generate.cpp
    hgeguirange.cpp
    savepng.cpp
    fonted.h
    fontlist.h
    hgeguirange.h    )

#------ additional includes ------
include_directories( ${HGEHELPERS_SOURCE_DIR}/include )
include_directories( ${HGECORE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/3rdParty/libPNG )
include_directories( ${CMAKE_SOURCE_DIR}/3tdParty/zlib-1.2.5 )

include_directories( ${DIRECTX_SDK_DIR}/include )

#------ link directories listed ------
link_directories( ${CMAKE_SOURCE_DIR}/lib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
#if( ${HGE_DIRECTX_VER} MATCHES "8" )
#    link_libraries( d3d8 d3dx8 )
#endif()
#if( ${HGE_DIRECTX_VER} MATCHES "9" )
#    link_libraries( d3d9 d3dx9 )
#endif()
link_libraries( winmm )
link_libraries( hgelibpng zlib hgehelpers hge )

#------ target -----
add_executable( fonted WIN32 ${HGE_FONTEDIT_SRC} )

if( MSVC )
    SET_TARGET_PROPERTIES( fonted PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET fonted		PROPERTY FOLDER "Tools")
endif()
