// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	GenericPlatformMisc.cpp: Generic implementations of misc platform functions
=============================================================================*/

#include "Core.h"
#include "GenericPlatformMisc.h"
#include "GenericApplication.h"

//#include "MallocAnsi.h"
// #include "GenericPlatformChunkInstall.h"
// #include "HAL/FileManagerGeneric.h"
// #include "ModuleManager.h"
// #include "VarargsHelper.h"
// #include "SecureHash.h"
// #include "Containers/Map.h"
// #include "../../Launch/Resources/Version.h"

//#include "UProjectInfo.h"

#if UE_ENABLE_ICU
#include <unicode/locid.h>
#endif

/** Holds an override path if a program has special needs */
std::tstring OverrideGameDir;

/* EBuildConfigurations interface
 *****************************************************************************/

namespace EBuildConfigurationsType
{
	EBuildConfigurationsType FromString( const TCHAR* Configuration )
	{
		if (_tcscmp(Configuration, TEXT("Debug")) == 0)
		{
			return EBuildConfigurationsType::Debug;
		}
		else if (_tcscmp(Configuration, TEXT("DebugGame")) == 0)
		{
			return EBuildConfigurationsType::DebugGame;
		}
		else if (_tcscmp(Configuration, TEXT("Development")) == 0)
		{
			return EBuildConfigurationsType::Development;
		}
		else if (_tcscmp(Configuration, TEXT("Shipping")) == 0)
		{
			return EBuildConfigurationsType::Shipping;
		}
		else if (_tcscmp(Configuration, TEXT("Test")) == 0)
		{
			return EBuildConfigurationsType::Test;
		}

		return EBuildConfigurationsType::Unknown;
	}


	const TCHAR* ToString(EBuildConfigurationsType Configuration)
	{
		switch (Configuration)
		{
			case EBuildConfigurationsType::Debug:
				return TEXT("Debug");

			case EBuildConfigurationsType::DebugGame:
				return TEXT("DebugGame");

			case EBuildConfigurationsType::Development:
				return TEXT("Development");

			case EBuildConfigurationsType::Shipping:
				return TEXT("Shipping");

			case EBuildConfigurationsType::Test:
				return TEXT("Test");

			default:
				return TEXT("Unknown");
		}
	}

// 	FText ToText( EBuildConfigurations::Type Configuration )
// 	{
// 		switch (Configuration)
// 		{
// 		case Debug:
// 			return NSLOCTEXT("UnrealBuildConfigurations", "DebugName", "Debug");
// 
// 		case DebugGame:
// 			return NSLOCTEXT("UnrealBuildConfigurations", "DebugGameName", "DebugGame");
// 
// 		case Development:
// 			return NSLOCTEXT("UnrealBuildConfigurations", "DevelopmentName", "Development");
// 
// 		case Shipping:
// 			return NSLOCTEXT("UnrealBuildConfigurations", "ShippingName", "Shipping");
// 
// 		case Test:
// 			return NSLOCTEXT("UnrealBuildConfigurations", "TestName", "Test");
// 
// 		default:
// 			return NSLOCTEXT("UnrealBuildConfigurations", "UnknownName", "Unknown");
// 		}
// 	}
}


/* EBuildConfigurations interface
 *****************************************************************************/

namespace EBuildTargetsType
{
	EBuildTargetsType FromString(const TCHAR* Target)
	{
		if (_tcscmp(Target, TEXT("Editor")) == 0)
		{
			return EBuildTargetsType::Editor;
		}
		else if (_tcscmp(Target, TEXT("Game")) == 0)
		{
			return EBuildTargetsType::Game;
		}
		else if (_tcscmp(Target, TEXT("Server")) == 0)
		{
			return EBuildTargetsType::Server;
		}

		return EBuildTargetsType::Unknown;
	}


	const TCHAR* ToString( EBuildTargetsType Target )
	{
		switch (Target)
		{
			case EBuildTargetsType::Editor:
				return TEXT("Editor");

			case EBuildTargetsType::Game:
				return TEXT("Game");

			case EBuildTargetsType::Server:
				return TEXT("Server");

			default:
				return TEXT("Unknown");
		}
	}
}


/* FGenericPlatformMisc interface
 *****************************************************************************/
#if !UE_BUILD_SHIPPING
	bool FGenericPlatformMisc::bShouldPromptForRemoteDebugging = false;
	bool FGenericPlatformMisc::bPromptForRemoteDebugOnEnsure = false;
#endif	//#if !UE_BUILD_SHIPPING

