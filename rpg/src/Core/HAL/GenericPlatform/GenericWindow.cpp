#include "GenericWindow.h"

GenericWindow::GenericWindow()
{

}

GenericWindow::~GenericWindow()
{

}

void GenericWindow::ReshapeWindow(int32 X, int32 Y, int32 Width, int32 Height)
{
	// empty default functionality
}

bool GenericWindow::GetFullScreenInfo(int32& X, int32& Y, int32& Width, int32& Height) const
{
	// this function cannot return valid results, and should not be needed on consoles, etc
	//UE_LOG(LogGenericPlatformWindow, Fatal, TEXT("GetFullScreenInfo is not expected to be called on this platform"));
	return false;
}

void GenericWindow::MoveWindowTo(int32 X, int32 Y)
{
	// empty default functionality
}

void GenericWindow::BringToFront(bool bForce)
{
	// empty default functionality
}

void GenericWindow::HACK_ForceToFront()
{
	// empty default functionality
}

void GenericWindow::Destroy()
{
	// empty default functionality
}

void GenericWindow::Minimize()
{
	// empty default functionality
}

void GenericWindow::Maximize()
{
	// empty default functionality
}

void GenericWindow::Restore()
{
	// empty default functionality
}

void GenericWindow::Show()
{
	// empty default functionality
}

void GenericWindow::Hide()
{
	// empty default functionality
}

void GenericWindow::SetWindowMode(EWindowModeType InNewWindowMode)
{
	// empty default functionality
}

EWindowModeType GenericWindow::GetWindowMode() const
{
	// default functionality
	return EWindowModeType::Windowed;
}

bool GenericWindow::IsMaximized() const
{
	// empty default functionality
	return true;
}

bool GenericWindow::IsVisible() const
{
	// empty default functionality
	return true;
}

bool GenericWindow::GetRestoredDimensions(int32& X, int32& Y, int32& Width, int32& Height)
{
	// this function cannot return valid results, and should not be needed on consoles, etc
	//UE_LOG(LogGenericPlatformWindow, Fatal, TEXT("GetRestoredDimensions is not expected to be called on this platform"));
	return false;
}

void GenericWindow::SetWindowFocus()
{
	// empty default functionality
}

void GenericWindow::SetOpacity(const float InOpacity)
{
	// empty default functionality
}

void GenericWindow::Enable(bool bEnable)
{
	// empty default functionality
}

bool GenericWindow::IsPointInWindow(int32 X, int32 Y) const
{
	// empty default functionality
	return true;
}

int32 GenericWindow::GetWindowBorderSize() const
{
	// empty default functionality
	return 0;
}

void* GenericWindow::GetOSWindowHandle() const
{
	// empty default functionality (for platforms that don't need an OS handle)
	return NULL;
}

bool GenericWindow::IsForegroundWindow() const
{
	// empty default functionality
	return true;
}

void GenericWindow::SetText(const TCHAR* const Text)
{
	// empty default functionality
}

const GenericWindowDefinition& GenericWindow::GetDefinition() const
{
	//TODO change to std::share_ptr
	return *Definition;
}

void GenericWindow::AdjustCachedSize(Vector2D& Size) const
{
}
