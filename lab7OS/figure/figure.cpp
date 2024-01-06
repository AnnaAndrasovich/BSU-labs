#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	HANDLE hReadChannelReady = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"WRITE_EVENT");
	HANDLE hWriteChannelReady = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"READ_EVENT");
	HANDLE hWritePipe = (HANDLE)atoi(argv[1]), hReadPipe = (HANDLE)atoi(argv[0]);
	int dwBytesWritten = 0;
	WaitForSingleObject(hReadChannelReady, INFINITE);
	int n;
	if (!ReadFile(hReadPipe, (int*)&n, sizeof(int), (LPDWORD)&dwBytesWritten, NULL)){
		_cputs("Read from file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	cout << "Original array:\nSize: " << n << endl;
	char* arr = new char[n];
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 100 - 50;
		cout << static_cast<int>(arr[i]) << " ";
	}
	cout << endl;
	int sum = 0;
	for (int i = 0; i < n; i++)
		if ((arr[i] >= '1'&& arr[i] <= '9') ||  (arr[i]>='1' && arr[i] <= '255'))
			sum++;
	cout << endl;
	if (!WriteFile(hWritePipe, &(sum), sizeof(int), (LPDWORD)&dwBytesWritten, NULL)){
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	SetEvent(hWriteChannelReady);
	for (int i = 0; i < n; i++){
		WaitForSingleObject(hReadChannelReady, INFINITE);
		if (!WriteFile(hWritePipe, &(arr[i]), sizeof(arr[i]), (LPDWORD)&dwBytesWritten, NULL)){
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		SetEvent(hWriteChannelReady);
	}
	_cputs("Press any key to finish.\n");
	_getch();
	return 0;
}