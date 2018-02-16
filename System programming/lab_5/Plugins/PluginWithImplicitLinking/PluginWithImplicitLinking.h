#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#ifdef PLUGINWITHIMPLICITLINKING_EXPORTS
#define PLUGINWITHIMPLICITLINKING_API __declspec(dllexport)
#else
#define PLUGINWITHIMPLICITLINKING_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	namespace ErrorHandling
	{
		PLUGINWITHIMPLICITLINKING_API BOOLEAN __stdcall error(char* message);
	}
#ifdef __cplusplus
};
#endif
