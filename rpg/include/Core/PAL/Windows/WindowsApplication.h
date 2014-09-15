#pragma once
#include "Core.h"
#include "GenericApplication.h"

//#include "AllowWindowsPlatformTypes.h"
#include "Ole2.h"
#include "OleIdl.h"
//#include "HideWindowsPlatformTypes.h"
//#include "IForceFeedbackSystem.h"
//#include "WindowsTextInputMethodSystem.h"

class WindowsWindow;
class FGenericApplicationMessageHandler;

struct FDeferredWindowsMessage
{
	FDeferredWindowsMessage(const std::shared_ptr<WindowsWindow>& InNativeWindow, HWND InHWnd, uint32 InMessage, WPARAM InWParam, LPARAM InLParam, int32 InX = 0, int32 InY = 0, uint32 InRawInputFlags = 0)
	: NativeWindow(InNativeWindow)
	, hWND(InHWnd)
	, Message(InMessage)
	, wParam(InWParam)
	, lParam(InLParam)
	, X(InX)
	, Y(InY)
	, RawInputFlags(InRawInputFlags)
	{}
	/** Native window that received the message */
	std::weak_ptr<WindowsWindow> NativeWindow;
	/** Window handle */
	HWND hWND;
	/** Message code */
	uint32 Message;
	/** Message data */
	WPARAM wParam;
	LPARAM lParam;
	/** Mouse coordinates */
	int32 X;
	int32 Y;
	uint32 RawInputFlags;
};

namespace EWindowsDragDropOperationType
{
	enum Type
	{
		DragEnter,
		DragOver,
		DragLeave,
		Drop
	};
}

struct DragDropOLEData
{
	enum EWindowsOLEDataType
	{
		None,
		Text,
		Files
	};

	DragDropOLEData()
		: Type(None)
	{}

	std::tstring OperationText;
	std::vector<std::tstring> OperationFilenames;
	EWindowsOLEDataType Type;
};

struct FDeferredWindowsDragDropOperation
{
private:
	// Private constructor. Use the factory functions below.
	FDeferredWindowsDragDropOperation()
		: HWnd(NULL)
		, KeyState(0)
	{
		CursorPosition.x = 0;
		CursorPosition.y = 0;
	}

public:
	static FDeferredWindowsDragDropOperation MakeDragEnter(HWND InHwnd, const DragDropOLEData& InOLEData, ::DWORD InKeyState, POINTL InCursorPosition)
	{
		FDeferredWindowsDragDropOperation NewOperation;
		NewOperation.OperationType = EWindowsDragDropOperationType::DragEnter;
		NewOperation.HWnd = InHwnd;
		NewOperation.OLEData = InOLEData;
		NewOperation.KeyState = InKeyState;
		NewOperation.CursorPosition = InCursorPosition;
		return NewOperation;
	}

	static FDeferredWindowsDragDropOperation MakeDragOver(HWND InHwnd, ::DWORD InKeyState, POINTL InCursorPosition)
	{
		FDeferredWindowsDragDropOperation NewOperation;
		NewOperation.OperationType = EWindowsDragDropOperationType::DragOver;
		NewOperation.HWnd = InHwnd;
		NewOperation.KeyState = InKeyState;
		NewOperation.CursorPosition = InCursorPosition;
		return NewOperation;
	}

	static FDeferredWindowsDragDropOperation MakeDragLeave(HWND InHwnd)
	{
		FDeferredWindowsDragDropOperation NewOperation;
		NewOperation.OperationType = EWindowsDragDropOperationType::DragLeave;
		NewOperation.HWnd = InHwnd;
		return NewOperation;
	}

	static FDeferredWindowsDragDropOperation MakeDrop(HWND InHwnd, const DragDropOLEData& InOLEData, ::DWORD InKeyState, POINTL InCursorPosition)
	{
		FDeferredWindowsDragDropOperation NewOperation;
		NewOperation.OperationType = EWindowsDragDropOperationType::Drop;
		NewOperation.HWnd = InHwnd;
		NewOperation.OLEData = InOLEData;
		NewOperation.KeyState = InKeyState;
		NewOperation.CursorPosition = InCursorPosition;
		return NewOperation;
	}

	EWindowsDragDropOperationType::Type OperationType;

	HWND HWnd;
	DragDropOLEData OLEData;
	::DWORD KeyState;
	POINTL CursorPosition;
};

/**
* Windows-specific application implementation.
*/
class WindowsApplication : public GenericApplication //, IForceFeedbackSystem
{

public:

	/**
	* Static: Creates a new Win32 application
	*
	* @param	InstanceHandle  Win32 instance handle
	* @param	IconHandle		Win32 application icon handle
	*
	* @return  New application object
	*/
	static WindowsApplication* CreateWindowsApplication(const HINSTANCE InstanceHandle, const HICON IconHandle);


public:

	virtual ~WindowsApplication();

	virtual void DestroyApplication() OVERRIDE;


public:

	virtual void SetMessageHandler(const std::shared_ptr < class FGenericApplicationMessageHandler >& InMessageHandler) OVERRIDE;

	virtual void PollGameDeviceState(const float TimeDelta) OVERRIDE;

