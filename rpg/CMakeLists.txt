project( RPG )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE MY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp)
#file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h)
create_source_group("Source Files" "${CMAKE_CURRENT_SOURCE_DIR}/src" ${MY_SRC})
file(GLOB_RECURSE MY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
create_source_group("Header Files" "${CMAKE_CURRENT_SOURCE_DIR}/include" ${MY_HEADERS})

set (MY_INCLUDE_DIRS "")
foreach (_headerFile ${MY_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND MY_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES MY_INCLUDE_DIRS)
include_directories( ${MY_INCLUDE_DIRS} )

#------ additional includes ------
include_directories(
${FWANKIE_SOURCE_DIR}/hge/core/include
${FWANKIE_SOURCE_DIR}/hge/helpers/include
${FWANKIE_SOURCE_DIR}/hge/hgeb2draw/include
${FWANKIE_SOURCE_DIR}/3rdParty/TmxParser/include
${FWANKIE_SOURCE_DIR}/3rdParty/libPNG 
${FWANKIE_SOURCE_DIR}/3rdParty/zlib-1.2.5
${FWANKIE_SOURCE_DIR}/3rdParty/Box2D
#${FWANKIE_SOURCE_DIR}/3rdParty/OIS/include
)

include_directories( ${DIRECTX_SDK_DIR}/include )

include_directories(
	${MYGUI_SOURCE_DIR}/Platforms/DirectX/HGEPlatform/include
	${MYGUI_SOURCE_DIR}/MyGUIEngine/include
	${MYGUI_SOURCE_DIR}/Common/Input/Win32
	${MYGUI_SOURCE_DIR}/Common/Base/DirectX
	${MYGUI_SOURCE_DIR}/Common
)
#------ link directories listed ------
#link_directories( ${HGE_SOURCE_DIR}/lib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
link_libraries( ${DirectX_D3DX9_LIBRARY} ${DirectX_LIBRARY} )
link_libraries( Common )
link_libraries( hge )
link_libraries( hgeb2draw )
link_libraries( tmxparser )
link_libraries( Box2D )

#------ target -----
#add_executable (RPG WIN32 ${RPG_SOURCES} ${RPG_HEADERS})
add_executable (RPG WIN32 ${MY_SRC} ${MY_HEADERS})

install (TARGETS RPG
         RUNTIME DESTINATION ${FWANKIE_SOURCE_DIR}/bin) #${PROJECT_BINARY_DIR}/bin)

if( MSVC )
    SET_TARGET_PROPERTIES( RPG PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()