GenericApplication* FGenericPlatformMisc::CreateApplication()
{
	return new GenericApplication();
}

std::vector<uint8> FGenericPlatformMisc::GetMacAddress()
{
	return std::vector<uint8>();
}

std::tstring FGenericPlatformMisc::GetMacAddressString()
{
	std::vector<uint8> MacAddr = FPlatformMisc::GetMacAddress();
	std::tstring Result;
	for (std::vector<uint8>::iterator it = MacAddr.begin(); it != MacAddr.end(); ++it)
	{
		Result += _tprintf(TEXT("%02x"),*it);
	}
	return Result;
}

std::tstring FGenericPlatformMisc::GetHashedMacAddressString()
{
	return NULL; //TODO: FIX hash//FMD5::HashAnsiString(*FPlatformMisc::GetMacAddressString());
}

std::tstring FGenericPlatformMisc::GetUniqueDeviceId()
{
	return FPlatformMisc::GetHashedMacAddressString();
}

void FGenericPlatformMisc::SubmitErrorReport( const TCHAR* InErrorHist, EErrorReportModeType InMode )
{
	//TODO: Fix log system
	//UE_LOG(LogGenericPlatformMisc, Error, TEXT("This platform cannot submit a crash report. Report was:\n%s"), InErrorHist);
}

void FGenericPlatformMisc::MemoryBarrier()
{
}

void FGenericPlatformMisc::HandleIOFailure( const TCHAR* Filename )
{
	//TODO: Fix log system
	//UE_LOG(LogGenericPlatformMisc, Fatal,TEXT("I/O failure operating on '%s'"), Filename ? Filename : TEXT("Unknown file"));
}

bool FGenericPlatformMisc::GetRegistryString(const std::tstring& InRegistryKey, const std::tstring& InValueName, bool bPerUserSetting, std::tstring& OutValue)
{
	// By default, fail.
	return false;
}

void FGenericPlatformMisc::LowLevelOutputDebugString( const TCHAR *Message )
{
	FPlatformMisc::LocalPrint( Message );
}

void FGenericPlatformMisc::LowLevelOutputDebugStringf(const TCHAR *Fmt, ... )
{
	//Requires additional macros to function
// 	GROWABLE_LOGF(
// 		FPlatformMisc::LowLevelOutputDebugString( Buffer );
// 	);
}

void FGenericPlatformMisc::SetUTF8Output()
{
	// assume that UTF-8 is possible by default anyway
}

void FGenericPlatformMisc::LocalPrint( const TCHAR* Str )
{
#if PLATFORM_USE_LS_SPEC_FOR_WIDECHAR
	printf("%ls", Str);
#else
	printf("%s", Str);
#endif
}

void FGenericPlatformMisc::RequestExit( bool Force )
{
	//TODO: Fix log
	//UE_LOG(LogGenericPlatformMisc, Log,  TEXT("FPlatformMisc::RequestExit(%i)"), Force );
	if( Force )
	{
		// Force immediate exit.
		// Dangerous because config code isn't flushed, global destructors aren't called, etc.
		// Suppress abort message and MS reports.
		abort();
	}
	else
	{
		// Tell the platform specific code we want to exit cleanly from the main loop.
		GIsRequestingExit = 1;
	}
}

const TCHAR* FGenericPlatformMisc::GetSystemErrorMessage(TCHAR* OutBuffer, int32 BufferCount, int32 Error)
{
	const TCHAR* Message = TEXT("No system errors available on this platform.");
	//TODO: Fix check
	//check(OutBuffer && BufferCount > 80);
	Error = 0;
	_tcscpy_s(OutBuffer, BufferCount - 1, Message);
	return OutBuffer;
}

void FGenericPlatformMisc::ClipboardCopy(const TCHAR* Str)
{

}
void FGenericPlatformMisc:: ClipboardPaste(std::tstring& Dest)
{
	Dest = std::tstring();
}

void FGenericPlatformMisc::CreateGuid(FGuid& Guid)
{
	int32 Year=0, Month=0, DayOfWeek=0, Day=0, Hour=0, Min=0, Sec=0, MSec=0;

	//TODO: Fix time and guid
	//FPlatformTime::SystemTime(Year, Month, DayOfWeek, Day, Hour, Min, Sec, MSec);

	//TODO: FIX guid
	//Guid = FGuid(Day | (Hour << 16), Month | (Sec << 16), MSec | (Min << 16), Year ^ FPlatformTime::Cycles());
}

