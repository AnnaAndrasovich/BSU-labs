#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include "Header.h"
using namespace std;

int main()
{

	srand(time(0));

	int i, N = 10;
	char numstr[100] = "";
	char strok[1000] = "";
	char str[100] ="";
	char* st;
		
	_itoa_s(6 * N, numstr, 10);
	cout << numstr << "\n";

	long* arr = new long[N];
	for (i = 0; i < N; i++)
	{
		arr[i] = rand() % 50;
		//cout << arr[i] << ' ';
		_itoa_s(arr[i], str, 10);
		strcat(strok, str);
		strcat(strok, " ");
	}
	cout <<strok << endl;

	//char lpszAppName[] = "ConsoleProject.exe 3 1 2 3";
	char lpszAppName[] = "D:\\2 курс\\3 семестр\\OS\\lab2\\os2lab\\x64\\Debug\\ConsoleProject.exe ";
	strcat(lpszAppName, numstr);
	strcat(lpszAppName, " ");
	strcat(lpszAppName, strok);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwX = 200;
	si.dwY = 400;
	//si.lpTitle = "r";
	si.dwXSize = 300;
	si.dwYSize = 600;
	
	// создаем новый консольный процесс
	cout <<strok << endl;
	if (!CreateProcess(NULL, (LPSTR)lpszAppName, NULL, NULL, FALSE,
	//if (!CreateProcess((LPSTR)lpszAppName, NULL, NULL, NULL, FALSE,
	//if (!CreateProcess((LPSTR)lpszAppName, (LPSTR)strok, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		char t;
		cout << "The new process is not created.\n";
		cout << "Check a name of the process.\n";
		cout << "Press any key to finish.\n";
		cin >> t;
		return 0;
	}
	cout << "The new process is created.\n";
	
	HANDLE hThread;
	DWORD dwThread;
	/*hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)child, arr, 0, &dwThread);
	if (hThread == NULL)
		return GetLastError();*/
	// ждем завершения потока worker и counter
	/*if (WaitForSingleObject(hThread, INFINITE) != WAIT_OBJECT_0)
	{
		cout << "Wait for single object failed." << endl;
		cout << "Press any key to exit." << endl;
	}*/

	/*while (true)
	{
		char c;
		cout << "Input 't' to terminate the new console process: ";
		cin >> c;
		if (c == 't')
		{
			cout << "t\n";
			 завершаем новый процесс
			TerminateProcess(pi.hProcess, 1);
			break;
		}
	}*/

	// закрываем дескриптор потока worker и counter
	//CloseHandle(hThread);

	// закрываем дескрипторы этого процесса
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);


	return 0;
}