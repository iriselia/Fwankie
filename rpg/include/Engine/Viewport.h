#include "Core.h"
#include "ViewportClient.h"
#include "InputCoreTypes.h"

/**
* Encapsulates the I/O of a viewport.
* The viewport display is implemented using the platform independent RHI.
*/
class FViewport //: public FRenderTarget, protected FRenderResource
{
public:
	/** delegate type for viewport resize events ( Params: FViewport* Viewport, uint32 ) */
	//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnViewportResized, FViewport*, uint32);
	
	/** Send when a viewport is resized */
	//static FOnViewportResized ViewportResizedEvent;

	// Constructor.
	FViewport(ViewportClient* InViewportClient);
	// Destructor
	virtual ~FViewport(){}

	// FViewport interface.
	virtual void* GetWindow() = 0;
	virtual void MoveWindow(int32 NewPosX, int32 NewPosY, int32 NewSizeX, int32 NewSizeY) = 0;

	virtual void Destroy() = 0;

	// New MouseCapture/MouseLock API
	virtual bool HasMouseCapture() const				{ return true; }
	virtual bool HasFocus() const					{ return true; }
	virtual bool IsForegroundWindow() const			{ return true; }
	virtual void CaptureMouse(bool bCapture)		{ }
	virtual void LockMouseToViewport(bool bLock)	{ }
	virtual void ShowCursor(bool bVisible)			{ }
	virtual bool UpdateMouseCursor(bool bSetCursor)	{ return true; }

	virtual void ShowSoftwareCursor(bool bVisible)		{ }
	virtual void SetSoftwareCursorPosition(Vector2D Position) { }
	virtual bool IsSoftwareCursorVisible() const { return false; }

	/**
	* Returns true if the mouse cursor is currently visible
	*
	* @return True if the mouse cursor is currently visible, otherwise false.
	*/
	virtual bool IsCursorVisible() const { return true; }

	virtual bool CaptureJoystickInput(bool Capture) = 0;
	virtual bool KeyState(FKey Key) const = 0;
	virtual int32 GetMouseX() const = 0;
	virtual int32 GetMouseY() const = 0;
	virtual void GetMousePos(IntPoint& MousePosition, const bool bLocalPosition = true) = 0;
	virtual float GetTabletPressure() { return 0.f; }
	virtual bool IsPenActive() { return false; }
	virtual void SetMouse(int32 x, int32 y) = 0;
	virtual bool IsFullscreen()	const { return WindowMode == EWindowModeType::Fullscreen || WindowMode == EWindowModeType::WindowedFullscreen; }
	virtual void ProcessInput(float DeltaTime) = 0;

	/**
	* @return A canvas that can be used while this viewport is being drawn to render debug elements on top of everything else
	*/  
	//virtual FCanvas* GetDebugCanvas() { return NULL; };

	/**
	* Indicate that the viewport should be block for vsync.
	*/
	virtual void SetRequiresVsync(bool bShouldVsync) {}

	/**
	* Sets PreCapture coordinates from the current position of the slate cursor.
	*/
	virtual void SetPreCaptureMousePosFromSlateCursor() {}

	/**
	*	Starts a new rendering frame. Called from the game thread thread.
	*/
	virtual void	EnqueueBeginRenderFrame();

	/**
	*	Starts a new rendering frame. Called from the rendering thread.
	*/
	virtual void	BeginRenderFrame();

	/**
	*	Ends a rendering frame. Called from the rendering thread.
	*	@param bPresent		Whether the frame should be presented to the screen
	*	@param bLockToVsync	Whether the GPU should block until VSYNC before presenting
	*/
	virtual void	EndRenderFrame(bool bPresent, bool bLockToVsync);

	/**
	* @return whether or not this Controller has a keyboard available to be used
	**/
	virtual bool IsKeyboardAvailable(int32 ControllerID) const { return true; }

	/**
	* @return whether or not this Controller has a mouse available to be used
	**/
	virtual bool IsMouseAvailable(int32 ControllerID) const { return true; }


	/**
	* @return aspect ratio that this viewport should be rendered at
	*/
	virtual float GetDesiredAspectRatio() const
	{
		IntPoint Size = GetSizeXY();
		return (float)Size.X / (float)Size.Y;
	}

