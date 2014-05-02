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


#--- 3rd Party library ---
add_subdirectory( 3rdParty/zlib-1.2.5 )
add_subdirectory( 3rdParty/libPNG )
add_subdirectory( 3rdParty/tinyxml )
add_subdirectory( 3rdParty/base64 )
add_subdirectory( 3rdParty/TmxParser )

#--- HGE core library and helpers ---
add_subdirectory( hge/helpers )
add_subdirectory( hge/core )

#--- HGE TOOLS - comment out of not needed ---
#add_subdirectory( hge/tools/fontconv )
#add_subdirectory( hge/tools/fonted )
#add_subdirectory( hge/tools/particleed )
#add_subdirectory( hge/tools/pngopt )
#add_subdirectory( hge/tools/texasm )

#--- Box2D ---
#add_subdirectory( Box2D )

#--- Game Project ---
add_subdirectory( rpg )

if( ${HGE_DIRECTX_VER} MATCHES "9" )
    #add_subdirectory( tutorials/tutorial05_shaders )
endif()
