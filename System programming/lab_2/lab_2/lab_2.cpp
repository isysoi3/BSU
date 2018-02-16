// lab_2.cpp: определяет точку входа для консольного приложения.
//

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

BOOL GetProcessList();
BOOL ListProcessModules(DWORD dwPID);
BOOL ListProcessThreads(DWORD dwOwnerPID);

int main(void)
{
	GetProcessList();
	return 0;
}

BOOL GetProcessList()
{
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32; //струкура которая описывет процесс
	DWORD dwPriorityClass; 

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //снимок всех запущенных процессов
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 0;
	
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);    
		return 0;
	}
	

	do 
	{
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
		if (hProcess != NULL){
			dwPriorityClass = GetPriorityClass(hProcess);
			CloseHandle(hProcess);
		}
		_tprintf(TEXT("====================================================="));
		_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
		_tprintf(TEXT("\n-------------------------------------------------------"));
		_tprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
		_tprintf(TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
		_tprintf(TEXT("\n  Priority     = %d"), pe32.pcPriClassBase);
		_tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
	
		ListProcessThreads(pe32.th32ProcessID);
		ListProcessModules(pe32.th32ProcessID);

		system("pause");
		system("cls");
	} while(Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return 1;
}

BOOL ListProcessModules(DWORD dwPID)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	int countModules = 0;

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID); // снимок модулей процесса 
	if (hModuleSnap == INVALID_HANDLE_VALUE) {
		_tprintf(TEXT("\n     Total number of modules for process     = %d \n"), countModules);
		return 0;
	}

	me32.dwSize = sizeof(MODULEENTRY32);

	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);
		return 0;
	}

	do
	{
		//if (me32.th32ProcessID == dwPID)
		//{
			_tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
			_tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);
			_tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
			countModules++;
		//}
	} while (Module32Next(hModuleSnap, &me32));

	_tprintf(TEXT("\n     Total number of modules for process     = %d \n"), countModules);
	CloseHandle(hModuleSnap);
	return 1;
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;


	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); // снимок потоков процесса 
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return 0;

	te32.dwSize = sizeof(THREADENTRY32);

	if (!Thread32First(hThreadSnap, &te32))
	{
		CloseHandle(hThreadSnap); 
		return 0;
	}

	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			_tprintf(TEXT("\n\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
			_tprintf(TEXT("\n     Base priority  = %d"), te32.tpBasePri);
			_tprintf(TEXT("\n"));
		}
	} while (Thread32Next(hThreadSnap, &te32));

	CloseHandle(hThreadSnap);
	return 1;
}