	/**
	* Invalidates the viewport's displayed pixels.
	*/
	virtual void InvalidateDisplay() = 0;

	/**
	* Updates the viewport's displayed pixels with the results of calling ViewportClient->Draw.
	*
	* @param	bShouldPresent	Whether we want this frame to be presented
	*/
	void Draw(bool bShouldPresent = true);

	/**
	* Invalidates the viewport's cached hit proxies at the end of the frame.
	*/
	//virtual void DeferInvalidateHitProxy();

	/**
	* Invalidates cached hit proxies
	*/
	//void InvalidateHitProxy();

	/**
	* Invalidates cached hit proxies and the display.
	*/
	//void Invalidate();

	//const TArray<FColor>& GetRawHitProxyData(FIntRect InRect);

	/**
	* Copies the hit proxies from an area of the screen into a buffer.
	* InRect must be entirely within the viewport's client area.
	* If the hit proxies are not cached, this will call ViewportClient->Draw with a hit-testing canvas.
	*/
	//void GetHitProxyMap(FIntRect InRect, TArray<HHitProxy*>& OutMap);

	/**
	* Returns the dominant hit proxy at a given point.  If X,Y are outside the client area of the viewport, returns NULL.
	* Caution is required as calling Invalidate after this will free the returned HHitProxy.
	*/
	//HHitProxy* GetHitProxy(int32 X, int32 Y);

	/**
	* Retrieves the interface to the viewport's frame, if it has one.
	* @return The viewport's frame interface.
	*/
	virtual FViewportFrame* GetViewportFrame() = 0;

	/**
	* Calculates the view inside the viewport when the aspect ratio is locked.
	* Used for creating cinematic bars.
	* @param Aspect [in] ratio to lock to
	* @param ViewRect [in] unconstrained view rectangle
	* @return	constrained view rectangle
	*/
	FIntRect CalculateViewExtents(float AspectRatio, const FIntRect& ViewRect);

	/**
	*	Sets a viewport client if one wasn't provided at construction time.
	*	@param InViewportClient	- The viewport client to set.
	**/
	virtual void SetViewportClient(ViewportClient* InViewportClient);

	// FRenderTarget interface.
	virtual IntPoint GetSizeXY() const { return IntPoint(SizeX, SizeY); }

	// Accessors.
	ViewportClient* GetClient() const { return ViewportClient; }

	/**
	* Globally enables/disables rendering
	*
	* @param bIsEnabled true if drawing should occur
	* @param PresentAndStopMovieDelay Number of frames to delay before enabling bPresent in RHIEndDrawingViewport, and before stopping the movie
	*/
	static void SetGameRenderingEnabled(bool bIsEnabled, int32 PresentAndStopMovieDelay = 0);

	/**
	* Returns whether rendering is globally enabled or disabled.
	* @return	true if rendering is globally enabled, otherwise false.
	**/
	bool IsGameRenderingEnabled()	{ return bIsGameRenderingEnabled; }

	/**
	* Handles freezing/unfreezing of rendering
	*/
	virtual void ProcessToggleFreezeCommand();

	/**
	* Returns if there is a command to freeze
	*/
	virtual bool HasToggleFreezeCommand();

	/**
	* Accessors for RHI resources
	*/
	//const FViewportRHIRef& GetViewportRHI() const { return ViewportRHI; }

	/**
	* Update the render target surface RHI to the current back buffer
	*/
	//void UpdateRenderTargetSurfaceRHIToCurrentBackBuffer();

	/**
	* First chance for viewports to render custom stats text
	* @param InCanvas - Canvas for rendering
	* @param InX - Starting X for drawing
	* @param InY - Starting Y for drawing
	* @return - Y for next stat drawing
	*/
// 	virtual int32 DrawStatsHUD(FCanvas* InCanvas, const int32 InX, const int32 InY)
// 	{
// 		return InY;
// 	}

	/**
	* Sets the initial size of this viewport.  Will do nothing if the viewport has already been sized
	*
	* @param InitialSizeXY	The initial size of the viewport
	*/
	void SetInitialSize(IntPoint InitialSizeXY);

	/** Returns true if this is an FSlateSceneViewport */
	bool IsSlateViewport() const { return bIsSlateViewport; }

