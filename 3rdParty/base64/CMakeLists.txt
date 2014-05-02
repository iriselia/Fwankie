project( BASE64 )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE BASE64_SOURCES ${BASE64_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE BASE64_HEADERS ${BASE64_SOURCE_DIR}/include/*.h)

set (BASE64_INCLUDE_DIRS "")
foreach (_headerFile ${BASE64_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND BASE64_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES BASE64_INCLUDE_DIRS)

include_directories( ${BASE64_INCLUDE_DIRS} )

#------ target -----
add_library( base64 STATIC ${BASE64_SOURCES} ${BASE64_HEADERS} )

if( MSVC )

    SET_TARGET_PROPERTIES( base64 PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET base64		PROPERTY FOLDER "3rd Party")
endif()
