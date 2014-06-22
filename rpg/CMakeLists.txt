project( RPG )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE RPG_SOURCES ${RPG_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE RPG_HEADERS ${RPG_SOURCE_DIR}/include/*.h)

set (RPG_INCLUDE_DIRS "")
foreach (_headerFile ${RPG_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND RPG_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES RPG_INCLUDE_DIRS)
include_directories( ${RPG_INCLUDE_DIRS} )

#------ additional includes ------
include_directories(
${FWANKIE_SOURCE_DIR}/3rdParty/TmxParser/include
${FWANKIE_SOURCE_DIR}/3rdParty/libPNG 
${FWANKIE_SOURCE_DIR}/3rdParty/zlib-1.2.5
#${FWANKIE_SOURCE_DIR}/3rdParty/OIS/include
)

include_directories( ${HGEHELPERS_SOURCE_DIR}/include )
include_directories( ${DIRECTX_SDK_DIR}/include )
include_directories(
	${MYGUI_SOURCE_DIR}/Platforms/DirectX/HGEPlatform/include
	${MYGUI_SOURCE_DIR}/MyGUIEngine/include
	${MYGUI_SOURCE_DIR}/Common/Input/Win32
	${MYGUI_SOURCE_DIR}/Common/Base/DirectX
	${MYGUI_SOURCE_DIR}/Common
)
#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/lib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
link_libraries( ${DirectX_D3DX9_LIBRARY} ${DirectX_LIBRARY} )
link_libraries( Common )
link_libraries( hge )
link_libraries( tmxparser )

#------ target -----
add_executable (RPG WIN32 ${RPG_SOURCES} ${RPG_HEADERS})

if( MSVC )
    SET_TARGET_PROPERTIES( RPG PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()
