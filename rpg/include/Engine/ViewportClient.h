/**
* An abstract interface to a viewport's client.
* The viewport's client processes input received by the viewport, and draws the viewport.
*/
class ViewportClient
{
public:
	/** The different types of sound stat flags */
	struct ESoundShowFlags
	{
		enum Type
		{
			Disabled = 0x00,
			Debug = 0x01,
			Sort_Distance = 0x02,
			Sort_Class = 0x04,
			Sort_Name = 0x08,
			Sort_WavesNum = 0x10,
			Sort_Disabled = 0x20,
			Long_Names = 0x40,
		};
	};

	virtual ~ViewportClient(){}
	virtual void Precache() {}
	virtual void RedrawRequested(FViewport* Viewport) { Viewport->Draw(); }
	virtual void RequestInvalidateHitProxy(FViewport* Viewport) { Viewport->InvalidateHitProxy(); }
	virtual void Draw(FViewport* Viewport, FCanvas* Canvas) {}
	virtual void ProcessScreenShots(FViewport* Viewport) {}
	virtual UWorld* GetWorld() const { return NULL; }
	virtual struct FEngineShowFlags* GetEngineShowFlags() { return NULL; }

	/**
	* Check a key event received by the viewport.
	* If the viewport client uses the event, it should return true to consume it.
	* @param	Viewport - The viewport which the key event is from.
	* @param	ControllerId - The controller which the key event is from.
	* @param	Key - The name of the key which an event occured for.
	* @param	Event - The type of event which occured.
	* @param	AmountDepressed - For analog keys, the depression percent.
	* @param	bGamepad - input came from gamepad (ie xbox controller)
	* @return	True to consume the key event, false to pass it on.
	*/
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed = 1.f, bool bGamepad = false) { return false; }

	/**
	* Check an axis movement received by the viewport.
	* If the viewport client uses the movement, it should return true to consume it.
	* @param	Viewport - The viewport which the axis movement is from.
	* @param	ControllerId - The controller which the axis movement is from.
	* @param	Key - The name of the axis which moved.
	* @param	Delta - The axis movement delta.
	* @param	DeltaTime - The time since the last axis update.
	* @param	NumSamples - The number of device samples that contributed to this Delta, useful for things like smoothing
	* @param	bGamepad - input came from gamepad (ie xbox controller)
	* @return	True to consume the axis movement, false to pass it on.
	*/
	virtual bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamepad = false) { return false; }

	/**
	* Check a character input received by the viewport.
	* If the viewport client uses the character, it should return true to consume it.
	* @param	Viewport - The viewport which the axis movement is from.
	* @param	ControllerId - The controller which the axis movement is from.
	* @param	Character - The character.
	* @return	True to consume the character, false to pass it on.
	*/
	virtual bool InputChar(FViewport* Viewport, int32 ControllerId, TCHAR Character) { return false; }

	/**
	* Check a key event received by the viewport.
	* If the viewport client uses the event, it should return true to consume it.
	* @param	Viewport - The viewport which the event is from.
	* @param	ControllerId - The controller which the key event is from.
	* @param	Handle - Identifier unique to this touch event
	* @param	Type - What kind of touch event this is (see ETouchType)
	* @param	TouchLocation - Screen position of the touch
	* @param	DeviceTimestamp - Timestamp of the event
	* @param	TouchpadIndex - For devices with multiple touchpads, this is the index of which one
	* @return	True to consume the key event, false to pass it on.
	*/
	virtual bool InputTouch(FViewport* Viewport, int32 ControllerId, uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp, uint32 TouchpadIndex) { return false; }

	/**
	* Check a gesture event received by the viewport.
	* If the viewport client uses the event, it should return true to consume it.
	* @param	Viewport - The viewport which the event is from.
	* @param	GestureType - @todo desc
	* @param	GestureDelta - @todo desc
	* @return	True to consume the gesture event, false to pass it on.
	*/
	virtual bool InputGesture(FViewport* Viewport, EGestureEvent::Type GestureType, const FVector2D& GestureDelta) { return false; }

	/**
	* Each frame, the input system will update the motion data.
	*
	* @param Viewport - The viewport which the key event is from.
	* @param ControllerId - The controller which the key event is from.
	* @param Tilt			The current orientation of the device
	* @param RotationRate	How fast the tilt is changing
	* @param Gravity		Describes the current gravity of the device
	* @param Acceleration  Describes the acceleration of the device
	* @return	True to consume the motion event, false to pass it on.
	*/
	virtual bool InputMotion(FViewport* Viewport, int32 ControllerId, const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration) { return false; }

	virtual void SetIsSimulateInEditorViewport(bool bInIsSimulateInEditorViewport) { };

	virtual bool WantsPollingMouseMovement(void) const { return true; }

	/**
	* Sets whether or not a controller is actively plugged in
	* @param InControllID - Unique ID of the joystick
	* @param bInConnected - true, if the joystick is valid for input
	*/
	virtual void OnJoystickPlugged(const uint32 InControllerID, const uint32 InType, const uint32 bInConnected) {};

	virtual void MouseEnter(FViewport* Viewport, int32 x, int32 y) {}

	virtual void MouseLeave(FViewport* Viewport) {}

	virtual void MouseMove(FViewport* Viewport, int32 X, int32 Y) {}

	/**
	* Called when the mouse is moved while a window input capture is in effect
	*
	* @param	InViewport	Viewport that captured the mouse input
	* @param	InMouseX	New mouse cursor X coordinate
	* @param	InMouseY	New mouse cursor Y coordinate
	*/
	virtual void CapturedMouseMove(FViewport* InViewport, int32 InMouseX, int32 InMouseY) { }

	/**
	* Retrieves the cursor that should be displayed by the OS
	*
	* @param	Viewport	the viewport that contains the cursor
	* @param	X			the x position of the cursor
	* @param	Y			the Y position of the cursor
	*
	* @return	the cursor that the OS should display
	*/
	virtual EMouseCursor::Type GetCursor(FViewport* Viewport, int32 X, int32 Y) { return EMouseCursor::Default; }

	virtual void LostFocus(FViewport* Viewport) {}
	virtual void ReceivedFocus(FViewport* Viewport) {}
	virtual bool IsFocused(FViewport* Viewport) { return true; }

	virtual void CloseRequested(FViewport* Viewport) {}

	virtual bool RequiresHitProxyStorage() { return true; }

	/**
	* Determines whether this viewport client should receive calls to InputAxis() if the game's window is not currently capturing the mouse.
	* Used by the UI system to easily receive calls to InputAxis while the viewport's mouse capture is disabled.
	*/
	virtual bool RequiresUncapturedAxisInput() const { return false; }

	/**
	* Determine if the viewport client is going to need any keyboard input
	* @return true if keyboard input is needed
	*/
	virtual bool RequiresKeyboardInput() const { return true; }

	/**
	* Returns true if this viewport is orthogonal.
	* If hit proxies are ever used in-game, this will need to be
	* overridden correctly in GameViewportClient.
	*/
	virtual bool IsOrtho() const { return false; }

	/**
	* Returns true if this viewport is excluding non-game elements from its display
	*/
	virtual bool IsInGameView() const { return false; }

	/**
	* Sets GWorld to the appropriate world for this client
	*
	* @return the previous GWorld
	*/
	virtual class UWorld* ConditionalSetWorld() { return NULL; }

	/**
	* Restores GWorld to InWorld
	*
	* @param InWorld	The world to restore
	*/
	virtual void ConditionalRestoreWorld(class UWorld* InWorld) {}

	/**
	* Allow viewport client to override the current capture region
	*
	* @param OutCaptureRegion    Ref to rectangle where we will write the overridden region
	* @return true if capture region has been overridden, false otherwise
	*/
	virtual bool OverrideHighResScreenshotCaptureRegion(FIntRect& OutCaptureRegion) { return false; }

	/**
	* Get a ptr to the stat unit data for this viewport
	*/
	virtual FStatUnitData* GetStatUnitData() const { return NULL; }

	/**
	* Get a ptr to the stat unit data for this viewport
	*/
	virtual FStatHitchesData* GetStatHitchesData() const { return NULL; }

	/**
	* Get a ptr to the enabled stats list
	*/
	virtual const TArray<FString>* GetEnabledStats() const { return NULL; }

	/**
	* Sets all the stats that should be enabled for the viewport
	*/
	virtual void SetEnabledStats(const TArray<FString>& InEnabledStats) {}

	/**
	* Check whether a specific stat is enabled for this viewport
	*/
	virtual bool IsStatEnabled(const TCHAR* InName) const { return false; }

	/**
	* Get the sound stat flags enabled for this viewport
	*/
	virtual ESoundShowFlags::Type GetSoundShowFlags() const { return ESoundShowFlags::Disabled; }

	/**
	* Set the sound stat flags enabled for this viewport
	*/
	virtual void SetSoundShowFlags(const ESoundShowFlags::Type InSoundShowFlags) {}
};