set (PROJECTNAME MyGUI.HGEPlatform)

include_directories(
 include
 ${MYGUI_SOURCE_DIR}/MyGUIEngine/include
 ${DirectX_INCLUDE_DIR}
 ${MYGUI_SOURCE_DIR}/Common
 #${HGEHELPERS_INCLUDE_DIRS}
 ${FWANKIE_SOURCE_DIR}/hge/helpers/include
)

include(${PROJECTNAME}.list)

add_library(${PROJECTNAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

add_dependencies(${PROJECTNAME} MyGUIEngine)

target_link_libraries(${PROJECTNAME} ${MYGUI_LIBRARIES} hgehelpers)
#link_directories(${DirectX_LIBRARY_DIRS})

if( MSVC )
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
	SET_PROPERTY(TARGET ${PROJECTNAME}		PROPERTY FOLDER "3rd Party/MyGUI")
endif()