#include "stdafx.h"
#include "PluginWithImplicitLinking.h"

namespace ErrorHandling
{
	BOOLEAN __stdcall error(char* message)
	{
		printf(message);
		system("pause");
		return false;
	}
}