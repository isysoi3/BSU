#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "PluginWithImplicitLinking.h"

using namespace std;

typedef BOOLEAN(__stdcall* DLLFUNC)(LPSTR, DWORD, DWORD*);
typedef VOID(__stdcall* DLLFUNCEXE)();

bool loadPlugin(HINSTANCE& hDLL, PCTSTR pluginPath);
bool freePlugin(HINSTANCE& hDLL);
bool showInformation(HINSTANCE hDLL);
bool executePlugin(HINSTANCE hDLL);
bool PluginsMenu(HINSTANCE& hDLL1, HINSTANCE& hDLL2, PCTSTR pluginAPath, PCTSTR pluginBPath, int option);

int MainMenu()
{
	int choose;
	cout << "[1] - Загрузить плагины\n";
	cout << "[2] - Выгрузить плагины\n";
	cout << "[3] - Показать на экране список плагинов\n";
	cout << "[4] - Показать информацию о каждом плагине\n";
	cout << "[5] - Выполнить действие\n";
	cout << "[0] - Выход\n";
	while ((choose = _getch()) != '1' && choose != '2'
		&& choose != '3' && choose != '4' && choose != '5' && choose != '0');
	system("cls");
	return choose;
}

int main()
{

	setlocale(LC_ALL, "Russian");

	PCTSTR plugin1Path = (".\\Plugins\\Release\\PluginA.dll");
	PCTSTR plugin2Path = (".\\Plugins\\Release\\PluginB.dll");
	HINSTANCE hDLL1 = NULL;
	HINSTANCE hDLL2 = NULL;

	bool exit = false;
	int n;
	while (!exit)
	{

		n = MainMenu();

		switch (n)
		{
		case'0':
			exit = true;
			break;
		case '1':
			if (!PluginsMenu(hDLL1, hDLL2, plugin1Path, plugin2Path, n))
				return EXIT_FAILURE;
			break;
		case '2':
			if (!PluginsMenu(hDLL1, hDLL2, plugin1Path, plugin2Path, n))
				return EXIT_FAILURE;
			break;
		case '3':
			if (hDLL1 != NULL)
			{
				printf("Plugin1\n");
			}
			if (hDLL2 != NULL)
			{
				printf("Plugin2\n");
			}
			_getch();
			break;
		case '4':
			if (hDLL1 != NULL)
			{
				cout << "Plugin1:\n";
				if (!showInformation(hDLL1))
					return EXIT_FAILURE;
			}
			if (hDLL2 != NULL)
			{
				cout << "\nPlugin2:\n";
				if (!showInformation(hDLL2))
					return EXIT_FAILURE;
			}
			_getch();
			break;
		case '5':
			if (!PluginsMenu(hDLL1, hDLL2, plugin1Path, plugin2Path, n))
				return EXIT_FAILURE;
			break;
		default:
			break;
		}
		system("cls");
	}
	FreeLibrary(hDLL1);
	FreeLibrary(hDLL2);
	return 0;
}


bool loadPlugin(HINSTANCE &hDLL, PCTSTR pluginPath)
{
	if (hDLL == NULL)
	{
		hDLL = LoadLibrary(pluginPath);
		if (hDLL == NULL)
			return ErrorHandling::error("could not load the dynamic library\n");
		cout << "Плагин загружен\n";
		_getch();
	}
	else
	{
		cout << "Плагин уже был загружен\n";
		_getch();
	}
	return true;
}

bool freePlugin(HINSTANCE& hDLL)
{
	if (hDLL != NULL)
	{
		if (!FreeLibrary(hDLL))
			return ErrorHandling::error("FreeLibrary failed\n");
		hDLL = NULL;
		cout << "Плагин выгружен\n";
		_getch();
	}
	else
	{
		cout << "Плагин уже был выгружен\n";
		_getch();
	}
	return true;
}

bool showInformation(HINSTANCE hDLL)
{
	DLLFUNC GetAuthor = (DLLFUNC)GetProcAddress(hDLL, "GetAuthor");
	if (GetAuthor == NULL)
		return ErrorHandling::error("could not locate the function");

	DLLFUNC GetDescription = (DLLFUNC)GetProcAddress(hDLL, "GetDescription");
	if (GetDescription == NULL)
		return ErrorHandling::error("could not locate the function");

	char author[255], description[255];
	DWORD written;
	if (!GetAuthor(author, 255, &written))
		return ErrorHandling::error("GetAuthor failed");

	if (!GetDescription(description, 255, &written))
		return ErrorHandling::error("GetDescription failed");
	cout << "Author: " << author << endl;
	cout << "Description: " << description << endl;
	return true;
}

bool executePlugin(HINSTANCE hDLL)
{
	DLLFUNCEXE Execute = (DLLFUNCEXE)GetProcAddress(hDLL, "Execute");
	if (Execute == NULL)
		return ErrorHandling::error("could not locate the function");
	Execute();
	return true;
}

int PluginsMenu(LPCSTR str)
{
	int choose;
	cout << str;
	cout << "[1] - Plugin1\n";
	cout << "[2] - Plugin2\n";
	cout << "[0] - Назад\n";

	while ((choose = _getch()) != '1' && choose != '2' && choose != '0');
	system("cls");
	return choose;
}

bool PluginsMenu(HINSTANCE& hDLLA, HINSTANCE& hDLLB, PCTSTR pluginAPath, PCTSTR pluginBPath, int option)
{
	bool exit = false;
	switch (option) {
	case '1':
		while (!exit)
		{
			auto dec = PluginsMenu("Загрузить плагин : \n");
			switch (dec)
			{
			case '0':
				exit = true;
				break;
			case '1':
				if (!loadPlugin(hDLLA, pluginAPath))
					return false;
				break;
			case '2':
				if (!loadPlugin(hDLLB, pluginBPath))
					return false;
				break;
			default:
				break;
			}
			system("cls");
		}
		break;
	case '2':
		while (!exit)
		{
			auto dec = PluginsMenu("Выгрузить плагин:\n");
			switch (dec)
			{
			case '0':
				exit = true;
				break;
			case '1':
				if (!freePlugin(hDLLA))
					return false;
				break;
			case '2':
				if (!freePlugin(hDLLB))
					return false;
				break;
			default:
				break;
			}
			system("cls");
		}
		break;
	case '5':
		while (!exit)
		{
			auto dec = PluginsMenu("Выпонить плагин:\n");
			switch (dec)
			{
			case '0':
				exit = true;
				break;
			case '1':
				if (hDLLA != NULL) {
					if (!executePlugin(hDLLA))
						return false;
				}
				else
					printf("Плагин не загружен!!!");
				_getch();
				break;
			case '2':
				if (hDLLB != NULL) {
					if (!executePlugin(hDLLB))
						return false;
				}
				else
					printf("Плагин не загружен!!!");
				_getch();
				break;
			default:
				break;
			}
			system("cls");
		}
		break;
	}
	return true;
}