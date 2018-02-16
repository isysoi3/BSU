#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#ifdef PLUGINA_EXPORTS
#define PLUGINA_API __declspec(dllexport)
#else
#define PLUGINA_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	PLUGINA_API BOOLEAN __stdcall GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);

	PLUGINA_API BOOLEAN __stdcall GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);

	PLUGINA_API VOID __stdcall Execute();

#ifdef __cplusplus
};
#endif
