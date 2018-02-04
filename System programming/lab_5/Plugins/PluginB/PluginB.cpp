#include "stdafx.h"
#include "PluginB.h"
#include <ctime>
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
	LPSTR description = "Выводит на экран текущую дату";
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
	char date[9];
	_strdate_s(date);
	printf("Текущая дата: %s", date);
}