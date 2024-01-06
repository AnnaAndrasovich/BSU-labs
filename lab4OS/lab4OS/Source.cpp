//// Синхронизация потоков, выполняющихся в
//// разных процессах, с использованинм мьютекса
//
//#include <windows.h>
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//	HANDLE	hMutex;
//	int		i, j;
//
//	// открываем мьютекс
//	hMutex = OpenMutex(SYNCHRONIZE, FALSE,/* L"D:\\2 курс:\\3 семестр:\\OS:
//		\\lab4OS:\\Consol:\\Console");*/"DemoMutex");
//	if (hMutex == NULL){
//		cout << "Open mutex failed." << endl;
//		cout << "Press any key to exit." << endl;
//		cin.get();
//
//		return GetLastError();
//	}
//
//	for (j = 10; j < 20; j++)
//	{
//		// захватываем мьютекс
//		WaitForSingleObject(hMutex, INFINITE);
//		for (i = 0; i < 10; i++){
//			cout << j << ' ';
//			cout.flush();
//			Sleep(5);
//		}
//		cout << endl;
//		// освобождаем мьютекс
//		ReleaseMutex(hMutex);
//	}
//	// закрываем дескриптор объекта
//	CloseHandle(hMutex);
//
//	return 0;
//}

// Пример синхронизации потоков с использованием семафора
//
//#include <windows.h>
//#include <iostream>
//
//using namespace std;
//
//volatile int a[10];
//HANDLE hSemaphore;
//
//DWORD WINAPI thread(LPVOID)
//{
//	int i;
//
//	for (i = 0; i < 10; i++)
//	{
//		a[i] = i + 1;
//		// отмечаем, что один элемент готов
//		ReleaseSemaphore(hSemaphore, 1, NULL);
//		Sleep(500);
//	}
//
//	return 0;
//}
//
//int main()
//{
//	int i;
//	HANDLE	hThread;
//	DWORD	IDThread;
//
//	cout << "An initial state of the array: ";
//	for (i = 0; i < 10; i++)
//		cout << a[i] << ' ';
//	cout << endl;
//	// создаем семафор		
//	hSemaphore = CreateSemaphore(NULL, 0, 10, NULL);
//	if (hSemaphore == NULL)
//		return GetLastError();
//
//	// создаем поток, который готовит элементы массива
//	hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);
//	if (hThread == NULL)
//		return GetLastError();
//
//	// поток main выводит элементы массива 
//	// только после их подготовки потоком thread
//	cout << "A final state of the array: ";
//	for (i = 0; i < 10; i++)
//	{
//		WaitForSingleObject(hSemaphore, INFINITE);
//		cout << a[i] << ' ' << flush;
//	}
//	cout << endl;
//
//	CloseHandle(hSemaphore);
//	CloseHandle(hThread);
//
//	return 0;
//}


#include <process.h>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

//Процессы и потоки 231
std::vector<std::string> v;
CRITICAL_SECTION fs;
unsigned __stdcall Thread(void* param)
{
	std::ifstream in;
	std::string st;
	EnterCriticalSection(&fs);
	in.open(("readme.txt"));
	while (getline(in, st)) v.push_back(st);
	in.close();
	LeaveCriticalSection(&fs);
	InvalidateRect((HWND)param, NULL, TRUE);
	return 0;
}
///////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	std::vector<std::string>::iterator it;
	int y;
	static HANDLE hThread;
	switch (message)
	{
	case WM_CREATE:
		InitializeCriticalSection(&fs);
		hThread = (HANDLE)_beginthreadex(NULL, 0, Thread, hWnd, 0, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		/*{
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}*/
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EnterCriticalSection(&fs);
		for (y = 0, it = v.begin(); it < v.end(); ++it, y += 16)
			TabbedTextOutA(hdc, 0, y, it->data(), it->length(), 0, NULL, 0);
		LeaveCriticalSection(&fs);
		EndPaint(hWnd, &ps);
			break;
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}