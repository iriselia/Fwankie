project( OIS )
cmake_minimum_required( VERSION 2.8 )

file(GLOB_RECURSE OIS_SOURCES ${OIS_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE OIS_HEADERS ${OIS_SOURCE_DIR}/include/*.h)

set (OIS_INCLUDE_DIRS "")
foreach (_headerFile ${OIS_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND OIS_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES OIS_INCLUDE_DIRS)
include_directories( ${OIS_INCLUDE_DIRS} )

#------ target -----
add_library (OIS STATIC ${OIS_SOURCES} ${OIS_HEADERS})

if( MSVC )
    SET_TARGET_PROPERTIES( OIS PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()
