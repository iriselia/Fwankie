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

add_definitions( "-DHGE_DIRECTX_VER=${HGE_DIRECTX_VER}" "-DHGE_UNICODE=${HGE_UNICODE}" )
# disable warnings on STD non conformance and security issues
add_definitions( "-D_CRT_SECURE_NO_WARNINGS" "-D_CRT_NONSTDC_NO_WARNINGS" "-D_SCL_SECURE_NO_WARNINGS" "-D_WIN32_WINNT=0x0501" "/MP" )
## add_definitions( /MDd )

SET( HGE_UNICODE "1" )

if(WIN32)
add_definitions( "-DPLATFORM_WINDOWS" )
endif(WIN32)

# Include necessary submodules
set(CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/CMake"
)

include(SourceFileFinder)
include(SetOutputDirectories)

#--- HGE core library and helpers ---
add_subdirectory( hge/helpers )
add_subdirectory( hge/core )
add_subdirectory( hge/hgeb2draw )

#--- 3rd Party library ---
add_subdirectory( 3rdParty/zlib-1.2.5 )
add_subdirectory( 3rdParty/libPNG )
add_subdirectory( 3rdParty/tinyxml )
add_subdirectory( 3rdParty/base64 )
add_subdirectory( 3rdParty/TmxParser )
#add_subdirectory( 3rdParty/TmxParser_Test )
add_subdirectory( 3rdParty/MyGUI )
add_subdirectory( 3rdParty/Box2D )
#add_subdirectory( 3rdParty/OIS )

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
add_subdirectory( testclient )
add_subdirectory( rpg )

if( ${HGE_DIRECTX_VER} MATCHES "9" )
    #add_subdirectory( tutorials/tutorial05_shaders )
endif()
