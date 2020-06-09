#pragma once

#ifdef SSM_PLATFORM_WINDOWS
	#ifdef SSM_BUILD_DLL
		#define SESAME_API __declspec(dllexport)
	#else
		#define SESAME_API __declspec(dllimport)
	#endif
#else
	#error This engine only is supported by Windows
#endif