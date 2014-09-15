set( PROJECT_NAME
tinyxml
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${CURRENT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/3rdParty/base64
${CMAKE_SOURCE_DIR}/3rdParty/tinyxml
${CMAKE_SOURCE_DIR}/3rdParty/zlib-1.2.5
)

#------ target -----
add_library (${PROJECT_NAME} STATIC ${MY_SRC} ${MY_HEADERS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET ${PROJECT_NAME}		PROPERTY FOLDER "3rd Party")
endif()