EAppReturnTypeType FGenericPlatformMisc::MessageBoxExt( EAppMsgTypeType MsgType, const TCHAR* Text, const TCHAR* Caption )
{
	//TODO: Do we need this warning.
// 	if (GWarn)
// 	{
// 		UE_LOG(LogGenericPlatformMisc, Warning, TEXT("Cannot display dialog box on this platform: %s : %s"), Caption, Text);
// 	}

	switch(MsgType)
	{
	case EAppMsgTypeType::Ok:
		return EAppReturnTypeType::Ok; // Ok
	case EAppMsgTypeType::YesNo:
		return EAppReturnTypeType::No; // No
	case EAppMsgTypeType::OkCancel:
		return EAppReturnTypeType::Cancel; // Cancel
	case EAppMsgTypeType::YesNoCancel:
		return EAppReturnTypeType::Cancel; // Cancel
	case EAppMsgTypeType::CancelRetryContinue:
		return EAppReturnTypeType::Cancel; // Cancel
	case EAppMsgTypeType::YesNoYesAllNoAll:
		return EAppReturnTypeType::No; // No
	case EAppMsgTypeType::YesNoYesAllNoAllCancel:
		return EAppReturnTypeType::Yes; // Yes
	default:
		//TODO: What does this check do?
		//check(0);
		return EAppReturnTypeType::Cancel;
	}
	return EAppReturnTypeType::Cancel; // Cancel
}

const TCHAR* FGenericPlatformMisc::RootDir()
{
	//TODO: do we need root dir

// 	static std::tstring Path;
// 	if (Path.length() == 0)
// 	{
// 		std::tstring TempPath = FPaths::EngineDir();
// 		int32 chopPos = TempPath.Find(TEXT("/Engine"));
// 		if (chopPos != INDEX_NONE)
// 		{
// 			TempPath = TempPath.Left(chopPos + 1);
// 			TempPath = FPaths::ConvertRelativePathToFull(TempPath);
// 			Path = TempPath;
// 		}
// 		else
// 		{
// 			Path = FPlatformProcess::BaseDir();
// 
// 			// if the path ends in a separator, remove it
// 			if( Path.Right(1)==TEXT("/") )
// 			{
// 				Path = Path.LeftChop( 1 );
// 			}
// 
// 			// keep going until we've removed Binaries
// #if IS_MONOLITHIC && !IS_PROGRAM
// 			int32 pos = Path.Find(*std::tstring::Printf(TEXT("/%s/Binaries"), GGameName));
// #else
// 			int32 pos = Path.Find(TEXT("/Engine/Binaries"), ESearchCase::IgnoreCase);
// #endif
// 			if ( pos != INDEX_NONE )
// 			{
// 				Path = Path.Left(pos + 1);
// 			}
// 			else
// 			{
// 				pos = Path.Find(TEXT("/../Binaries"), ESearchCase::IgnoreCase);
// 				if ( pos != INDEX_NONE )
// 				{
// 					Path = Path.Left(pos + 1) + TEXT("../../");
// 				}
// 				else
// 				{
// 					while( Path.Len() && Path.Right(1)!=TEXT("/") )
// 					{
// 						Path = Path.LeftChop( 1 );
// 					}
// 				}
// 
// 			}
// 		}
// 	}
// 	return *Path;
	//todo: fix root path
	return nullptr;
}

const TCHAR* FGenericPlatformMisc::EngineDir()
{
	static std::tstring EngineDirectory = TEXT("");
// 	if (EngineDirectory.length() == 0)
// 	{
// 		// See if we are a root-level project
// 		std::tstring DefaultEngineDir = TEXT("../../../Engine/");
// #if PLATFORM_DESKTOP
// 		//@todo. Need to have a define specific for this scenario??
// 		if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*(DefaultEngineDir / TEXT("Binaries"))))
// 		{
// 			EngineDirectory = DefaultEngineDir;
// 		}
// 		else if (GForeignEngineDir != NULL && FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*(std::tstring(GForeignEngineDir) / TEXT("Binaries"))))
// 		{
// 			EngineDirectory = GForeignEngineDir;
// 		}
// 
// 		if (EngineDirectory.Len() == 0)
// 		{
// 			// Temporary work-around for legacy dependency on ../../../ (re Lightmass)
// 			EngineDirectory = DefaultEngineDir;
// 			UE_LOG(LogGenericPlatformMisc, Warning, TEXT("Failed to determine engine directory: Defaulting to %s"), *EngineDirectory);
// 		}
// #else
// 		EngineDirectory = DefaultEngineDir;
// #endif
// 	}
	return EngineDirectory.c_str();
}

