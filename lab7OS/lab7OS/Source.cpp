//5.1.Написать программы двух консольных процессов Server и Figure, которые обмениваются сообщениями по анонимному каналу.Создать ненаследуемые дескрипторы канала и создать наследуемые дубликаты дескрипторов канала.
//
//Одновременно сообщение может передаваться только одним из процессов.
//
//Процесс - Server, который выполняет следующие действия :
//-Размер массива вводится с консоли.Тип массива : char
//Запускает процесс Figure.
//Передает процессу - Figure по анонимному каналу размер массива символов.
//Получает от процесса - Figure по анонимному каналу массив символов.Выводит полученную и переданную информацию на консоль.
//Выводит переданную и полученную информацию по каналу на консоль.
//
//Процесс - Figure, который выполняет следующие действия.
//Получает размер массива  символов по анонимному каналу от процесса - сервера.
//Генерирует элементы массива
//Определяет цифры и передает  их по анонимному каналу процессу - серверу.
//Выводит переданную и полученную информацию по каналу на консоль.
//Элементы массива предаются  по одному.

#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;
int main()
{
	HANDLE hWriteChannelReady = CreateEvent(NULL, FALSE, FALSE, L"WRITE_EVENT");
	HANDLE hReadChannelReady = CreateEvent(NULL, FALSE, FALSE, L"READ_EVENT");

	srand(time(NULL));
	int n;
	cout << "Enter array size: ";
	cin >> n;

	HANDLE hWritePipe, hReadPipe;
	HANDLE hWritePipe2, hReadPipe2;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)){
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}

	if (!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0)){
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}

	char lpszAppName[] = "D:\\2 курс\\3 семестр\\OS\\lab7OS\\x64\\Debug\\figure.exe";
	char lpszParameter[100];
	sprintf_s(lpszParameter, "%d %d", (int)hReadPipe, (int)hWritePipe2);
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	if (!CreateProcessA((LPCSTR)lpszAppName, lpszParameter, nullptr, nullptr, TRUE,CREATE_NEW_CONSOLE, nullptr, nullptr, (LPSTARTUPINFOA)&si, &piApp)){
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	int dwBytesWritten = 0;
	if (!WriteFile(hWritePipe, (int*)&n, sizeof(int), (LPDWORD)&dwBytesWritten, NULL)){
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	SetEvent(hWriteChannelReady);
	WaitForSingleObject(hReadChannelReady, INFINITE);
	char* res = new char[n];
	int num;
	if (!ReadFile(hReadPipe2, &(num), sizeof(int), (LPDWORD)&dwBytesWritten, NULL)){
		_cputs("Read from file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	cout << "Positive numbers " << num << "\n";
	SetEvent(hWriteChannelReady);
	for (int i = 0; i < n; i++){
		WaitForSingleObject(hReadChannelReady, INFINITE);
		if (!ReadFile(hReadPipe2, &(res[i]), sizeof(res[i]), (LPDWORD)&dwBytesWritten, NULL))
		{
			_cputs("Read from file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		SetEvent(hWriteChannelReady);
	}
	cout << "Array  : ";
	for (int i = 0; i < n; i++)
		cout << static_cast<int>(res[i]) << " ";

	CloseHandle(hWriteChannelReady);
	CloseHandle(hReadChannelReady);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe2);
	CloseHandle(hReadPipe2);
	return 0;
}