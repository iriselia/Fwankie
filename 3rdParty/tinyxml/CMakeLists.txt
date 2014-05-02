project( TINYXML )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE TINYXML_SOURCES ${TINYXML_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TINYXML_HEADERS ${TINYXML_SOURCE_DIR}/include/*.h)

set (TINYXML_INCLUDE_DIRS "")
foreach (_headerFile ${TINYXML_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND TINYXML_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES TINYXML_INCLUDE_DIRS)

include_directories( ${TINYXML_INCLUDE_DIRS} )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/base64 )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/tinyxml )
include_directories( ${FWANKIE_SOURCE_DIR}/3rdParty/zlib-1.2.5 )


#------ target -----
add_library( tinyxml STATIC ${TINYXML_SOURCES} ${TINYXML_HEADERS} )

if( MSVC )

    SET_TARGET_PROPERTIES( tinyxml PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET tinyxml		PROPERTY FOLDER "3rd Party")
endif()