const TCHAR* FGenericPlatformMisc::GetNullRHIShaderFormat()
{
	return TEXT("PCD3D_SM5");
}

IPlatformChunkInstall* FGenericPlatformMisc::GetPlatformChunkInstall()
{
	//static FGenericPlatformChunkInstall Singleton;
	return nullptr;//TODO: figure out wtf this is// &Singleton;
}

//TODO: do we even need this
// FLinearColor FGenericPlatformMisc::GetScreenPixelColor(const struct FVector2D& InScreenPos, float InGamma)
// { 
// 	return FLinearColor::Black;
// }

void GenericPlatformMisc_GetProjectFilePathGameDir(std::tstring& OutGameDir)
{
	//TODO: Fix path
	// Here we derive the game path from the project file location.
// 	std::tstring BasePath = FPaths::GetPath(FPaths::GetProjectFilePath());
// 	FPaths::NormalizeFilename(BasePath);
// 	BasePath = FFileManagerGeneric::DefaultConvertToRelativePath(*BasePath);
// 	if(!BasePath.EndsWith("/")) BasePath += TEXT("/");
// 	OutGameDir = BasePath;
}

const TCHAR* FGenericPlatformMisc::GameDir()
{
// 	static std::tstring GameDir = TEXT("");
// 
// 	// track if last time we called this function the .ini was ready and had fixed the GGameName case
// 	static bool bWasIniReady = false;
// 	bool bIsIniReady = GConfig && GConfig->IsReadyForUse();
// 	if (bWasIniReady != bIsIniReady)
// 	{
// 		GameDir = TEXT("");
// 		bWasIniReady = bIsIniReady;
// 	}
// 
// 	// try using the override game dir if it exists, which will override all below logic
// 	if (GameDir.Len() == 0)
// 	{
// 		GameDir = OverrideGameDir;
// 	}
// 
// 	if (GameDir.Len() == 0)
// 	{
// 		if (FPlatformProperties::IsProgram())
// 		{
// 			// monolithic, game-agnostic executables, the ini is in Engine/Config/Platform
// 			GameDir = std::tstring::Printf(TEXT("../../../Engine/Programs/%s/"), GGameName);
// 		}
// 		else
// 		{
// 			if (FPaths::IsProjectFilePathSet())
// 			{
// 				GenericPlatformMisc_GetProjectFilePathGameDir(GameDir);
// 			}
// 			else if ( FApp::HasGameName() )
// 			{
// 				if (FPlatformProperties::IsMonolithicBuild() == false)
// 				{
// 					// No game project file, but has a game name, use the game folder next to the working directory
// 					GameDir = std::tstring::Printf(TEXT("../../../%s/"), GGameName);
// 					std::tstring GameBinariesDir = GameDir / TEXT("Binaries/");
// 					if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*GameBinariesDir) == false)
// 					{
// 						// The game binaries folder was *not* found
// 						// 
// 						FPlatformMisc::LowLevelOutputDebugStringf(TEXT("Failed to find game directory: %s\n"), *GameDir);
// 
// 						// Use the uprojectdirs
// 						std::tstring GameProjectFile = FUProjectDictionary::GetDefault().GetRelativeProjectPathForGame(GGameName, FPlatformProcess::BaseDir());
// 						if (GameProjectFile.IsEmpty() == false)
// 						{
// 							// We found a project folder for the game
// 							FPaths::SetProjectFilePath(GameProjectFile);
// 							GameDir = FPaths::GetPath(GameProjectFile);
// 							if (GameDir.EndsWith(TEXT("/")) == false)
// 							{
// 								GameDir += TEXT("/");
// 							}
// 						}
// 					}
// 				}
// 				else
// 				{
// #if !PLATFORM_DESKTOP
// 					GameDir = std::tstring::Printf(TEXT("../../../%s/"), GGameName);
// #else
// 					// This assumes the game executable is in <GAME>/Binaries/<PLATFORM>
// 					GameDir = TEXT("../../");
// 
// 					// Determine a relative path that includes the game folder itself, if possible...
// 					std::tstring LocalBaseDir = std::tstring(FPlatformProcess::BaseDir());
// 					std::tstring LocalRootDir = FPaths::RootDir();
// 					std::tstring BaseToRoot = LocalRootDir;
// 					FPaths::MakePathRelativeTo(BaseToRoot, *LocalBaseDir);
// 					std::tstring LocalGameDir = LocalBaseDir / TEXT("../../");
// 					FPaths::CollapseRelativeDirectories(LocalGameDir);
// 					FPaths::MakePathRelativeTo(LocalGameDir, *(FPaths::RootDir()));
// 					LocalGameDir = BaseToRoot / LocalGameDir;
// 					if (LocalGameDir.EndsWith(TEXT("/")) == false)
// 					{
// 						LocalGameDir += TEXT("/");
// 					}
// 
// 					std::tstring CheckLocal = FPaths::ConvertRelativePathToFull(LocalGameDir);
// 					std::tstring CheckGame = FPaths::ConvertRelativePathToFull(GameDir);
// 					if (CheckLocal == CheckGame)
// 					{
// 						GameDir = LocalGameDir;
// 					}
// 
// 					if (GameDir.EndsWith(TEXT("/")) == false)
// 					{
// 						GameDir += TEXT("/");
// 					}
// #endif
// 				}
// 			}
// 			else
// 			{
// 				// Get a writable engine directory
// 				GameDir = FPaths::EngineUserDir();
// 				FPaths::NormalizeFilename(GameDir);
// 				GameDir = FFileManagerGeneric::DefaultConvertToRelativePath(*GameDir);
// 				if(!GameDir.EndsWith(TEXT("/"))) GameDir += TEXT("/");
// 			}
// 		}
// 	}
// 
// 	return *GameDir;
//TODO: Fix game dir
	return NULL;
}