	virtual void PumpMessages(const float TimeDelta) OVERRIDE;

	virtual void ProcessDeferredEvents(const float TimeDelta) OVERRIDE;

	virtual std::shared_ptr < GenericWindow > MakeWindow() OVERRIDE;

	virtual void WindowsApplication::InitializeWindow(const std::shared_ptr < GenericWindow >& InWindow, const std::shared_ptr < GenericWindowDefinition >& InDefinition, const std::shared_ptr < GenericWindow >& InParent, const bool bShowImmediately);

	virtual void SetCapture(const std::shared_ptr< GenericWindow >& InWindow) OVERRIDE;

	virtual void* GetCapture(void) const OVERRIDE;

	virtual void SetHighPrecisionMouseMode(const bool Enable, const std::shared_ptr< GenericWindow >& InWindow) OVERRIDE;

	virtual bool IsUsingHighPrecisionMouseMode() const OVERRIDE{ return bUsingHighPrecisionMouseInput; }

	virtual FModifierKeysState GetModifierKeys() const OVERRIDE;

	virtual FPlatformRect GetWorkArea(const FPlatformRect& CurrentWindow) const OVERRIDE;

	//virtual bool TryCalculatePopupWindowPosition(const FPlatformRect& InAnchor, const Vector2D& InSize, const EPopUpOrientationType Orientation, /*OUT*/ Vector2D* const CalculatedPopUpPosition) const OVERRIDE;

	virtual void GetDisplayMetrics(FDisplayMetrics& OutDisplayMetrics) const OVERRIDE;

	virtual void GetInitialDisplayMetrics(FDisplayMetrics& OutDisplayMetrics) const OVERRIDE;

// 	virtual IForceFeedbackSystem *GetForceFeedbackSystem() OVERRIDE
// 	{
// 		return this;
// 	}

	//virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) OVERRIDE;

	//virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &Values) OVERRIDE;

// 	virtual ITextInputMethodSystem *GetTextInputMethodSystem() OVERRIDE
// 	{
// 		return TextInputMethodSystem.Get();
// 	}

protected:

	static LRESULT CALLBACK AppWndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

	int32 ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

	int32 ProcessDeferredMessage(const FDeferredWindowsMessage& DeferredMessage);

	void ProcessDeferredDragDropOperation(const FDeferredWindowsDragDropOperation& Op);

public:

	/** Called by a window when an OLE Drag and Drop operation occurred on a non-game thread */
	void DeferDragDropOperation(const FDeferredWindowsDragDropOperation& DeferredDragDropOperation);

	/** Invoked by a window when an OLE Drag and Drop first enters it. */
	HRESULT OnOLEDragEnter(const HWND HWnd, const DragDropOLEData& OLEData, ::DWORD KeyState, POINTL CursorPosition, ::DWORD *CursorEffect);

	/** Invoked by a window when an OLE Drag and Drop moves over the window. */
	HRESULT OnOLEDragOver(const HWND HWnd, ::DWORD KeyState, POINTL CursorPosition, ::DWORD *CursorEffect);

	/** Invoked by a window when an OLE Drag and Drop exits the window. */
	HRESULT OnOLEDragOut(const HWND HWnd);

	/** Invoked by a window when an OLE Drag and Drop is dropped onto the window. */
	HRESULT OnOLEDrop(const HWND HWnd, const DragDropOLEData& OLEData, ::DWORD KeyState, POINTL CursorPosition, ::DWORD *CursorEffect);


private:

	WindowsApplication(const HINSTANCE HInstance, const HICON IconHandle);

	/** Registers the Windows class for windows and assigns the application instance and icon */
	static bool RegisterClass(const HINSTANCE HInstance, const HICON HIcon);

	/**  @return  True if a windows message is related to user input (mouse, keyboard) */
	static bool IsInputMessage(uint32 msg);

	void DeferMessage(std::shared_ptr<WindowsWindow>& NativeWindow, HWND InHWnd, uint32 InMessage, WPARAM InWParam, LPARAM InLParam, int32 MouseX = 0, int32 MouseY = 0, uint32 RawInputFlags = 0);

	void CheckForShiftUpEvents(const int32 KeyCode);

private:

	static const IntPoint MinimizedWindowPosition;

	HINSTANCE InstanceHandle;

	bool bUsingHighPrecisionMouseInput;

	std::vector< FDeferredWindowsMessage > DeferredMessages;

	std::vector< FDeferredWindowsDragDropOperation > DeferredDragDropOperations;

	std::vector< std::shared_ptr<WindowsWindow> > Windows;

	std::shared_ptr< class XInputInterface > XInput;

	/** List of input devices implemented in external modules. */
	std::vector< std::shared_ptr<class IInputDevice> > ExternalInputDevices;
	bool bHasLoadedInputPlugins;

	std::vector< int32 > PressedModifierKeys;

	//FAutoConsoleVariableRef CVarDeferMessageProcessing;

	int32 bAllowedToDeferMessageProcessing;

	/** True if we are in the middle of a windows modal size loop */
	bool bInModalSizeLoop;

	FDisplayMetrics InitialDisplayMetrics;

	//std::shared_ptr<FWindowsTextInputMethodSystem> TextInputMethodSystem;
};