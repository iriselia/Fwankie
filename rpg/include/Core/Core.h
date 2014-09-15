#pragma once
/* C++ Standard Library Includes */
#include <string>
#include <vector>
#include <map>
#include <memory>

#ifdef _UNICODE
namespace std{ typedef wstring tstring; }

#define _tsprintf swprintf
#define wcstotcs(dest, src, count) wcsncpy(dest, src, count)
#define mbstotcs mbstowcs
#else /* _UNICODE */
namespace std{ typedef string tstring; }

#define _tsprintf sprintf
#define wcstotcs wcstombs
#define mbstotcs(dest, src, count) strncpy(dest, src, count)
#endif


/* Multi-Platform Support Includes */
#include "Platform.h" // Bit abstraction
#include "PlatformIncludes.h"
#include "PlatformMath.h"

extern bool GIsRequestingExit;

//#include "GenericWindowDefinition.h"
//#include "GenericWindow.h"

enum { INDEX_NONE = -1 };

//#include "InputCoreTypes.h"

