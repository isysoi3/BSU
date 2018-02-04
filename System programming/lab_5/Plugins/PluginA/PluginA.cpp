#include "stdafx.h"
#include "PluginA.h"
#include <iostream>

BOOLEAN __stdcall GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD * pdwBytesWritten)
{
	LPSTR author = "Ilya Sysoi";
	DWORD authorSize = strlen(author);
	if (dwBufferSize < authorSize)
	{
		*pdwBytesWritten = 0;
		return FALSE;
	}
	strcpy_s(buffer, dwBufferSize, author);
	*pdwBytesWritten = authorSize;
	return TRUE;

}


BOOLEAN __stdcall GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten)
{
	LPSTR description = "Ýòîò ïëàãèí ïå÷àòåò ñàìîëåò)))";
	DWORD descriptionSize = strlen(description);
	if (dwBufferSize < descriptionSize)
	{
		*pdwBytesWritten = 0;
		return FALSE;
	}
	strcpy_s(buffer, dwBufferSize, description);
	*pdwBytesWritten = descriptionSize;
	return TRUE;

}

VOID __stdcall Execute()
{
	printf("__________________¶¶¶____________________________\n");
	printf("___________________¶¶¶___________________________\n");
	printf("__¶¶¶_______________¶¶¶¶_________________________\n");
	printf("__¶¶¶¶_______________¶__¶________________________\n");
	printf("__¶__¶¶¶_____________¶¶__¶¶______________________\n");
	printf("__¶¶¶¶¶¶¶_____________¶¶___¶_____________________\n");
	printf("__¶¶¶¶¶¶¶______________¶___¶¶____________________\n");
	printf("__¶______¶_____________¶¶____¶___________________\n");
	printf("_¶¶_____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶___\n");
	printf("_¶¶¶¶¶¶¶¶¶0¶0¶00¶0¶0¶¶0¶0¶00¶0¶0¶¶0¶0¶0¶¶00¶¶¶¶¶_\n");
	printf("¶¶¶______________________¶¶_____¶_____________¶¶¶\n");
	printf("___¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_\n");
	printf("_______________________¶_____¶___________________\n");
	printf("______________________¶____¶¶____________________\n");
	printf("_____________________¶_____¶_____________________\n");
	printf("_____________________¶___¶¶______________________\n");
	printf("____________________¶___¶________________________\n");
	printf("___________________¶¶_¶¶_________________________\n");
	printf("__________________¶¶_¶___________________________\n");
	printf("_________________¶¶_¶¶___________________________\n");
	printf("________________¶¶¶¶_____________________________\n");

}