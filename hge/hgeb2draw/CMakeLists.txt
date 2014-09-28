set( PROJECT_NAME
hgeb2draw
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${CURRENT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/3rdParty/Box2D
${CMAKE_SOURCE_DIR}/rpg/include
${CMAKE_SOURCE_DIR}/hge/core/include
#${CMAKE_SOURCE_DIR}/hge/coredx11/include
${CMAKE_SOURCE_DIR}/hge/helpers/include
)

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/lib )
link_libraries(
#hgedx11
#hge
Box2D
)

#------ target -----
add_library (${PROJECT_NAME} STATIC ${MY_SRC} ${MY_HEADERS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET ${PROJECT_NAME}		PROPERTY FOLDER "HGE")
endif()
