#pragma once

#ifdef RUNNING_PLATFORM_WINDOWS
	#ifdef RUNNING_BUILD_DLL
		#define RUNNING_API __declspec(dllexport)
	#else
		#define RUNNING_API __declspec(dllimport)	
	#endif
#else
	#error Running only supports Windows!
#endif

#define BIT(x) (1 << x)