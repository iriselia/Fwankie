set( PROJECT_NAME
SERVER
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${DIRECTX_SDK_DIR}/include
${CURRENT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/hge/core/include
${CMAKE_SOURCE_DIR}/hge/helpers/include
${CMAKE_SOURCE_DIR}/rpg/include
${RPG_INCLUDE_DIRS}
#${CMAKE_SOURCE_DIR}/3rdParty/OIS/include
)
link_libraries(
Common
hgeb2draw
)

#------ target -----
add_executable (${PROJECT_NAME} WIN32 ${MY_SRC} ${MY_HEADERS})