#pragma once

#ifdef RUNNING_PLATFORM_WINDOWS
#else
	#error Running only supports Windows!
#endif

#ifdef RUNNING_ENABLE_ASSERTS
	#define RUNNING_ASSERT(x, ...) { if (!(x)) { RUNNING_CLIENT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RUNNING_CORE_ASSERT(x, ...) { if (!(x)) { RUNNING_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RUNNING_ASSERT(x, ...)
	#define RUNNING_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)