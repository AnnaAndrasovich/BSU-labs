#pragma once
#include <iostream>
using namespace std;
long fib(int n) {
	int x = 1;
		if (n > 0)
			x = fib(n - 1) + fib(n - 2);
		return x;
}
DWORD WINAPI counter()
{
	int c = 0, x = 0, y = 1;
	Sleep(500);
	cout << "Enter the n-Fibonacci" << ' ';
	cin >> c;
	for (int i = 0; i < c; i++)
		cout << fib(i) << ' ';
	cout << endl;
	return 0;
}
DWORD WINAPI worker(long* mas) {
	for (int i = 0; i < 30; i++)
	{
		if (mas[i] % 4 == 0)
			cout << mas[i] << ' ';
		cout << flush << '\a';
		Sleep(12);
	}
	cout << endl;
	return 0;
}