uint32 FGenericPlatformMisc::GetStandardPrintableKeyMap(uint16* KeyCodes, std::tstring* KeyNames, uint32 MaxMappings, bool bMapUppercaseKeys, bool bMapLowercaseKeys)
{
	uint32 NumMappings = 0;

#define ADDKEYMAP(KeyCode, KeyName)		if (NumMappings<MaxMappings) { KeyCodes[NumMappings]=KeyCode; KeyNames[NumMappings]=KeyName; ++NumMappings; };

	ADDKEYMAP( '0', TEXT("Zero") );
	ADDKEYMAP( '1', TEXT("One") );
	ADDKEYMAP( '2', TEXT("Two") );
	ADDKEYMAP( '3', TEXT("Three") );
	ADDKEYMAP( '4', TEXT("Four") );
	ADDKEYMAP( '5', TEXT("Five") );
	ADDKEYMAP( '6', TEXT("Six") );
	ADDKEYMAP( '7', TEXT("Seven") );
	ADDKEYMAP( '8', TEXT("Eight") );
	ADDKEYMAP( '9', TEXT("Nine") );

	// we map both upper and lower
	if (bMapUppercaseKeys)
	{
		ADDKEYMAP( 'A', TEXT("A") );
		ADDKEYMAP( 'B', TEXT("B") );
		ADDKEYMAP( 'C', TEXT("C") );
		ADDKEYMAP( 'D', TEXT("D") );
		ADDKEYMAP( 'E', TEXT("E") );
		ADDKEYMAP( 'F', TEXT("F") );
		ADDKEYMAP( 'G', TEXT("G") );
		ADDKEYMAP( 'H', TEXT("H") );
		ADDKEYMAP( 'I', TEXT("I") );
		ADDKEYMAP( 'J', TEXT("J") );
		ADDKEYMAP( 'K', TEXT("K") );
		ADDKEYMAP( 'L', TEXT("L") );
		ADDKEYMAP( 'M', TEXT("M") );
		ADDKEYMAP( 'N', TEXT("N") );
		ADDKEYMAP( 'O', TEXT("O") );
		ADDKEYMAP( 'P', TEXT("P") );
		ADDKEYMAP( 'Q', TEXT("Q") );
		ADDKEYMAP( 'R', TEXT("R") );
		ADDKEYMAP( 'S', TEXT("S") );
		ADDKEYMAP( 'T', TEXT("T") );
		ADDKEYMAP( 'U', TEXT("U") );
		ADDKEYMAP( 'V', TEXT("V") );
		ADDKEYMAP( 'W', TEXT("W") );
		ADDKEYMAP( 'X', TEXT("X") );
		ADDKEYMAP( 'Y', TEXT("Y") );
		ADDKEYMAP( 'Z', TEXT("Z") );
	}

	if (bMapLowercaseKeys)
	{
		ADDKEYMAP( 'a', TEXT("A") );
		ADDKEYMAP( 'b', TEXT("B") );
		ADDKEYMAP( 'c', TEXT("C") );
		ADDKEYMAP( 'd', TEXT("D") );
		ADDKEYMAP( 'e', TEXT("E") );
		ADDKEYMAP( 'f', TEXT("F") );
		ADDKEYMAP( 'g', TEXT("G") );
		ADDKEYMAP( 'h', TEXT("H") );
		ADDKEYMAP( 'i', TEXT("I") );
		ADDKEYMAP( 'j', TEXT("J") );
		ADDKEYMAP( 'k', TEXT("K") );
		ADDKEYMAP( 'l', TEXT("L") );
		ADDKEYMAP( 'm', TEXT("M") );
		ADDKEYMAP( 'n', TEXT("N") );
		ADDKEYMAP( 'o', TEXT("O") );
		ADDKEYMAP( 'p', TEXT("P") );
		ADDKEYMAP( 'q', TEXT("Q") );
		ADDKEYMAP( 'r', TEXT("R") );
		ADDKEYMAP( 's', TEXT("S") );
		ADDKEYMAP( 't', TEXT("T") );
		ADDKEYMAP( 'u', TEXT("U") );
		ADDKEYMAP( 'v', TEXT("V") );
		ADDKEYMAP( 'w', TEXT("W") );
		ADDKEYMAP( 'x', TEXT("X") );
		ADDKEYMAP( 'y', TEXT("Y") );
		ADDKEYMAP( 'z', TEXT("Z") );
	}

	ADDKEYMAP( ';', TEXT("Semicolon") );
	ADDKEYMAP( '=', TEXT("Equals") );
	ADDKEYMAP( ',', TEXT("Comma") );
	ADDKEYMAP( '-', TEXT("Underscore") );
	ADDKEYMAP( '.', TEXT("Period") );
	ADDKEYMAP( '/', TEXT("Slash") );
	ADDKEYMAP( '`', TEXT("Tilde") );
	ADDKEYMAP( '[', TEXT("LeftBracket") );
	ADDKEYMAP( '\\', TEXT("Backslash") );
	ADDKEYMAP( ']', TEXT("RightBracket") );
	ADDKEYMAP( '\'', TEXT("Quote") );
	ADDKEYMAP( ' ', TEXT("SpaceBar") );

	return NumMappings;
}

