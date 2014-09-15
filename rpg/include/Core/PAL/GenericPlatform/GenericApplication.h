#pragma once
#include "Core.h"
#include "GenericWindow.h"
//#include "SharedPointer.h"

class FGenericApplicationMessageHandler;
class ICursor;
//class ITextInputMethodSystem;
//class IForceFeedbackSystem;
//class IAnalyticsProvider;

	enum class EPopUpOrientationType
	{
		Horizontal,
		Vertical,
	};

/**
* FModifierKeysState stores the pressed state of keys that are commonly used as modifiers
*/
class FModifierKeysState
{

public:

	/**
	* Constructor.  Events are immutable once constructed.
	*
	* @param  bInIsLeftShiftDown  True if left shift is pressed
	* @param  bInIsRightShiftDown  True if right shift is pressed
	* @param  bInIsLeftControlDown  True if left control is pressed
	* @param  bInIsRightControlDown  True if right control is pressed
	* @param  bInIsLeftAltDown  True if left alt is pressed
	* @param  bInIsRightAltDown  True if right alt is pressed
	*/
	FModifierKeysState(const bool bInIsLeftShiftDown,
		const bool bInIsRightShiftDown,
		const bool bInIsLeftControlDown,
		const bool bInIsRightControlDown,
		const bool bInIsLeftAltDown,
		const bool bInIsRightAltDown)
		: bIsLeftShiftDown(bInIsLeftShiftDown),
		bIsRightShiftDown(bInIsRightShiftDown),
		bIsLeftControlDown(bInIsLeftControlDown),
		bIsRightControlDown(bInIsRightControlDown),
		bIsLeftAltDown(bInIsLeftAltDown),
		bIsRightAltDown(bInIsRightAltDown)
	{
	}


	/**
	* Returns true if either shift key was down when this event occurred
	*
	* @return  True if shift is pressed
	*/
	bool IsShiftDown() const
	{
		return bIsLeftShiftDown || bIsRightShiftDown;
	}

	/**
	* Returns true if left shift key was down when this event occurred
	*
	* @return  True if left shift is pressed
	*/
	bool IsLeftShiftDown() const
	{
		return bIsLeftShiftDown;
	}

	/**
	* Returns true if right shift key was down when this event occurred
	*
	* @return  True if right shift is pressed
	*/
	bool IsRightShiftDown() const
	{
		return bIsRightShiftDown;
	}

	/**
	* Returns true if either control key was down when this event occurred
	*
	* @return  True if control is pressed
	*/
	bool IsControlDown() const
	{
		return bIsLeftControlDown || bIsRightControlDown;
	}

	/**
	* Returns true if left control key was down when this event occurred
	*
	* @return  True if left control is pressed
	*/
	bool IsLeftControlDown() const
	{
		return bIsLeftControlDown;
	}

	/**
	* Returns true if right control key was down when this event occurred
	*
	* @return  True if right control is pressed
	*/
	bool IsRightControlDown() const
	{
		return bIsRightControlDown;
	}

	/**
	* Returns true if either alt key was down when this event occurred
	*
	* @return  True if alt is pressed
	*/
	bool IsAltDown() const
	{
		return bIsLeftAltDown || bIsRightAltDown;
	}

	/**
	* Returns true if left alt key was down when this event occurred
	*
	* @return  True if left alt is pressed
	*/
	bool IsLeftAltDown() const
	{
		return bIsLeftAltDown;
	}

	/**
	* Returns true if right alt key was down when this event occurred
	*
	* @return  True if right alt is pressed
	*/
	bool IsRightAltDown() const
	{
		return bIsRightAltDown;
	}


private:

	/** True if the left shift key was down when this event occurred. */
	bool bIsLeftShiftDown;

	/** True if the right shift key was down when this event occurred. */
	bool bIsRightShiftDown;

	/** True if the left control key was down when this event occurred. */
	bool bIsLeftControlDown;

	/** True if the right control key was down when this event occurred. */
	bool bIsRightControlDown;

	/** True if the left alt key was down when this event occurred. */
	bool bIsLeftAltDown;

	/** True if the right alt key was down when this event occurred. */
	bool bIsRightAltDown;
};

struct FPlatformRect
{
	int32 Left;
	int32 Top;
	int32 Right;
	int32 Bottom;
};

/**
* Contains info on a physical monitor connected to the display device
*/
struct FMonitorInfo
{
	std::tstring Name;
	std::tstring ID;
	int32 NativeWidth;
	int32 NativeHeight;
	bool bIsPrimary;
};

