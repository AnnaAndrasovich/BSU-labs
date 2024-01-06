#include <windows.h>
#include <iostream>
#include <time.h>
#include <string>
using namespace std;
HANDLE hOutEvent[2];
CRITICAL_SECTION cs;

DWORD WINAPI work(string &s)
{
	cout << "work 2_thread:\n";
	string lat_chars = "", sign = "";
	cout << "work event: -> critical section\n";
	for (int i = 0; i < s.size() - 1; i++) {
		sign = s.substr(i, 1);
		if (sign >= "A" && sign <= "z")
			lat_chars += sign;
	}
	cout << "This is " << lat_chars.size() << " char of string: " << lat_chars << endl;
	s = lat_chars;
	SetEvent(hOutEvent[0]);
	cout << "work thread: leaving critical section\n";
	return 0;
}

DWORD WINAPI Count_Element(string &str)
{
	cout << "count 3_thread: \n";
	cout << "is waiting for 2nd thread\n";
	int k = 0;
	WaitForSingleObject(hOutEvent[0], INFINITE);
	cout << "count event: -> critical section\n";
	string lat_chars = "", a = "a", e = "e", o = "o", i = "i", y = "y", u = "u";
	string sign = "";
	for (int j = 0; j < str.size() - 1; j++) {
		sign = str.substr(j, 1);
		if ((sign == a) || (sign == i) || (sign == e) || (sign == u) || (sign == y) || (sign == o)){
			k++;
			lat_chars += sign;
		}
	}
	cout << k << " vowels of string: " <<lat_chars<< endl;
	SetEvent(hOutEvent[1]);
	cout << "count thread: leaving critical section\n";
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	string* the_line = new string[1];
	the_line[0] = "aluhiëKOäîSDGSîäðGsodøíïuheuhwøíeaeiohfwsdjjsjb";
	cout << "string S: " << the_line[0] << "\n";
	cout << "string S length: " << the_line[0].length() << endl;
	int N = rand() % the_line[0].length();
	cout << "count: " << N << "\n\n";
	HANDLE hThread[2]{};
	DWORD IDThread[2]{};
	hOutEvent[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hOutEvent[0] == NULL)
		return GetLastError();
	hOutEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hOutEvent[1] == NULL)
		return GetLastError();
	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work, the_line, 0, &IDThread[0]);
	if (hThread[0] == NULL)
		return GetLastError();
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Count_Element, the_line, 0, &IDThread[1]);
	if (hThread[1] == NULL)
		return GetLastError();
	WaitForSingleObject(hOutEvent[0], INFINITE);
		cout << "main: Have been waiting for hOutEvent[0]" << "\n";
		cout << "\nMAIN mas:" << the_line[0].substr(0, N) << "\n" << endl;
	WaitForSingleObject(hOutEvent[1], INFINITE);
	cout << "main: Have been waiting for hOutEvent[1]" << "\n";
	cout << "MAIN mas:" << the_line[0].substr(0, N) << endl;
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hOutEvent[0]);
	CloseHandle(hOutEvent[1]);
	return 0;
}