const TCHAR* FGenericPlatformMisc::GetUBTPlatform()
{
	//todo: wtf is this UBT platform thing
	return nullptr; //TEXT( PREPROCESSOR_TO_STRING(UBT_COMPILED_PLATFORM) );
}

const TCHAR* FGenericPlatformMisc::GetDefaultDeviceProfileName()
{
	return TEXT("Default");
}

void FGenericPlatformMisc::SetOverrideGameDir(const std::tstring& InOverrideDir)
{
	OverrideGameDir = InOverrideDir;
}

int32 FGenericPlatformMisc::NumberOfCoresIncludingHyperthreads()
{
	return FPlatformMisc::NumberOfCores();
}

int32 FGenericPlatformMisc::NumberOfWorkerThreadsToSpawn()
{
	static int32 MaxGameThreads = 4;
	static int32 MaxThreads = 16;

	int32 NumberOfCores = FPlatformMisc::NumberOfCores();
	//int32 MaxWorkerThreadsWanted = (IsRunningGame() || IsRunningDedicatedServer() || IsRunningClientOnly()) ? MaxGameThreads : MaxThreads;
	// TODO: we don't have threads yet
	// need to spawn at least one worker thread (see FTaskGraphImplementation)
	return 0;//FMath::Max(FMath::Min(NumberOfCores - 1, MaxWorkerThreadsWanted), 1);
}

void FGenericPlatformMisc::GetValidTargetPlatforms(std::vector<std::tstring>& TargetPlatformNames)
{
	//TODO: Fix this target platforms thingy
	// by default, just return the running PlatformName as the only TargetPlatform we support
	TargetPlatformNames.push_back(TEXT("Fix this hack")/*FPlatformProperties::PlatformName()*/);
}

const TCHAR* FGenericPlatformMisc::GetDefaultPathSeparator()
{
	return TEXT( "/" );
}

std::tstring FGenericPlatformMisc::GetDefaultLocale()
{
#if UE_ENABLE_ICU
	icu::Locale ICUDefaultLocale = icu::Locale::getDefault();
	return std::tstring(ICUDefaultLocale.getName());
#else
	return TEXT("en");
#endif
}

std::tstring FGenericPlatformMisc::GetFileManagerName()
{
	//todo: fix this 
	return TEXT("YOLO, FIX IT");//TEXT("GenericPlatform", "FileManagerName", "File Manager");
}