/**
* Contains metrics information for the desktop area
*/
struct FDisplayMetrics
{
	FDisplayMetrics() : TitleSafePaddingSize(0, 0), ActionSafePaddingSize(0, 0) { }

	/** Width of the primary display in pixels */
	int32 PrimaryDisplayWidth;

	/** Height of the primary display in pixels */
	int32 PrimaryDisplayHeight;

	/** Info on connected physical monitors. Only available on platforms where this information is accessible (PC currently) */
	std::vector<FMonitorInfo> MonitorInfo;

	/** Area of the primary display not covered by task bars or other docked widgets */
	FPlatformRect PrimaryDisplayWorkAreaRect;

	/** Virtual display coordinate range (includes all active displays) */
	FPlatformRect VirtualDisplayRect;

	/** The safe area for all content on TVs (see http://en.wikipedia.org/wiki/Safe_area_%28television%29) - content will be inset TitleSafePaddingSize.X on left _and_ right */
	Vector2D TitleSafePaddingSize;

	/** The safe area for less important spill over on TVs (see TitleSafePaddingSize) */
	Vector2D ActionSafePaddingSize;
};

/**
* Generic platform application interface
*/
class GenericApplication
{
public:

	GenericApplication()//const std::shared_ptr< ICursor >& InCursor)
		//: Cursor(InCursor)
		//, MessageHandler(MakeShareable(new FGenericApplicationMessageHandler()))
	{

	}

	virtual ~GenericApplication() {}

	virtual void SetMessageHandler(const std::shared_ptr < FGenericApplicationMessageHandler >& InMessageHandler) { MessageHandler = InMessageHandler; }

	virtual void PollGameDeviceState(const float TimeDelta) { }

	virtual void PumpMessages(const float TimeDelta) { }

	virtual void ProcessDeferredEvents(const float TimeDelta) { }

	virtual void Tick(const float TimeDelta) { }

	virtual std::shared_ptr < GenericWindow > MakeWindow() { return std::shared_ptr<GenericWindow>(new GenericWindow()); }

	virtual void InitializeWindow(const std::shared_ptr < GenericWindow >& Window, const std::shared_ptr < GenericWindowDefinition > & InDefinition, const std::shared_ptr< GenericWindow >& InParent, const bool bShowImmediately) { }

	virtual void SetCapture(const std::shared_ptr< GenericWindow >& InWindow) { }

	virtual void* GetCapture(void) const { return NULL; }

	virtual FModifierKeysState GetModifierKeys() const  { return FModifierKeysState(false, false, false, false, false, false); }

	virtual void SetHighPrecisionMouseMode(const bool Enable, const std::shared_ptr< GenericWindow >& InWindow) { };

	virtual bool IsUsingHighPrecisionMouseMode() const { return false; }

	virtual bool IsUsingTrackpad() const { return false; }

	virtual FPlatformRect GetWorkArea(const FPlatformRect& CurrentWindow) const
	{
		FPlatformRect OutRect;
		OutRect.Left = 0;
		OutRect.Top = 0;
		OutRect.Right = 0;
		OutRect.Bottom = 0;

		return OutRect;
	}

	virtual bool TryCalculatePopupWindowPosition(const FPlatformRect& InAnchor, const Vector2D& InSize, const EPopUpOrientationType Orientation, /*OUT*/ Vector2D* const CalculatedPopUpPosition) const { return false; }

	virtual void GetDisplayMetrics(FDisplayMetrics& OutDisplayMetrics) const { }

	virtual void GetInitialDisplayMetrics(FDisplayMetrics& OutDisplayMetrics) const { GetDisplayMetrics(OutDisplayMetrics); }

	virtual void DestroyApplication() { }

	/** Function to return the current implementation of the ForceFeedback system */
	//virtual IForceFeedbackSystem *GetForceFeedbackSystem() { return NULL; }

	/** Function to return the current implementation of the Text Input Method System */
	//virtual ITextInputMethodSystem *GetTextInputMethodSystem() { return NULL; }

	/** Send any analytics captured by the application */
	//virtual void SendAnalytics(IAnalyticsProvider* Provider) { }

	virtual bool SupportsSystemHelp() const { return false; }

	virtual void ShowSystemHelp() {}

public:

	//const std::shared_ptr< ICursor > Cursor;

protected:

	std::shared_ptr < class FGenericApplicationMessageHandler > MessageHandler;
};