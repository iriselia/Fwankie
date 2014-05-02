project( TMXPARSER )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE TMXPARSER_SOURCES ${TMXPARSER_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TMXPARSER_HEADERS ${TMXPARSER_SOURCE_DIR}/include/*.h)

set (TMXPARSER_INCLUDE_DIRS "")
foreach (_headerFile ${TMXPARSER_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND TMXPARSER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES TMXPARSER_INCLUDE_DIRS)

include_directories( ${TMXPARSER_INCLUDE_DIRS} )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/base64/include )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/tinyxml/include )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/zlib-1.2.5 )

#------ link directories listed ------
link_directories( ${FWANKIE_SOURCE_DIR}/lib )
link_libraries( zlib tinyxml base64 )


#------ target -----
add_library( tmxparser STATIC ${TMXPARSER_SOURCES} ${TMXPARSER_HEADERS} )

if( MSVC )

    SET_TARGET_PROPERTIES( tmxparser PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET tmxparser		PROPERTY FOLDER "3rd Party")
endif()
