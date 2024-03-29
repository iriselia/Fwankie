

/*=============================================================================================
	WindowsPlatformMisc.h: Windows platform misc functions
==============================================================================================*/

#pragma once
#include "Core.h"

/**
* Windows implementation of the misc OS functions
**/
struct FWindowsPlatformMisc : public FGenericPlatformMisc
{
	static void PlatformPreInit();
	static void PlatformInit();
	static class GenericApplication* CreateApplication();
	static void SetGracefulTerminationHandler();
	static void GetEnvironmentVariable(const TCHAR* VariableName, TCHAR* Result, int32 ResultLength);
	static std::vector<uint8> GetMacAddress();
	static void SubmitErrorReport( const TCHAR* InErrorHist, EErrorReportModeType InMode );

#if !UE_BUILD_SHIPPING
	FORCEINLINE static bool IsDebuggerPresent()
	{
		return !!::IsDebuggerPresent(); 
	}
	FORCEINLINE static void DebugBreak()
	{
		if (IsDebuggerPresent())
		{
			::DebugBreak();
		}
	}
#endif

	static void PumpMessages(bool bFromMainLoop);
	static uint32 GetKeyMap( uint16* KeyCodes, std::tstring* KeyNames, uint32 MaxMappings );
	static uint32 GetCharKeyMap(uint16* KeyCodes, std::tstring* KeyNames, uint32 MaxMappings);
	static void SetUTF8Output();
	static void LocalPrint(const TCHAR *Message);
	static void RequestExit(bool Force);
	static const TCHAR* GetSystemErrorMessage(TCHAR* OutBuffer, int32 BufferCount, int32 Error);
	static void ClipboardCopy(const TCHAR* Str);
	static void ClipboardPaste(std::tstring& Dest);
	static void CreateGuid(class FGuid& Result);
	static EAppReturnTypeType MessageBoxExt( EAppMsgTypeType MsgType, const TCHAR* Text, const TCHAR* Caption );
	static void PreventScreenSaver();
	static bool CommandLineCommands();
	static bool Is64bitOperatingSystem();
	static bool IsValidAbsolutePathFormat(const std::tstring& Path);
	static int32 NumberOfCores();
	static int32 NumberOfCoresIncludingHyperthreads();
	static void LoadPreInitModules();
	static void LoadStartupModules();

	static uint32 GetLastError();

	static void RaiseException( uint32 ExceptionCode );

	static bool CoInitialize();
	static void CoUninitialize();

	/** 
	 * Determines the shader format for the plarform
	 *
	 * @return	Returns the shader format to be used by that platform
	 */
	static const TCHAR* GetNullRHIShaderFormat();

	/**
	 * Has the OS execute a command and path pair (such as launch a browser)
	 *
	 * @param ComandType OS hint as to the type of command 
	 * @param Command the command to execute
	 *
	 * @return whether the command was successful or not
	 */
	static bool OsExecute(const TCHAR* CommandType, const TCHAR* Command);

	/**
	 * Searches for a window that matches the window name or the title starts with a particular text. When
	 * found, it returns the title text for that window
	 *
	 * @param TitleStartsWith searches for a window that has partial information about the title
	 * @param OutTitle the string the data is copied into
	 *
	 * @return whether the window was found and the text copied or not
	 */
	static bool GetWindowTitleMatchingText(const TCHAR* TitleStartsWith, std::tstring& OutTitle);

	//////// Platform specific
	static int32	GetAppIcon();

	/** 
	 * Determines if we are running on the Windows version or newer
	 *
	 * @return	Returns true if the current Windows version if equal or newer than MajorVersion
	 */
	static bool VerifyWindowsMajorVersion(uint32 MajorVersion);

	/**
	 * Sample the displayed pixel color from anywhere on the screen using the OS
	 *
	 * @param	InScreenPos		The screen coords to sample for current pixel color
	 * @param	InGamma			Optional gamma correction to apply to the screen color
	 *
	 * @return					The color of the pixel displayed at the chosen location
	 */
	//static struct FLinearColor GetScreenPixelColor(const Vector2D& InScreenPos, float InGamma = 1.0f);

#if !UE_BUILD_SHIPPING
	static void PromptForRemoteDebugging(bool bIsEnsure);
#endif	//#if !UE_BUILD_SHIPPING

	FORCEINLINE static void PrefetchBlock(const void* InPtr, int32 NumBytes = 1)
	{
		const char* Ptr           = (const char*)InPtr;
		const int32 CacheLineSize = GetCacheLineSize();
		for (int32 LinesToPrefetch = (NumBytes + CacheLineSize - 1) / CacheLineSize; LinesToPrefetch; --LinesToPrefetch)
		{
			_mm_prefetch( Ptr, _MM_HINT_T0 );
			Ptr += CacheLineSize;
		}
	}

	FORCEINLINE static void Prefetch(void const* x, int32 offset = 0)
	{
		 _mm_prefetch( (char const*)(x) + offset, _MM_HINT_T0 );
	}

	/** 
	 * Determines if the cpuid instruction is supported on this processor
	 *
	 * @return	Returns true if cpuid is supported
	 */
	static bool HasCPUIDInstruction();

	/** 
	 * Uses cpuid instruction to get the vendor string
	 *
	 * @return	CPU vendor name
	 */
	static std::tstring GetCPUVendor();

	/**
	 * Uses cpuid instruction to get the vendor string
	 *
	 * @return	CPU info bitfield
	 *
	 *			Bits 0-3	Stepping ID
	 *			Bits 4-7	Model
	 *			Bits 8-11	Family
	 *			Bits 12-13	Processor type (Intel) / Reserved (AMD)
	 *			Bits 14-15	Reserved
	 *			Bits 16-19	Extended model
	 *			Bits 20-27	Extended family
	 *			Bits 28-31	Reserved
	 */
	static uint32 GetCPUInfo();

	static bool GetRegistryString(const std::tstring& InRegistryKey, const std::tstring& InValueName, bool bPerUserSetting, std::tstring& OutValue);

	/** 
	 * Provides a simpler interface for fetching and cleanup of registry value queries
	 *
	 * @param	InKey		The Key (folder) in the registry to search under
	 * @param	InSubKey	The Sub Key (folder) within the main Key to look for
	 * @param	InValueName	The Name of the Value (file) withing the Sub Key to look for
	 * @param	OutData		The Data entered into the Value
	 *
	 * @return	true, if it successfully found the Value
	 */
	static bool QueryRegKey( const HKEY InKey, const TCHAR* InSubKey, const TCHAR* InValueName, std::tstring& OutData );

	/**
	 * Gets Visual Studio common tools path.
	 *
	 * @param Version Version of VS to get (11 - 2012, 12 - 2013).
	 * @param OutData Output parameter with common tools path.
	 *
	 * @return Returns if succeeded.
	 */
	static bool GetVSComnTools(int32 Version, std::tstring& OutData);

	/**
	 * Returns the size of the cache line in bytes.
	 *
	 * @return The cache line size.
	 */
	static int32 GetCacheLineSize();

	/**
	* @return Windows path separator.
	*/
	static const TCHAR* GetDefaultPathSeparator();

	/** @return Get the name of the platform specific file manager (Explorer) */
	static std::tstring GetFileManagerName();
};

typedef FWindowsPlatformMisc FPlatformMisc;
