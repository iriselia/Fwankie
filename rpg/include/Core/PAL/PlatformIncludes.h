// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*================================================================================
	PlatformIncludes.h: Setup the main includes for the platform
==================================================================================*/
#pragma once

#include <new>
#include <wchar.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>
#include <string.h>

// Platform specific compiler pre-setup, must be included before everything else
#if PLATFORM_WINDOWS
//#include "Windows/WindowsPlatformCompilerPreSetup.h"
#endif

// Generic versions of the platform abstractions
// #include "GenericPlatform/GenericPlatformCompilerSetup.h"
// #include "GenericPlatform/GenericPlatformMemory.h"
// #include "GenericPlatform/GenericPlatformString.h"

//THIS IS REQUIRED!!
//#include "GenericPlatformMisc.h"



//#include "GenericPlatform/GenericPlatformStackWalk.h"
#include "GenericPlatformMath.h"
// #include "GenericPlatform/GenericPlatformNamedPipe.h"
// #include "GenericPlatform/GenericPlatformTime.h"
// #include "GenericPlatform/GenericPlatformProcess.h"
// #include "GenericPlatform/GenericPlatformOutputDevices.h"
// #include "GenericPlatform/GenericPlatformAtomics.h"
// #include "GenericPlatform/GenericPlatformTLS.h"
// #include "GenericPlatform/GenericPlatformSplash.h"
// #include "GenericPlatform/GenericPlatformFile.h"
// #include "GenericPlatform/GenericPlatformSurvey.h"
// #include "GenericPlatform/GenericPlatformHttp.h"

// Platform specific include.
//@port This is where you include your "main" platform header
#if PLATFORM_WINDOWS
	#include "WindowsPlatformIncludes.h"
#elif PLATFORM_PS4
	#include "PS4/PS4Includes.h"
#elif PLATFORM_XBOXONE
	#include "XboxOne/XboxOnePlatformIncludes.h"
#elif PLATFORM_MAC
	#include "Mac/MacPlatformIncludes.h"
#elif PLATFORM_IOS
	#include "IOS/IOSPlatformIncludes.h"
#elif PLATFORM_ANDROID
	#include "Android/AndroidIncludes.h"
#elif PLATFORM_WINRT
	#include "WinRT/WinRTPlatformIncludes.h"
#elif PLATFORM_HTML5
	#include "HTML5/HTML5PlatformIncludes.h"
#elif PLATFORM_LINUX
	#include "Linux/LinuxPlatformIncludes.h"
#endif

//TEXT macro, may or may not have come from OS includes
#if !defined(TEXT) && !UE_BUILD_DOCS
		#define TEXT(s) L##s
#endif

