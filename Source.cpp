//������� ������������� ��������, ������� 4 �� �������.
//��� ��������� - long. ����� ������ �������� ����� - 
//������� 12 �����������.��������� ���� ������.
//����� Count ���������:
//������� �� ������� ����� ���������, �� �����������.
#include <windows.h>
#include <iostream>
#include <time.h>
#include "Header.h"
using namespace std;
int main()
{
	srand(time(0));

	long i, N = 30;
	long* arr = new long[N];
	for (i = 0; i < N; i++)
	{
		arr[i] = rand() % 50;
		cout << arr[i] << ' ';
	}
	cout << endl;

	HANDLE hThread[2];
	DWORD dwThread[2];
	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, arr, 0, &dwThread[0]);
	if (hThread == NULL)
		return GetLastError();
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)counter, NULL, 0, &dwThread[1]);
	if (hThread[1] == NULL)
		return GetLastError();
	// ���� ���������� ������ worker � counter
	if (WaitForMultipleObjects(2, hThread, TRUE, INFINITE) != WAIT_OBJECT_0)
	{
		cout << "Wait for single object failed." << endl;
		cout << "Press any key to exit." << endl;
	}
	// ��������� ���������� ������ worker � counter
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	return 0;
}