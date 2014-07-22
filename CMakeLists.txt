## HGE CMake script including HGEHELP and examples
##
project( FWANKIE )
cmake_minimum_required( VERSION 2.8 )


##----------------------------------------
## Edit this to match your configuration
##----------------------------------------

##--- set this to 8 or 9 ---
SET( HGE_DIRECTX_VER "9" )
## SET( DIRECTX_SDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)" )
SET( DIRECTX_SDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)" )

SET( HGE_UNICODE "1" )

if(WIN32)
add_definitions( "-DPLATFORM_WINDOWS" )
endif(WIN32)

##----------------------------------------
## End of manual configuration section
## try to minimize tampering with code below unless you know how CMake works
##----------------------------------------

add_definitions( "-DHGE_DIRECTX_VER=${HGE_DIRECTX_VER}" "-DHGE_UNICODE=${HGE_UNICODE}" )
# disable warnings on STD non conformance and security issues
add_definitions( "-D_CRT_SECURE_NO_WARNINGS" "-D_CRT_NONSTDC_NO_WARNINGS" "-D_SCL_SECURE_NO_WARNINGS" "-D_WIN32_WINNT=0x0501" "/MP" )
## add_definitions( /MDd )

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FWANKIE_SOURCE_DIR}/bin CACHE PATH "Single Directory for all executables." )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${FWANKIE_SOURCE_DIR}/bin_debug CACHE PATH "Single Directory for all executables." )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FWANKIE_SOURCE_DIR}/lib CACHE PATH "Single Directory for all static libraries." )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${FWANKIE_SOURCE_DIR}/lib CACHE PATH "Single Directory for all static libraries." )
SET( CMAKE_PDB_OUTPUT_DIRECTORY ${FWANKIE_SOURCE_DIR}/bin_debug/pdb CACHE PATH "Single Directory for all static libraries." )

SET( CMAKE_INCLUDE_CURRENT_DIR ON )

    # create_source_group(relativeSourcePath sourceGroupName files)
    #
    # Creates a source group with the specified name relative to the relative path
    # specified.
    #
    # Parameters:
    #    - sourceGroupName: Name of the source group to create.
    #    - relativeSourcePath: Relative path to the files.
    #    - sourceFiles: Files to add to the source group.
    #
    # For example if you have the following directory structure:
    #
    #    - ExampleApplication
    #        - include
    #            - Main.h
    #                - Window
    #                    Window.h
    #        - source
    #            - Main.cpp
    #                - Window
    #                    Window.cpp
    #
    # You can get your list of files and call create_source_group the following way
    #
    #    file(GLOB_RECURSE my_source_files ${CMAKE_CURRENT_SOURCE_DIR}/source/*)
    #    create_source_group("Source Files"
	#	"${CMAKE_CURRENT_SOURCE_DIR}/source" ${my_source_files})
    #    file(GLOB_RECURSE my_header_files ${CMAKE_CURRENT_SOURCE_DIR}/include/*)
    #    create_source_group("Header Files"
	#	"${CMAKE_CURRENT_SOURCE_DIR}/include" ${my_header_files})
    #    add_executable(ExampleApplication ${my_source_files} ${my_header_files})
    #
    # Then the generated solution would look like this
    #
    #    - ExampleApplication (project)
    #        - Header Files
    #            - Main.h
    #                - Window
    #                    Window.h
    #        - Source Files
    #            - Main.cpp
    #                - Window
    #                    Window.cpp
    #
	
    function(create_source_group sourceGroupName relativeSourcePath sourceFiles)
	    FOREACH(currentSourceFile ${ARGN})
            FILE(RELATIVE_PATH folder ${relativeSourcePath} ${currentSourceFile})
            get_filename_component(filename ${folder} NAME)
            string(REPLACE ${filename} "" folder ${folder})
            if(NOT folder STREQUAL "")
                string(REGEX REPLACE "/+$" "" folderlast ${folder})
                string(REPLACE "/" "\\" folderlast ${folderlast})
                SOURCE_GROUP("${sourceGroupName}\\${folderlast}" FILES ${currentSourceFile})
            endif(NOT folder STREQUAL "")
        ENDFOREACH(currentSourceFile ${ARGN})
		
        FOREACH(currentSourceFile ${sourceFiles})
            FILE(RELATIVE_PATH folder ${relativeSourcePath} ${currentSourceFile})
            get_filename_component(filename ${folder} NAME)
            string(REPLACE ${filename} "" folder ${folder})
            if(NOT folder STREQUAL "")
                string(REGEX REPLACE "/+$" "" folderlast ${folder})
                string(REPLACE "/" "\\" folderlast ${folderlast})
                SOURCE_GROUP("${sourceGroupName}\\${folderlast}" FILES ${currentSourceFile})
            endif(NOT folder STREQUAL "")
        ENDFOREACH(currentSourceFile ${sourceFiles})
		
		
		
		
    endfunction(create_source_group)

#--- 3rd Party library ---
add_subdirectory( 3rdParty/zlib-1.2.5 )
add_subdirectory( 3rdParty/libPNG )
add_subdirectory( 3rdParty/tinyxml )
add_subdirectory( 3rdParty/base64 )
add_subdirectory( 3rdParty/TmxParser )
add_subdirectory( 3rdParty/TmxParser_Test )
add_subdirectory( 3rdParty/MyGUI )
add_subdirectory( 3rdParty/Box2D )
#add_subdirectory( 3rdParty/OIS )

#--- HGE core library and helpers ---
add_subdirectory( hge/helpers )
add_subdirectory( hge/core )
add_subdirectory( hge/hgeb2draw )

#--- HGE TOOLS - comment out if not needed ---
#add_subdirectory( hge/tools/fontconv )
#add_subdirectory( hge/tools/fonted )
#add_subdirectory( hge/tools/particleed )
#add_subdirectory( hge/tools/pngopt )
#add_subdirectory( hge/tools/texasm )

#--- Box2D ---
#add_subdirectory( Box2D )

#--- Game Project ---
add_subdirectory( engine )
add_subdirectory( server )
add_subdirectory( rpg )

if( ${HGE_DIRECTX_VER} MATCHES "9" )
    #add_subdirectory( tutorials/tutorial05_shaders )
endif()
