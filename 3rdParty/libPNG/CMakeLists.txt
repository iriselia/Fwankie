project( HGELIBPNG )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( HGELIBPNG_SRC
    png.c
    pngerror.c
    pnggccrd.c
    pngget.c
    pngmem.c
    pngpread.c
    pngread.c
    pngrio.c
    pngrtran.c
    pngrutil.c
    pngset.c
    pngtrans.c
    pngvcrd.c
    pngwio.c
    pngwrite.c
    pngwtran.c
    pngwutil.c
    png.h
    pngconf.h    )

#------ additional includes ------
include_directories( ${HGECORE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/3rdParty )
include_directories( ${CMAKE_SOURCE_DIR}/3rdParty/zlib-1.2.5 )

#------ link directories listed ------
link_directories( ${CMAKE_SOURCE_DIR}/lib )

#------ target -----
add_library( hgelibpng STATIC ${HGELIBPNG_SRC} )

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET hgelibpng		PROPERTY FOLDER "3rd Party")
endif()