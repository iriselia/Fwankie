set( PROJECT_NAME
TESTCLIENT
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
)

#------ link directories listed ------
link_libraries(
Common
hgeb2draw
)

#------ target -----
add_executable (${PROJECT_NAME} WIN32 ${MY_SRC} ${MY_HEADERS})

