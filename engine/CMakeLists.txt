set( PROJECT_NAME
ENGINE
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${CURRENT_INCLUDE_DIRS}
${DIRECTX_SDK_DIR}/include
${CMAKE_SOURCE_DIR}/hge/core/include
${CMAKE_SOURCE_DIR}/hge/helpers/include
${CMAKE_SOURCE_DIR}/rpg/include
${RPG_INCLUDE_DIRS}
${MYGUI_SOURCE_DIR}/Platforms/DirectX/HGEPlatform/include
${MYGUI_SOURCE_DIR}/MyGUIEngine/include
${MYGUI_SOURCE_DIR}/Common/Input/Win32
${MYGUI_SOURCE_DIR}/Common/Base/DirectX
${MYGUI_SOURCE_DIR}/Common
)

#------ link directories listed ------
#link_directories( ${HGE_SOURCE_DIR}/lib )
link_directories(
${DIRECTX_SDK_DIR}/lib
${DIRECTX_SDK_DIR}/lib/x64
${DIRECTX_SDK_DIR}/lib/x86
)
link_libraries(
${DirectX_D3DX9_LIBRARY}
${DirectX_LIBRARY}
Common
hgeb2draw
)

#------ target -----
add_library (${PROJECT_NAME} STATIC ${MY_SRC} ${MY_HEADERS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	#SET_PROPERTY(TARGET ${PROJECT_NAME}		PROPERTY FOLDER "HGE")
endif()






