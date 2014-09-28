set( PROJECT_NAME
hgedx11
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)
add_definitions( "-DHGE_DIRECTX_VER=11" )
#------ additional includes ------
include_directories(
${DIRECTX_SDK_DIR}/include
${CURRENT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/hge/helpers/include
${CMAKE_SOURCE_DIR}/3rdParty
${CMAKE_SOURCE_DIR}/3rdParty/libPNG
${CMAKE_SOURCE_DIR}/3rdParty/zlib-1.2.5
${CMAKE_SOURCE_DIR}/3rdParty/zlib-1.2.5/contrib/minizip
)

#------ link directories listed ------
link_directories(
${CMAKE_SOURCE_DIR}/lib
${DIRECTX_SDK_DIR}/lib
${DIRECTX_SDK_DIR}/lib/x86
${DIRECTX_SDK_DIR}/lib/x64
)
link_libraries(
winmm
zlib
hgehelpers
)
#------ directx version based link ------
link_libraries(
d3d11
d3dx11
d3dcompiler
)


#------ target -----
add_library( ${PROJECT_NAME} SHARED ${MY_SRC} ${MY_HEADERS} )
#add_dependencies( HGEHELPERS zlib )
add_library (${PROJECT_NAME}-static STATIC ${MY_SRC} ${MY_HEADERS})

if( MSVC )
    SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET ${PROJECT_NAME}		PROPERTY FOLDER "HGE")
	SET_PROPERTY(TARGET ${PROJECT_NAME}-static		PROPERTY FOLDER "HGE")
endif()

#------ precompiled headers support (not done for now) ------
## if (MSVC)
##     set( PRECOMP_FILENAME "precompiled_headers" )
##     set_source_files_properties( ${PRECOMP_FILENAME}.cpp PROPERTIES COMPILE_FLAGS "/Yc${PRECOMP_FILENAME}.h" )
##     foreach( src_file ${HGECORE_SRC} )
##         set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yu${PRECOMP_FILENAME}.h" )
##     endforeach( src_file ${HGECORE_SRC} )
##     list( APPEND HGECORE_SRC ${PRECOMP_FILENAME}.cpp ${PRECOMP_FILENAME}.h )
## endif (MSVC)
