set( PROJECT_NAME
tmxparser_test
)
cmake_minimum_required( VERSION 2.8 )
include( ScanSourceFiles )

#----- Enable Unicode -----
#add_definitions(-DUNICODE -D_UNICODE)

#------ additional includes ------
include_directories(
${CURRENT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/3rdParty/tmxparser/include
${CMAKE_SOURCE_DIR}/3rdParty/tinyxml/include
)

#------ link directories listed ------
link_libraries(
tmxparser
tinyxml
)

#------ target -----
add_executable (${PROJECT_NAME} WIN32 ${MY_SRC} ${MY_HEADERS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET ${PROJECT_NAME}		PROPERTY FOLDER "3rd Party")
endif()

if(WIN32)
   set_target_properties(TMXPARSER_TEST PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
   set_target_properties(TMXPARSER_TEST PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
   set_target_properties(TMXPARSER_TEST PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
   set_target_properties(TMXPARSER_TEST PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
   set_target_properties(TMXPARSER_TEST PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
   set_target_properties(TMXPARSER_TEST PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif(WIN32)