	/** The current version of the running instance */
	std::tstring AppVersionString;

	/** Trigger a high res screenshot. Returns true if the screenshot can be taken, and false if it can't. The screenshot
	* can fail if the requested multiplier makes the screen too big for the GPU to cope with
	**/
	bool TakeHighResScreenShot();

protected:

	/** The viewport's client. */
	ViewportClient* ViewportClient;

	/**
	* Updates the viewport RHI with the current viewport state.
	* @param bDestroyed - True if the viewport has been destroyed.
	*/
	virtual void UpdateViewportRHI(bool bDestroyed, uint32 NewSizeX, uint32 NewSizeY, EWindowModeType NewWindowMode);

	/**
	* Take a high-resolution screenshot and save to disk.
	*/
	void HighResScreenshot();

protected:

	/** A map from 2D coordinates to cached hit proxies. */
// 	class FHitProxyMap : public FHitProxyConsumer, public FRenderTarget, public FGCObject
// 	{
// 	public:
// 
// 		/** Constructor */
// 		FHitProxyMap();
// 
// 		/** Destructor */
// 		ENGINE_API virtual ~FHitProxyMap();
// 
// 		/** Initializes the hit proxy map with the given dimensions. */
// 		void Init(uint32 NewSizeX, uint32 NewSizeY);
// 
// 		/** Releases the hit proxy resources. */
// 		void Release();
// 
// 		/** Invalidates the cached hit proxy map. */
// 		void Invalidate();
// 
// 		// FHitProxyConsumer interface.
// 		virtual void AddHitProxy(HHitProxy* HitProxy);
// 
// 		// FRenderTarget interface.
// 		virtual FIntPoint GetSizeXY() const { return FIntPoint(SizeX, SizeY); }
// 
// 		/** FGCObject interface */
// 		virtual void AddReferencedObjects(FReferenceCollector& Collector) OVERRIDE;
// 
// 		const FTexture2DRHIRef& GetHitProxyTexture(void) const		{ return HitProxyTexture; }
// 		const FTexture2DRHIRef& GetHitProxyCPUTexture(void) const		{ return HitProxyCPUTexture; }
// 
// 	private:
// 
// 		/** The width of the hit proxy map. */
// 		uint32 SizeX;
// 
// 		/** The height of the hit proxy map. */
// 		uint32 SizeY;
// 
// 		/** References to the hit proxies cached by the hit proxy map. */
// 		TArray<TRefCountPtr<HHitProxy> > HitProxies;
// 
// 		FTexture2DRHIRef HitProxyTexture;
// 		FTexture2DRHIRef HitProxyCPUTexture;
// 	};

	/** The viewport's hit proxy map. */
	//FHitProxyMap HitProxyMap;

	/** Cached hit proxy data. */
	//TArray<FColor> CachedHitProxyData;

	/** The RHI viewport. */
	//FViewportRHIRef ViewportRHI;

	/** The width of the viewport. */
	uint32 SizeX;

	/** The height of the viewport. */
	uint32 SizeY;

	/** The size of the region to check hit proxies */
	uint32 HitProxySize;

	/** What is the current window mode. */
	EWindowModeType WindowMode;

	/** True if the viewport client requires hit proxy storage. */
	//uint32 bRequiresHitProxyStorage : 1;

	/** True if the hit proxy buffer buffer has up to date hit proxies for this viewport. */
	//uint32 bHitProxiesCached : 1;

	/** If a toggle freeze request has been made */
	uint32 bHasRequestedToggleFreeze : 1;

	/** If true this viewport is an FSlateSceneViewport */
	uint32 bIsSlateViewport : 1;

	/** true if we should draw game viewports (has no effect on Editor viewports) */
	static bool bIsGameRenderingEnabled;

	/** Delay in frames to disable present (but still render scene) and stopping of a movie. This is useful to keep playing a movie while driver caches things on the first frame, which can be slow. */
	static int32 PresentAndStopMovieDelay;

	/** Triggers the taking of a high res screen shot for this viewport. */
	bool bTakeHighResScreenShot;
	// FRenderResource interface.
	virtual void InitDynamicRHI();
	virtual void ReleaseDynamicRHI();
	virtual void InitRHI();
	virtual void ReleaseRHI();
};
