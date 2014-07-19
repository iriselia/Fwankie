#pragma once
#include "GenericPlatform.h"

/**
* Windows specific types
**/
struct WindowsPlatformTypes : public GenericPlatformTypes
{
#ifdef _WIN64
	typedef std::int64_t		SIZE_T;
#else
	typedef std::int32_t		SIZE_T;
#endif
};

typedef WindowsPlatformTypes PlatformTypes;

// Function type macros.
#define VARARGS     __cdecl					/* Functions with variable arguments */
#ifdef CDECL
#undef CDECL
#define CDECL	    __cdecl					/* Standard C function */
#endif
#define STDCALL		__stdcall				/* Standard calling convention */
#define FORCEINLINE __forceinline			/* Force code to be inline */
#define FORCENOINLINE __declspec(noinline)	/* Force code to NOT be inline */

// DLL export and import definitions
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
