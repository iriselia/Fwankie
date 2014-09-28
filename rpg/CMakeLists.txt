set( PROJECT_NAME
RPG
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${DIRECTX_SDK_DIR}/include

${CMAKE_SOURCE_DIR}/hge/core/include
#${CMAKE_SOURCE_DIR}/hge/coredx11/include

${CMAKE_SOURCE_DIR}/hge/helpers/include
${CMAKE_SOURCE_DIR}/hge/hgeb2draw/include
${CMAKE_SOURCE_DIR}/3rdParty/TmxParser/include
${CMAKE_SOURCE_DIR}/3rdParty/libPNG 
${CMAKE_SOURCE_DIR}/3rdParty/zlib-1.2.5
${CMAKE_SOURCE_DIR}/3rdParty/Box2D
#${CMAKE_SOURCE_DIR}/3rdParty/OIS/include

${MYGUI_SOURCE_DIR}/Platforms/DirectX/HGEPlatform/include
${MYGUI_SOURCE_DIR}/MyGUIEngine/include
${MYGUI_SOURCE_DIR}/Common/Input/Win32
${MYGUI_SOURCE_DIR}/Common/Base/DirectX
${MYGUI_SOURCE_DIR}/Common
)

#------ link directories listed ------
link_directories(
${DIRECTX_SDK_DIR}/lib
${DIRECTX_SDK_DIR}/lib/x64
${DIRECTX_SDK_DIR}/lib/x86
)
link_libraries(
${DirectX_D3DX9_LIBRARY}
${DirectX_LIBRARY}
Common
#hge
hgedx11
hgeb2draw
tmxparser
Box2D
)
#------ directx version based link ------
link_libraries(
d3d11
d3dx11
d3dcompiler
)

#------ target -----
add_executable (${PROJECT_NAME} WIN32 ${MY_SRC} ${MY_HEADERS})