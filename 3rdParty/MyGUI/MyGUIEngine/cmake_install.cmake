# Install script for directory: C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/sdk")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/lib/Release/MyGUIEngine.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Release" TYPE SHARED_LIBRARY FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/bin/Release/MyGUIEngine.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/lib/RelWithDebInfo/MyGUIEngine.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/RelWithDebInfo" TYPE SHARED_LIBRARY FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/bin/RelWithDebInfo/MyGUIEngine.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/lib/MinSizeRel/MyGUIEngine.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/MinSizeRel" TYPE SHARED_LIBRARY FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/bin/MinSizeRel/MyGUIEngine.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/lib/Debug/MyGUIEngine_d.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Debug" TYPE SHARED_LIBRARY FILES "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/bin/Debug/MyGUIEngine_d.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MYGUI" TYPE FILE FILES
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Allocator.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_CustomAllocator.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DDItemInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IBItemInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MenuItemType.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResizingPolicy.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_WidgetToolTip.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Button.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Canvas.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ComboBox.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DDContainer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_EditBox.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ImageBox.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ItemBox.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ListBox.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MenuBar.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MenuControl.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MenuItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MultiListBox.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_PopupMenu.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ProgressBar.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ScrollBar.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ScrollView.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TextBox.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TabControl.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TabItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MultiListItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Widget.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Window.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Bitwise.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Constants.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_CoordConverter.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DataFileStream.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DataStream.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Delegate.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DelegateImplement.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DynLib.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Enumerator.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_EventPair.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_GeometryUtility.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_StringUtility.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TextChangeHistory.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TextIterator.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TextureUtility.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TextView.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TextViewData.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Timer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_UString.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_WidgetTranslate.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_XmlDocument.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ConsoleLogListener.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_FileLogListener.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ILogFilter.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ILogListener.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LevelLogFilter.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LogLevel.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LogManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LogSource.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LogStream.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_BackwardCompatibility.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Common.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DeprecatedTypes.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DeprecatedWidgets.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Diagnostic.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Exception.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_GenericFactory.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Macros.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Platform.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Precompiled.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Prerequest.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_RenderFormat.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_WidgetDefines.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ICroppedRectangle.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IDataStream.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IItemContainer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IObject.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ISerializable.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ITexture.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IUnlinkWidget.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IVertexBuffer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Plugin.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_RTTI.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Singleton.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_BiIndexBase.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ScrollViewBase.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_WidgetInput.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_WidgetUserData.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_EditText.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MainSkin.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_PolygonalSkin.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_RotatingSkin.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SimpleText.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SubSkin.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TileRect.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IStateInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ISubWidget.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ISubWidgetRect.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ISubWidgetText.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LayerItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LayerNode.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_OverlappedLayer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_RenderItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SharedLayer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SharedLayerNode.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SkinItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ILayer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ILayerItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ILayerNode.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IRenderTarget.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ActionController.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ControllerEdgeHide.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ControllerFadeAlpha.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ControllerItem.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ControllerPosition.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceImageSet.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceImageSetPointer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceLayout.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceManualFont.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceManualPointer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceSkin.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceTrueTypeFont.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IFont.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IPointer.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_IResource.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ChildSkinInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_FontData.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LayoutData.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MaskPickInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceImageSetData.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SubWidgetBinding.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SubWidgetInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Align.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Any.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Colour.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_CommonStateInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_FlowDirection.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ImageInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_KeyCode.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_MouseButton.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_RenderTargetInfo.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TCoord.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TPoint.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TRect.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_TSize.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Types.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Version.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_VertexData.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_WidgetStyle.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ClipboardManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ControllerManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DataManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_DynLibManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_FactoryManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_FontManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_Gui.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_InputManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LanguageManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LayerManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_LayoutManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_PluginManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_PointerManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_RenderManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ResourceManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SkinManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_SubWidgetManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_ToolTipManager.h"
    "C:/Users/piaoa_000/Documents/GitHub/Fwankie/3rdParty/MyGUI/MyGUIEngine/include/MyGUI_WidgetManager.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

